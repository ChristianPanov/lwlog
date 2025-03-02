#include "topic_registry.h"

namespace lwlog::details
{
    void topic_registry::set_separator(const char* separator)
    {
        m_separator = separator;
    }

    void topic_registry::start_topic(const char* topic)
    {
        m_topics.push_back(topic);

        m_topic_index = static_cast<std::uint8_t>(m_topics.size() - 1);
    }

    void topic_registry::end_topic()
    {
        m_topic_index -= 1;
    }

    std::uint8_t topic_registry::topic_index() const
    {
        return m_topic_index;
    }

    const std::vector<const char*>& topic_registry::topics() const
    {
        return m_topics;
    }

    std::string topic_registry::full_topic(std::uint8_t topic_index) const
    {
        std::string full_topic;

        const auto end{ m_topics.cbegin() + topic_index + 1 };
        for (auto it = m_topics.cbegin(); it != end; ++it)
        {
            full_topic.append(*it);

            if ((it + 1) != end)
            {
                full_topic.append(m_separator);
            }
        }

        return full_topic;
    }
}