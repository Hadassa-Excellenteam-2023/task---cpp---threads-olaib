#pragma once
#include "SafeQueue.h"
#include <iostream>


// representing the message sent by the producers
typedef struct Message {
    double value;
    std::size_t threadIdHash;
    bool isLast;

    Message(double value, std::size_t threadIdHash, bool isLast)
        : value(value), threadIdHash(threadIdHash), isLast(isLast) {}
} Message;

// Producer class
// This class is used to create the producers which send messages to the queue 
class Producer {
public:
    Producer(const int& id, SafeQueue<Message>& queue);

    void run();
    void addMessage(const double& value, const std::size_t& threadIdHash);


private:
    int m_id;
    SafeQueue<Message>& m_queue;
    double m_value;
};