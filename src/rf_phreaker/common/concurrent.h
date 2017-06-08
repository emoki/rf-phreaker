#pragma once

//#include "rf_phreaker/common/delegate_sink_tmp.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/common_types.h"
#include "tbb/concurrent_queue.h"
#include <thread>
#include <future>
#include <functional>
#include <type_traits>
#include <memory>
#include <stdexcept>


namespace rf_phreaker {

// From g3log: https://bitbucket.org/KjellKod/g3log
// A straightforward technique to move around packaged_tasks or anything else that is not copyable
//  Instances of std::packaged_task are MoveConstructible and MoveAssignable, but
//  not CopyConstructible or CopyAssignable. To put them in a std container they need
//  to be wrapped and their internals "moved" when tried to be copied.
template<typename Moveable>
struct MoveOnCopy {
	mutable Moveable _move_only;

	explicit MoveOnCopy(Moveable&& m) : _move_only(std::move(m)) {}
	MoveOnCopy(MoveOnCopy const& t) : _move_only(std::move(t._move_only)) {}
	MoveOnCopy(MoveOnCopy&& t) : _move_only(std::move(t._move_only)) {}

	MoveOnCopy& operator=(MoveOnCopy const& other) {
		_move_only = std::move(other._move_only);
		return *this;
	}

	MoveOnCopy& operator=(MoveOnCopy&& other) {
		_move_only = std::move(other._move_only);
		return *this;
	}

	void operator()() { _move_only(); }

	Moveable& get() { return _move_only; }

	Moveable release() { return std::move(_move_only); }
};

// Repository: https://github.com/KjellKod/Concurrent
//
// Concurrent Wrapper
// ===============================
// Wrap "any" object to get concurrent access with asynchronous execution in FIFO  order.
// Published originally at :
// http://kjellkod.wordpress.com/2014/04/07/concurrency-concurrent-wrapper/
// https://github.com/KjellKod/concurrent
//
//
// 1) The "concurrent" can wrap ANY object
// 2) All access to the concurrent is done though a lambda or using an easy pointer-to-member function call.
// 3) All access call to the concurrent is done asynchronously and they are executed in FIFO order
// 4) At scope exit all queued jobs has to finish before the concurrent goes out of scope
// 5) A function call to a concurrent wrapped object can either be bundled for several actions within one asynchronous call
//   or it can be a single action within that asynchronous call
//
// =========================================
// 1) Single Action per Single Asynchronous call. KjellKod's g3log approach.
// example usage:
// struct Hello { void world() { cout << "Hello World" << endl; } };
//  concurrent<Hello> ch;
//  ch.call(&world);
//
//
// 2) Bundled actions per Single Asynchronous call. Herb Sutter's approach
//                    Ref: http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Herb-Sutter-Concurrency-and-Parallelism
// The calls are made through a lambda. Multiple actions can be bundled. It also helps when there are overloads of the same function
// concurrent<Hello> ch;
// ch.lambda( [](Hello& msg){
//                msg.world();
//                msg.world();
//            });
//
//

namespace concurrent_helper {
typedef std::function<void() > Callback;

/** helper for non-void promises */
template<typename Fut, typename F, typename T>
void set_value(std::promise<Fut>& p, F& f, T& t) {
	p.set_value(f(t));
}

/** helper for setting promise/exception for promise of void */
template<typename F, typename T>
void set_value(std::promise<void>& p, F& f, T& t) {
	f(t);
	p.set_value();
}
} // namespace concurrent_helper

