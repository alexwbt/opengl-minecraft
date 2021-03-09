#include "pch.h"
#include "thread-pool.h"

namespace util
{
    ThreadPool::ThreadPool(int size)
    {
        threads_.reserve(size);
        for (int i = 0; i < size; i++)
            threads_.push_back(std::make_shared<Thread>(std::bind(&ThreadPool::RunThread, this, i)));
    }

    ThreadPool::~ThreadPool()
    {
        for (auto& thread : threads_)
        {
            thread->running = false;
            thread->thread.join();
        }
    }

    void ThreadPool::AddTask(std::function<void()> task)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            tasks_.push(task);
        }
        cv_.notify_all();
    }

    void ThreadPool::RunThread(int index)
    {
        while (threads_[index]->running)
        {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                cv_.wait(lock, [this]() { return !tasks_.empty(); });
                task = tasks_.front();
                tasks_.pop();
            }
            task();
        }
    }
}
