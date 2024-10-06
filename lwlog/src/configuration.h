#pragma once

namespace lwlog
{
    struct enable_time {}; 
    struct disable_time {};

    struct enable_thread_id {}; 
    struct disable_thread_id {};
    struct enable_process_id {}; 
    struct disable_process_id {};

    struct enable_local_time {}; 
    struct disable_local_time {};
    struct enable_precise_units {};
    struct disable_precise_units {};

    struct enable_topics {};
    struct disable_topics {};

    template<typename TimePolicy, typename LocalTimePolicy, typename PreciseUnitsPolicy,
        typename ThreadIdPolicy, typename ProcessIdPolicy, typename TopicPolicy>
    struct configuration
    {
        using time_t = TimePolicy;
        using local_time_t = LocalTimePolicy;
        using precise_units_t = PreciseUnitsPolicy;
        using thread_id_t = ThreadIdPolicy;
        using process_id_t = ProcessIdPolicy;
        using topic_t = TopicPolicy;
    };

    using default_config = configuration<enable_time, disable_local_time,
        enable_precise_units, enable_thread_id, enable_process_id, enable_topics>;
}