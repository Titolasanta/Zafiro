#ifndef THREAD_H
#define THREAD_H
#include <thread>
#include <mutex>


class Thread {
    protected:
        std::thread thread;
    public:
        bool joinable = false;

        Thread() {}

        void start();

        void join();

        virtual void run() = 0;
        virtual ~Thread() {}

        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;

        Thread(Thread&& other);

        Thread& operator=(Thread&& other);
};
	
#endif
