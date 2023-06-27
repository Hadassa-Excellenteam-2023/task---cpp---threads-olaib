#pragma once
#include "Producer.h"
#include "SafeQueue.h"


// Consumer class
class Consumer {
public:
    Consumer(SafeQueue<Message>& queue, std::atomic<int>& terminationCount);
    void run();

private:
    SafeQueue<Message>& m_queue;
    std::atomic<int>& m_terminationCount;
};