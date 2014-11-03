/*
 * Event.h
 *
 *  Created on: Sep 5, 2014
 *      Author: ck
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <iostream>
#include <list>
#include <functional>
#include <cstdint>



namespace rf_phreaker { namespace gps_comm {


// Have to wrap std::function in order to get == operator

template<class> class EventHandler;
template<class> class Event;


template<typename... Args>
class EventHandler<void(Args...)>
{
	friend Event<void(Args...)>;
private:
	static uint64_t LastID;
	uint64_t ID;
	std::function<void(Args...)> handler;

	void _copy(const EventHandler& ref){
		if(&ref != this){
			_iterator = ref._iterator;
			handler = ref.handler;
			ID = ref.ID;
		}
	}

	typename Event<void(Args...)>::ListIterator _iterator;
public:

	typedef void(*CFunctionPointer)(Args...);

	EventHandler(std::function<void(Args...)> h) : _iterator(), handler(h), ID(++LastID)
	{
	}
	EventHandler(const EventHandler& ref){
		_copy(ref);
	}
	virtual ~EventHandler(){};

	EventHandler& operator=(const EventHandler& ref){
		_copy(ref);
		return *this;
	}
	void operator() (Args... args){
		handler(args...);
	}
	bool operator==(const EventHandler& ref){
		return _iterator == ref._iterator;
	}
	bool operator!=(const EventHandler& ref){
		return _iterator != ref._iterator;
	}

	uint64_t GetID(){
		return ID;
	}
	//can be null
	CFunctionPointer* GetFunctionPointer(){
		CFunctionPointer* ptr = handler.template target<CFunctionPointer>();
		return ptr;
	}
};
template<typename... Args>
uint64_t EventHandler<void(Args...)>::LastID = 0;


template <typename ... Args>
class Event<void(Args...)>
{
	friend EventHandler<void(Args...)>;
private:
	std::list<EventHandler<void(Args...)>> handlers;
	typedef typename std::list<EventHandler<void(Args...)>>::iterator ListIterator;
	void _copy(const Event& ref){
		if(&ref != this){
			handlers = ref.handlers;
		}
	};
public:

	bool Enabled;

	Event() : Enabled(true)
	{
	};
	virtual ~Event() 			{};
	Event(const Event& ref) 	{
		_copy(ref);
	};

	void Call(Args... args)	{
		if(!Enabled) { return; }
		for(auto h = handlers.begin(); h != handlers.end(); h++)
		{
			(*h)(args...);
		}
	};
	EventHandler<void(Args...)> RegisterHandler(EventHandler<void(Args...)> handler)	{
		bool found = false;
		for(auto h = handlers.begin(); h != handlers.end(); h++)
		{
			if( (*h) == handler )	{
				found = true;
				break;
			}
		}
		if(!found)
		{
			ListIterator itr = handlers.insert(handlers.end(), handler);
			handler._iterator = itr;
		}
		return handler;
	};
	EventHandler<void(Args...)> RegisterHandler(std::function<void(Args...)> handler)	{
		EventHandler<void(Args...)> wrapper(handler);
		ListIterator itr = handlers.insert(handlers.end(), wrapper);
		wrapper._iterator = itr;
		return wrapper;
	};
private:
	bool RemoveHandler(ListIterator handlerIter)	{
		if( handlerIter == handlers.end() ){
			return false;
		}

		handlers.erase(handlerIter);
		return true;
	};
public:
	bool RemoveHandler(EventHandler<void(Args...)>& handler)	{
		bool sts = RemoveHandler( handler._iterator );
		handler._iterator = handlers.end();
		return sts;
	};

	void Clear(){
		for(auto h = handlers.begin(); h != handlers.end(); h++)
		{
			(*h)._iterator = handlers.end();
		}
		handlers.clear();
	};

	void operator ()(Args... args)													{ return Call(args...); };
	EventHandler<void(Args...)> operator +=(EventHandler<void(Args...)> handler)	{ return RegisterHandler(handler); };
	EventHandler<void(Args...)> operator +=(std::function<void(Args...)> handler)	{ return RegisterHandler(handler); };
	bool operator -=(EventHandler<void(Args...)>& handler)							{ return RemoveHandler(handler); };
	bool operator -=(uint64_t handlerID)											{ return RemoveHandler(handlerID); };

	EventHandler<void(Args...)>& operator =(const EventHandler<void(Args...)>& ref){
		_copy(ref);
		return *this;
	};

};




}}

#endif /* EVENT_H_ */
