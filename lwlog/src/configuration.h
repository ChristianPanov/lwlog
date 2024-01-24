#pragma once

namespace lwlog
{
    struct enable_thread_id {};
    struct disable_thread_id {};
    struct enable_process_id {};
    struct disable_process_id {};

    struct enable_local_time {};
    struct disable_local_time {};
    struct enable_precise_units {};
    struct disable_precise_units {};

    template<
        typename ThreadIdPolicy, 
        typename ProcessIdPolicy,
        typename LocaltimePolicy,
        typename PreciseUnitsPolicy
    > struct configuration 
    {
        using thread_id_t = ThreadIdPolicy;
        using process_id_t = ProcessIdPolicy;
        using local_time_t = LocaltimePolicy;
        using precise_units_t = PreciseUnitsPolicy;
    };

    using default_config = configuration<
        disable_thread_id, 
        disable_process_id, 
        disable_local_time,
        disable_precise_units
    >;
}