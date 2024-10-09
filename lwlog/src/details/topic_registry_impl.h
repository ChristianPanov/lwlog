#pragma once

namespace lwlog::details
{
    inline void topic_registry<enable_topics>::set_separator(std::string_view separator)
    {
        m_separator = separator;
    }

    inline void topic_registry<enable_topics>::start_topic(std::string_view topic)
    {
        m_topics.push_back(topic);

        m_current_topic = m_topics.back();
    }

    inline void topic_registry<enable_topics>::end_topic()
    {
        m_topics.pop_back();

        m_current_topic = m_topics.back();
    }

    inline std::string_view topic_registry<enable_topics>::current_topic() const
    {
        return m_current_topic;
    }

    inline std::string topic_registry<enable_topics>::full_topic() const
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

    inline void topic_registry<disable_topics>::set_separator(std::string_view) const
    {
    }

    inline void topic_registry<disable_topics>::start_topic(std::string_view) const
    {
    }

    inline void topic_registry<disable_topics>::end_topic() const
    {
    }

    inline std::string_view topic_registry<disable_topics>::current_topic() const
    {
        return {};
    }

    inline std::string topic_registry<disable_topics>::full_topic() const
    {
        return {};
    }
}