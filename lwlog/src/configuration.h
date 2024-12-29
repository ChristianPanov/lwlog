#pragma once

namespace lwlog
{
    struct enable_thread_id {}; 
    struct disable_thread_id {};
    struct enable_process_id {}; 
    struct disable_process_id {};

    struct enable_local_time {}; 
    struct disable_local_time {};

    struct enable_topics {};
    struct disable_topics {};

    template<typename LocalTimePolicy, typename ThreadIdPolicy, 
        typename ProcessIdPolicy, typename TopicPolicy>
    struct configuration
    {
        using local_time_t = LocalTimePolicy;
        using thread_id_t = ThreadIdPolicy;
        using process_id_t = ProcessIdPolicy;
        using topic_t = TopicPolicy;
    };
}