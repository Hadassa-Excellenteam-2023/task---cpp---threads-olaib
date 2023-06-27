#include "Consomer.h"
#include <iostream>

Consumer::Consumer(SafeQueue<Message>& queue, std::atomic<int>& terminationCount)
	: m_queue(queue), m_terminationCount(terminationCount) {}

void Consumer::run()
{
    try {
        while (m_terminationCount < MAX_TERMINATION_COUNT) {
            Message message = m_queue.pop();

            if (message.isLast) {
                ++m_terminationCount;
                std::cout << message.threadIdHash << FINISHED << std::endl;
            }
            else {
                std::cout << message.value << SENT << message.threadIdHash << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << CONSUMER_EXCEPTION << e.what() << std::endl;
    }
}
