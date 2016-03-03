#pragma once

#include <memory>
#include <boost/thread.hpp>

namespace cappeen_scanner {


class simple_logger
{
public:
	static simple_logger& instance()
	{
		if(logger_.get() == nullptr)
		{
			boost::lock_guard<boost::mutex> lock(m1_);
			if(logger_.get() == nullptr)
				logger_.reset(new simple_logger);
		}
		return *logger_;
	}

	template<typename Data>
	void log(const Data &data)
	{
		boost::lock_guard<boost::mutex> lock(m2_);
		std::cout << cappeen_utilities::create_time_stamp() << "\t" <<  data << std::endl;
	}

private:
	simple_logger() {};

	boost::mutex m2_;

	static std::unique_ptr<simple_logger> logger_;
	static boost::mutex m1_;
};

}