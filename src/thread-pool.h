#pragma once

namespace util
{
    class ThreadPool
    {
        std::vector<std::shared_ptr<std::thread>> threads_;
        bool running_ = false;

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