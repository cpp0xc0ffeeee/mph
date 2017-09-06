/*
 * JobQueue.hpp
 *
 *  Created on: Aug 27, 2017
 *      Author: butters
 */

#ifndef JobQueue_HPP_HB8531A42_BA21_42BB_BC79_F86C4A7AC9BC
#define JobQueue_HPP_HB8531A42_BA21_42BB_BC79_F86C4A7AC9BC

#include <utility>
#include <functional>
#include <deque>
#include <condition_variable>
#include <mutex>
#include <stdexcept>

namespace mph
{

class JobQueue
{
public:
    using Job=std::function<void()>;

private:

    enum class Status
    {
        Working,
        Canceling
    };

    std::deque<Job> mDeque;
    std::condition_variable mCondVar;
    std::mutex mMutex;
    Status mStatus;
    std::size_t mWaitingJobCount;

public:
    JobQueue();

    JobQueue(const JobQueue&) = delete;

    JobQueue(JobQueue&&) = delete;

    JobQueue& operator=(const JobQueue&) = delete;

    JobQueue& operator=(JobQueue&&) = delete;

    ~JobQueue() noexcept;

    void newJob(Job&& job);

    Job waitAJobEx();

    Job waitAJob() noexcept;

    void clear() noexcept;

    void cancelWaitingJob() noexcept;

};

} /* namespace mph */

#endif /* JobQueue_HPP_HB8531A42_BA21_42BB_BC79_F86C4A7AC9BC */
