#pragma once

//#include "rf_phreaker/common/delegate_sink_tmp.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/common_types.h"
#include "tbb/concurrent_queue.h"
#include <thread>
#include <future>


namespace rf_phreaker {

template <typename Fut, typename F, typename T> void set_value(std::promise<Fut> &p, F &f, T &t) { p.set_value(f(t)); }

template <typename F, typename T> void set_value(std::promise<void> &p, F &f, T &t) {
    f(t);
    p.set_value();
}

template <typename T> class concurrent {
  public:
    concurrent(T t = T())
        : t_(std::forward<T>(t)), done_(false), thread_([=] {
                                                    while (!done_) {
                                                        std::function<void()> f;
                                                        queue_.pop(f);
                                                        f();
                                                    }
                                                }) {}

    ~concurrent() {
        queue_.push([=] { done_ = true; });
        thread_.join();
    }

    template <typename F> auto operator()(F f) const -> std::future<decltype(f(/*concurrent::*/t_))> {
            auto p = std::make_shared<std::promise<decltype(f(t_))>>();
		
			auto ret = p->get_future();

			queue_.push([=] 
			{
				try
				{
					set_value(*p, f, t_);
				}
				catch(const rf_phreaker::rf_phreaker_error &) {
					//g_delegate_sink.log_error(err.what(), GENERAL_ERROR);
					p->set_exception(std::current_exception());
				}
				catch(const std::exception &) {
					//g_delegate_sink.log_error(err.what(), STD_EXCEPTION_ERROR);
					p->set_exception(std::current_exception());
				}
				catch(...) {
					//g_delegate_sink.log_error("An unknown error has occurred.", UNKNOWN_ERROR);
					p->set_exception(std::current_exception());
				}
			});

			return ret;
		}

	void clear_queue() {
		queue_.clear();
	}

	int approximate_size() {
		return queue_.size();
	}

	private:
		bool done_;

		mutable T t_;

		mutable tbb::concurrent_bounded_queue<std::function<void()>> queue_;

		mutable std::thread thread_;

	};

}
