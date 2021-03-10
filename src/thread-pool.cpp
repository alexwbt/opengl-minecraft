#include "pch.h"
#include "thread-pool.h"

namespace util
{
    ThreadPool::ThreadPool(int size) : running_(true)
    {
        threads_.reserve(size);
        for (int i = 0; i < size; i++)
            threads_.push_back(std::make_shared<std::thread>(std::bind(&ThreadPool::RunThread, this, i)));
    }

    ThreadPool::~ThreadPool()
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            running_ = false;
        }
        cv_.notify_all();
        for (auto& thread : threads_)
            if (thread->joinable())
                thread->join();
    }

    void ThreadPool::AddTask(std::function<void()> task, bool priority)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (priority) tasks_.push_front(task);
            else tasks_.push_back(task);
        }
        cv_.notify_all();
    }

    void ThreadPool::RunThread(int index)
    {
        while (true)
        {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                cv_.wait(lock, [this]() { return !tasks_.empty() || !running_; });
                if (!running_) break;
                task = tasks_.front();
                tasks_.pop_front();
            }
            task();
        }
    }
}
