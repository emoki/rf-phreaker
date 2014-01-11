#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include <fstream>
#include <boost/timer/timer.hpp>

namespace rf_phreaker {

class benchmark
{
public:
	benchmark()
	{
		clear();
	}

	benchmark(const std::string &filename, bool append)
	{
		clear();
		open_benchmark(filename, append);
	}

	void open_benchmark(const std::string &filename, bool append)
	{
		file_.open(filename.c_str(), append ? std::ios_base::app : 0);
		if(!file_)
			throw std::runtime_error("Unable to open benchmark file.");
	}

	void clear()
	{
		total_time_elapsed_.clear();
		time_elapsed_.clear();
	}

	void start_timer()
	{
		time_elapsed_.clear();
		timer_.start();
	}

	void stop_timer()
	{
		timer_.stop();
		time_elapsed_ = timer_.elapsed();
		total_time_elapsed_.system += time_elapsed_.system;
		total_time_elapsed_.user += time_elapsed_.user;
		total_time_elapsed_.wall += time_elapsed_.wall;
	}

	void output_time_elapsed(const std::string &str = "")
	{
		if(file_)
		{
			file_ << boost::timer::format(time_elapsed_, 6,"wall\t%w\tuser\t%u\tsystem\t%s\ttotal_cpu\t%t\ttotal_percentage\t%p\t")
				<< str 
				<< std::endl;
		}
	}

	void output_total_time_elapsed(const std::string &str = "")
	{
		if(file_)
		{
			file_ << boost::timer::format(total_time_elapsed_, 6,"wall\t%w\tuser\t%u\tsystem\t%s\ttotal_cpu\t%t\ttotal_percentage\t%p\t")
				<< str 
				<< std::endl;
		}
	}

	const boost::timer::cpu_times& total_time_elapsed() { return total_time_elapsed_; }

private:
	boost::timer::cpu_timer timer_;
	boost::timer::cpu_times time_elapsed_;
	boost::timer::cpu_times total_time_elapsed_;

	std::ofstream file_;
};

}

#endif