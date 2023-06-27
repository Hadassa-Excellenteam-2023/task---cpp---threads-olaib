#pragma once
#include <mutex>
#include <condition_variable>
#include <deque>
#include "Utitlities.h"

/* Thread-safe queue - template class
 * This class is used to store the messages sent by the producers */
// Thread-safe queue implementation
template <typename T>
class SafeQueue {
public:
    void push(const T& value) {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push_back(value);
        }
        m_condition.notify_one();
    }

    T pop() {
        std::unique_lock lock(m_mutex);
        m_condition.wait(lock, [this]() { return !m_queue.empty(); });
        T value = m_queue.front();
        m_queue.pop_front();
        return value;
    }

    bool empty() const {
        std::lock_guard lock(m_mutex);
        return m_queue.empty();
    }

private:
    std::deque<T> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_condition;
};