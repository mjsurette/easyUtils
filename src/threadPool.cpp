
#include "threadPool.h"

using namespace std;

namespace easyUtils
{
//==============================================================================
ThreadPool::ThreadPool(size_t size)
    : _poolSize(size == 0 ? thread::hardware_concurrency() * 2 : size)
    , _acceptingJobs(true)
{
    _workers.reserve(_poolSize);
}

//==============================================================================
void ThreadPool::operator()()
{
    for(size_t i { 0 }; i < _poolSize; ++i)
        _workers.emplace_back(&ThreadPool::processJobs, this);
}

//==============================================================================
void ThreadPool::addJob(TASK t)
{
    if(!_acceptingJobs)
        throw std::logic_error(
            "Attempt to add job to closed queue in ThreadPool::addJob");

    {
        lock_guard<mutex> lk(_mxDOJOB);
        _jobs.push(move(t));
    }
    _cvDOJOB.notify_one();
}

//==============================================================================
void ThreadPool::finish() noexcept
{
    _acceptingJobs.store(false);
    _cvDOJOB.notify_all();
    for(auto &t : _workers)
        if(t.joinable())
            t.join();
}

//==============================================================================
void ThreadPool::processJobs()
{
    TASK task;
    unique_lock<mutex> lk(_mxDOJOB);

    while(!_jobs.empty() || _acceptingJobs.load())
    {
        if(!_jobs.empty())
        {
            task = move(_jobs.front());
            _jobs.pop();
            lk.unlock();
            task();
            lk.lock();
        }
        if(!_jobs.empty())
            continue;
        _cvDOJOB.wait(
            lk, [&] { return !_jobs.empty() || !_acceptingJobs.load(); });
    }
}

} // end namespace easyUtils
