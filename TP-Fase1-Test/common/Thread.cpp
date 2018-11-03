
#include <thread>
#include "Thread.h"


	void Thread::start() {
	joinable = true;
		thread = std::thread(&Thread::run, this);
	}

	void Thread::join() {
        if(joinable)
            thread.join();
        joinable = false;
	}

	Thread::Thread(Thread&& other) {
		this->thread = std::move(other.thread);
	}

	Thread& Thread::operator=(Thread&& other) {
		this->thread = std::move(other.thread);
		return *this;
	}

