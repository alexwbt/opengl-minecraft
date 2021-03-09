#pragma once

namespace util
{
    class ThreadPool
    {
        struct Thread
        {
            std::thread thread;
            bool running;
            Thread(std::function<void()> run_function)
                : thread(run_function), running(true)
            {}
        };

        std::vector<std::shared_ptr<Thread>> threads_;

        std::queue<std::function<void()>> tasks_;

        std::mutex mutex_;
        std::condition_variable cv_;

    public:
        ThreadPool(int size);

        ~ThreadPool();

        void AddTask(std::function<void()> task);

    private:
        void RunThread(int index);
    };
}
