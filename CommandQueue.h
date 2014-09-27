#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H
#include <queue>
#include "Command.h"


class CommandQueue{
public:
	void push(const Command& command){ mQueue.push(command); }
	Command pop()
	{ 
		Command command = mQueue.front();
		mQueue.pop();
		return command;
	}
	bool isEmpty() const{ return mQueue.empty(); }
private:
	std::queue<Command> mQueue;
};



#endif