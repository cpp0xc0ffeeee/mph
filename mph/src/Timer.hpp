/*
 * Timer.hpp
 *
 *  Created on: Oct 11, 2017
 *      Author: butters
 */

#ifndef Timer_HPP_HA60B5678_ED48_4F58_9E92_7AD95977ABE0
#define Timer_HPP_HA60B5678_ED48_4F58_9E92_7AD95977ABE0

#include <chrono>
#include <utility>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>
#include <vector>
#include <stdexcept>
#include <thread>
#include <cstddef>

namespace mph
{
/*
 * class Timer has a thread for watching.
 * callback type: void(bool cancelled), argument "cancelled" indicate timer is cancelled or not.
 * every time call "expiresAt" or "expiresFromNow" will result a callback call, expired or cancelled.
 * during timer is watching(not expired yet) call "expiresAt" or "expiresFromNow" will cancel current watching and start another watching.
 * if destructor called during watching, current watching will be cancelled.
 * CT must meets the requirements of TrivialClock, and CT must be a steady clock.
*/

template<class CT>
class Timer
{

    static_assert(CT::is_steady, "");

public:
    using duration = typename CT::duration;
    using time_point = typename CT::time_point;

    using LockGuard = std::lock_guard<std::mutex>;
    using UniqueLock = std::unique_lock<std::mutex>;

private:

    enum class State
    {
        expired,
        waiting,
        finishing
    };

    const std::function<void(bool)> mCallback;

    std::mutex mMutex;
    std::condition_variable mCondVar;
    std::thread mThread;

    State mState;
    duration mTimeoutTSE;
    std::vector< bool > mResultVector;

public:

    /*
     * throw a exception std::invalid_argument if callback is empty.
     */
    Timer(std::function<void(bool)>&& callback)
            :mCallback( std::move(callback) )
            ,mState( State::expired )
    {
        if(mCallback == nullptr)
            throw std::invalid_argument("");
        mThread = std::thread( [this](){ run(); } );
    }

    Timer(std::nullptr_t) = delete;

    Timer(const Timer&) = delete;

    Timer(Timer&&) = delete;

    Timer& operator= (const Timer&) = delete;

    Timer& operator= (Timer&&) = delete;

    ~Timer()
    {
        {
            LockGuard lock(mMutex);
            if(mState == State::waiting)
            {
                mResultVector.emplace_back(true);
            }
            mState = State::finishing;
            mCondVar.notify_all();
        }
        mThread.join();
    }

    /*
     * start a new watching.
     * if called during watching, the watching will be cancelled(call the callback with bool=true argument) and start a new watching.
     */
    void expiresAt(time_point tp)
    {
        LockGuard lock(mMutex);
        auto nowTSE = CT::now().time_since_epoch();
        auto tpTSE = tp.time_since_epoch();
        if(mState == State::expired)
        {
            if(tpTSE <= nowTSE)
            {
                mResultVector.emplace_back( false );
            }
            else
            {
                mState = State::waiting;
                mTimeoutTSE = tpTSE;
                mCondVar.notify_all();
            }
        }
        else if(mState == State::waiting)
        {
            mResultVector.emplace_back(true);
            if( tpTSE <= nowTSE )
            {
                mState = State::expired;
                mResultVector.emplace_back( false );
                mCondVar.notify_all();
            }
            else
            {
                mState = State::waiting;
                mTimeoutTSE = tp.time_since_epoch();
                mCondVar.notify_all();
            }
        }
        else if(mState == State::finishing)
        {
            throw std::logic_error("");
        }
    }

    /*
     * same as expiresAt( CT::now() + dur )
     */
    void expiresFromNow(duration dur)
    {
        expiresAt(CT::now() + dur);
    }

    /*
     * cancel current watching, callback will be called in timer's thread.
     * notice: the expired result may on going during calling this "cancel()" function, and it cannot be cancelled.
     */
    void cancel()
    {
        LockGuard lock(mMutex);
        if(mState == State::waiting)
        {
            mState = State::expired;
            mResultVector.emplace_back(true);
            mCondVar.notify_all();
        }
        else if(mState == State::finishing)
        {
            throw std::logic_error("");
        }
    }

private:

    void run()
    {
        std::vector<bool> tmpResultVector;
        bool finishFlag = false;
        while(true)
        {

            {//sync
                UniqueLock lock(mMutex);
                do
                {
                    if(mState == State::expired)
                    {
                        if( !mResultVector.empty() )
                        {
                            tmpResultVector.swap(mResultVector);
                            break;
                        }
                        else
                        {
                            mCondVar.wait(lock);
                        }
                    }
                    else if(mState == State::waiting)
                    {
                        auto nowTSE = CT::now().time_since_epoch();
                        if( mTimeoutTSE <= nowTSE )
                        {
                            mResultVector.emplace_back(false);
                            tmpResultVector.swap(mResultVector);
                            break;
                        }
                        else
                        {
                            if( !mResultVector.empty() )
                            {
                                tmpResultVector.swap(mResultVector);
                                break;
                            }
                            else
                            {
                                auto cvState = mCondVar.wait_for( lock, mTimeoutTSE - nowTSE );
                                if(cvState == std::cv_status::timeout)
                                {
                                    mResultVector.emplace_back(false);
                                    tmpResultVector.swap(mResultVector);
                                    mState = State::expired;
                                    break;
                                }
                            }
                        }
                    }
                    else //mState == State::finishing, or something else.
                    {
                        tmpResultVector.swap(mResultVector);
                        finishFlag = true;
                        break;
                    }
                }while(true);
            }//end of sync

            for(auto cancelled : tmpResultVector)
            {
                mCallback(cancelled);
            }
            if(finishFlag)
                return;
            tmpResultVector.clear();

        }
    }

};

}


#endif /* Timer_HPP_HA60B5678_ED48_4F58_9E92_7AD95977ABE0 */
