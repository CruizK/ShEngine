#pragma once

class Event
{
public:
	virtual ~Event();

	using EventType = int;

	virtual EventType GetType() const = 0;
protected:

private:
	
};

/*
	Event Handler:
	 - void Subscribe(T EventId, Func<EventArgs>)
	 Every event needs an array of Functions 
*/