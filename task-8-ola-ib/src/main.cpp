#include "Consomer.h"
#include "Producer.h"
#include "Utitlities.h"
#include "SafeQueue.h"
#include <thread>
#include <functional>
#include <atomic>
#include <vector>


int main() {
    try {
        SafeQueue<Message> queue;
        std::atomic terminationCount(INITIAL_TERMINATION_COUNT);

        Consumer consumer(queue, terminationCount);
        std::thread consumerThread(&Consumer::run, &consumer);

        std::vector<std::thread> producerThreads;
        for (int i = 1; i <= MAX_TERMINATION_COUNT; ++i) {
            Producer producer(i, queue);
            producerThreads.emplace_back(&Producer::run, &producer);
        }

        // Wait for all threads to finish
        for (auto& thread : producerThreads) {
            thread.join();
        }
        consumerThread.join();
    }
    catch (const std::exception& e) {
        std::cerr << EXCEPTION << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << UNKNOWN_EXCEPTION << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
