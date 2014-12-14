#include <mutex>
#include <memory>

template<typename T>
class singleton
{
public:
	static T& instance() {
		static std::once_flag once_flag_;
		static std::unique_ptr<T> t_;
		std::call_once(once_flag_, []() { 
			t_.reset(new T());
		});
		return *t_;
	}
private:
	singleton() {}
};

