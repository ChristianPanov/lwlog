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

    inline void topic_registry<disable_topics>::start_topic(std::string_view, container&)
    {
    }

    inline void topic_registry<disable_topics>::end_topic(container&)
    {
    }
}