  /**
  * Basically a light weight active object. www.kjellkod.cc/active-object-with-cpp0x#TOC-Active-Object-the-C-11-way
  * all input happens in the background. At shutdown it exits only after all
  * queued requests are handled.
  */
template <class T> class concurrent {
	mutable std::unique_ptr<T> _worker;
	mutable tbb::concurrent_bounded_queue<concurrent_helper::Callback> queue_;
	bool done_; // not atomic since only the thread is touching it
	std::thread thread_;

	concurrent(const concurrent&) = delete;
	concurrent& operator=(const concurrent&) = delete;

public:

	/**  Constructs an unique_ptr<T>  that is the background object
	* @param args to construct the unique_ptr<T> in-place
	*/
	template<typename ... Args>
	concurrent(Args&& ... args)
		: concurrent(std::make_unique<T>(std::forward<Args>(args)...)) {}

	/**
	* Moves in a unique_ptr<T> to be the background object. Starts up the worker thread
	* @param worker to act as the background object
	*/
	concurrent(std::unique_ptr<T> worker)
		: _worker(std::move(worker))
		, done_(false)
		, thread_([=] {
		concurrent_helper::Callback call;
		while(_worker && !done_) {

			queue_.pop(call);
			call();
		}
	}) {}

	/**
	* Clean shutdown. All pending messages are executed before the shutdown message is received
	*/
	virtual ~concurrent() {
		queue_.push([=] {done_ = true; });
		if(thread_.joinable()) {
			thread_.join();
		}
	}

	/**
	* @return whether the background object is still active. If the thread is stopped then
	* the background object will also be removed.
	*/
	bool empty() const {
		return !_worker;
	}

	/**
	*  Following Herb Sutter's approach for a concurrent wrapper
	* using std::promise and setting the value using a lambda approach
	*
	* Example:   struct Hello { void foo(){...}
	*               concurrent<Hello>  h;
	*               h.lambda( [](Hello& object){ object.foo(); };
	*
	* @param func lambda that has to take the wrapped object by reference as argument
	*             the lambda will be called by the wrapper for the given lambda
	* @return std::future return of the lambda
	*/
	template<typename F>
	auto lambda(F func) const -> std::future<decltype(func(*_worker))> {
		auto p = std::make_shared<std::promise<decltype(func(*_worker))>>();
		auto future_result = p->get_future();

		if(empty()) {
			p->set_exception(std::make_exception_ptr(std::runtime_error("nullptr instantiated worker")));
		}
		else {
			queue_.push([=] {
				try {
					concurrent_helper::set_value(*p, func, *_worker);
				}
				catch(...) {
					p->set_exception(std::current_exception());
				}
			});
		}
		return future_result;
	}

	/**
	* Following Kjell Hedstr�m (KjellKod)'s approach for a concurrent wrapper in g3log
	* using std::packaged_task and and std::bind (since lambda currently cannot
	* deal with expanding parameter packs in a lambda).
	*
	* Example:   struct Hello { void foo(){...}
	*            concurrent<Hello>  h;
	*            std::future<X> result = h.call(&Hello::foo);
	*
	* @param func function pointer to the wrapped object
	* @param args parameter pack to executed by the function pointer.
	* @return std::future return of the background executed function
	*/
	template<typename AsyncCall, typename... Args>
	auto call(AsyncCall func, Args&& ... args) const -> std::future<typename std::result_of< decltype(func)(T*, Args...)>::type> {
		typedef typename std::result_of<decltype(func)(T*, Args...)>::type result_type;
		typedef std::packaged_task<result_type()> task_type;

		if(empty()) {
			auto p = std::make_shared<std::promise<result_type>>();
			std::future<result_type> future_result = p->get_future();
			p->set_exception(std::make_exception_ptr(std::runtime_error("nullptr instantiated worker")));
			return future_result;
		}

		// weak compiler support for expanding parameter pack in a lambda. std::function is the work-around
		// With better compiler support it can be changed to:
		//       auto bgCall = [&, args...]{ return (_worker.*func)(args...); };
		auto bgCall = std::bind(func, _worker.get(), std::forward<Args>(args)...);
		task_type task(std::move(bgCall));
		std::future<result_type> result = task.get_future();
		queue_.push(MoveOnCopy<task_type>(std::move(task)));
		return std::move(result);
	}

	/**
	* Using a "fire and forget' approach with async execution without receiving a std::future
	* Ignoring the future for the other calls, @ref call, @ref lambda would force a synchronous
	* wait until the std::future is done
	*
	* WARNING: This function call MAY THROW if instantiated with a null object. This follows
	* the policy in the other functions @ref call @ref lambda but of course for them the
	* exception is baked into a std::future
	*
	* Example usage
	* :   struct Hello { void foo(){...}
	*            concurrent<Hello>  h;
	*            for (int i = 0; i < 100; ++i) {
	*               h.fire(&Hello::foo);
	*             }
	*/
	template<typename AsyncCall, typename... Args>
	void fire(AsyncCall func, Args&& ... args) const noexcept(false) {

		if(empty()) {
			throw std::runtime_error("nullptr instantiated worker");
		}
		// weak compiler support for expanding parameter pack in a lambda. std::function is the
		// work-around, With better compiler support it can be changed to:
		//       auto bgCall = [&, args...]{ return (_worker.*func)(args...); };
		auto bgCall = std::bind(func, _worker.get(), std::forward<Args>(args)...);
		queue_.push(bgCall);
		return;
	}
	
	virtual size_t approximate_size() { return queue_.size(); }

	void clear_queue() { queue_.clear(); }
	
	void clear_and_wait(int loop, int ms_wait) {
		queue_.clear();
		for(int i = 0; i < loop; i++) {
			if(queue_.size() > 0) {
				std::this_thread::sleep_for(std::chrono::milliseconds(ms_wait));
			}
		}
	}
};


}
