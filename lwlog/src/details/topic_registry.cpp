#include "topic_registry.h"

namespace lwlog::details
{
    void topic_registry::set_separator(std::string_view separator)
    {
        m_separator = separator;
    }

    void topic_registry::start_topic(std::string_view topic)
    {
        m_topics.push_back(topic);

        m_current_topic = m_topics.back();
    }

    void topic_registry::end_topic()
    {
        m_topics.pop_back();

        m_current_topic = m_topics.back();
    }

    std::string_view topic_registry::current_topic() const
    {
        return m_current_topic;
    }

    std::string topic_registry::full_topic() const
    {
        std::string full_topic;

        for (auto it = m_topics.cbegin(); it != m_topics.cend(); ++it)
        {
            full_topic.append(*it);

            if ((it + 1) != m_topics.end())
            {
                full_topic.append(m_separator);
            }
        }

        return full_topic;
    }
}