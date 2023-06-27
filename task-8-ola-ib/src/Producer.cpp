#include "Producer.h"

Producer::Producer(const int& id, SafeQueue<Message>& queue)
    : m_id(id), m_queue(queue), m_value(static_cast<float>(m_id)) {}


void Producer::addMessage(const double& value, const std::size_t& threadIdHash)
{
	Message message(m_value, threadIdHash, false);
	m_queue.push(message);
}

void Producer::run()
{
    try {
        std::size_t threadIdHash = std::hash<std::thread::id>{}(std::this_thread::get_id());
        while (m_value > DOUBLE_ZERO) {
            Message message(m_value, threadIdHash, !IS_LAST_MSG);
            m_queue.push(message);

            m_value /= DEVIDING_FACTOR;
        }

        Message lastMessage(DOUBLE_ZERO, threadIdHash, IS_LAST_MSG);
        m_queue.push(lastMessage);
    }
    catch (const std::exception& e) {
        std::cerr << PRODUCER_EXCEPTION << e.what() << std::endl;
    }
};
