/*
 * FixedThreadPool.hpp
 *
 *  Created on: Aug 27, 2017
 *      Author: butters
 */

#ifndef FixedThreadPool_HPP_H905E3AD8_1AFB_47CE_A5A0_1E2A96CDF3A5
#define FixedThreadPool_HPP_H905E3AD8_1AFB_47CE_A5A0_1E2A96CDF3A5

#include <cstddef>
#include <stdexcept>
#include <array>
#include <utility>
#include <thread>
#include <condition_variable>

#include "Util.hpp"
#include "JobQueue.hpp"

namespace mph
{

template<std::size_t POOL_SIZE>
class FixedThreadPool
{
public:

private:
    JobQueue mJobQueue;
    std::array<std::thread, POOL_SIZE> mPool;
    std::condition_variable mCondVar;

public:
    FixedThreadPool() noexcept
    {
        for(auto& thr : mPool)
        {
            thr=std::thread{ Util::bindMFunc<
                    JobQueue::Job,
                    FixedThreadPool,
                    &FixedThreadPool::processingFunc>(this) };
        }
    }

    FixedThreadPool(const FixedThreadPool&) = delete;

    FixedThreadPool(FixedThreadPool&&) = delete;

    FixedThreadPool& operator=(const FixedThreadPool&) = delete;

    FixedThreadPool& operator=(FixedThreadPool&&) = delete;

    ~FixedThreadPool() noexcept
    {
        mJobQueue.cancelWaitingJob();
        for(auto& thr : mPool)
        {
            if(thr.joinable())
                thr.join();
        }
    }

    void run(JobQueue::Job&& job) noexcept
    {
        mJobQueue.newJob( std::move(job) );
    }

private:

    void processingFunc() noexcept
    {
        while(true)
        {
            JobQueue::Job job=mJobQueue.waitAJob();
            if(!job)
                break;
            job();
        }
    }

};

} /* namespace mph */

#endif /* FixedThreadPool_HPP_H905E3AD8_1AFB_47CE_A5A0_1E2A96CDF3A5 */
