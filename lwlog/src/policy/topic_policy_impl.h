#pragma once

#include "topic_policy.h"

namespace lwlog
{
    inline void topic_registry<enable_topics>::start_topic(std::string_view topic, container& registry)
    {
        registry.push(topic);
    }

    inline void topic_registry<enable_topics>::end_topic(container& registry)
    {
        registry.pop();
    }

    inline std::string_view& topic_registry<enable_topics>::current_topic(container& registry)
    {
        return registry.top();
    }

    inline void topic_registry<disable_topics>::start_topic(std::string_view, container&)
    {
    }

    inline void topic_registry<disable_topics>::end_topic(container&)
    {
    }

    inline std::string_view topic_registry<disable_topics>::current_topic(container&)
    {
        return {};
    }
}