/*
 * JobQueue.cpp
 *
 *  Created on: Aug 27, 2017
 *      Author: butters
 */

#include "JobQueue.hpp"

namespace mph
{

JobQueue::JobQueue()
        :
          mStatus
              { Status::Working },
          mWaitingJobCount
              { 0 }
{
}

JobQueue::~JobQueue() noexcept
{
    std::unique_lock<std::mutex> lock(mMutex);
    if (mStatus != Status::Canceling)
    {
        mStatus = Status::Canceling;
        mCondVar.notify_all();
    }
    while (mWaitingJobCount != 0)
        mCondVar.wait(lock);
}

void JobQueue::newJob(Job&& job)
{
    if (!job)
        return;

    std::lock_guard<std::mutex> lock(mMutex);
    if (mStatus == Status::Canceling)
        throw std::system_error{ std::make_error_code(std::errc::operation_canceled) };

    mDeque.emplace_back(std::move(job));
    mCondVar.notify_one();
}

mph::JobQueue::Job JobQueue::waitAJobEx()
{
    std::unique_lock<std::mutex> lock(mMutex);
    if (mStatus == Status::Canceling)
        throw std::system_error{ std::make_error_code(std::errc::operation_canceled) };

    mWaitingJobCount += 1;
    while (mStatus == Status::Working && mDeque.empty())
        mCondVar.wait(lock);
    mWaitingJobCount -= 1;
    if (mStatus == Status::Canceling)
    {
        if (mWaitingJobCount == 0)
            mCondVar.notify_all();
        throw std::system_error{ std::make_error_code(std::errc::operation_canceled) };
    }
    Job job = std::move(mDeque.front());
    mDeque.pop_front();
    return job;
}

mph::JobQueue::Job JobQueue::waitAJob() noexcept
{
    std::unique_lock<std::mutex> lock(mMutex);
    if (mStatus == Status::Canceling)
        return nullptr;

    mWaitingJobCount += 1;
    while (mStatus == Status::Working && mDeque.empty())
        mCondVar.wait(lock);
    mWaitingJobCount -= 1;
    if (mStatus == Status::Canceling)
    {
        if (mWaitingJobCount == 0)
            mCondVar.notify_all();
        return nullptr;
    }
    Job job = std::move(mDeque.front());
    mDeque.pop_front();
    return job;
}

void JobQueue::clear() noexcept
{
    std::lock_guard<std::mutex> lock(mMutex);
    mDeque.clear();
}

void JobQueue::cancelWaitingJob() noexcept
{
    std::unique_lock<std::mutex> lock(mMutex);
    if (mStatus != Status::Canceling)
    {
        mStatus = Status::Canceling;
        mCondVar.notify_all();
    }
    while (mWaitingJobCount != 0)
        mCondVar.wait(lock);
}

} /* namespace mph */
