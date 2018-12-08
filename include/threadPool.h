#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace easyUtils
{
using TASK = std::function<void()>;

class ThreadPool
{
public: // standard constructors
    // ThreadPool() case is covered by custom constructor
    ThreadPool(const ThreadPool &) = default;
    ThreadPool(ThreadPool &&) = default;
    ThreadPool &operator=(const ThreadPool &) = default;
    ThreadPool &operator=(ThreadPool &&) = default;
    ~ThreadPool() = default;
    //  custom constructor
    explicit ThreadPool(size_t size = 0);

    void operator()();

    void addJob(TASK t);
    void finish() noexcept;

    size_t size() const noexcept { return _poolSize; };

private:
    std::vector<std::thread> _workers;
    std::queue<TASK> _jobs;
    std::mutex _mxDOJOB;
    std::condition_variable _cvDOJOB;
    const size_t _poolSize;
    std::atomic<bool> _acceptingJobs;

    void processJobs();
};
} // end namespace easyUtils
