#pragma once

#include "rf_phreaker/common/log.h"
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
				catch(const rf_phreaker::rf_phreaker_error &err) {
					delegate_sink::rf_phreaker_log().log_error(err.what(), -49999);
					p->set_exception(std::current_exception());
				}
				catch(const std::exception &err) {
					delegate_sink::rf_phreaker_log().log_error(err.what(), -49998);
					p->set_exception(std::current_exception());
				}
				catch(...) {
					p->set_exception(std::current_exception());
					delegate_sink::rf_phreaker_log().log_error("An unknown error has occurred.", -50000);
				}
			});

			return ret;
		}

	private:
		bool done_;

		mutable T t_;

		mutable tbb::concurrent_bounded_queue<std::function<void()>> queue_;

		mutable std::thread thread_;

	};

}
