#pragma once

namespace lwlog
{
    struct enable_thread_id     {};
    struct disable_thread_id    {};
    struct enable_process_id    {};
    struct disable_process_id   {};

    template<typename ThreadIdPolicy, typename ProcessIdPolicy>
    struct configuration 
    {
        using thread_id_t = ThreadIdPolicy;
        using process_id_t = ProcessIdPolicy;
    };

    using default_config = configuration<disable_thread_id, disable_process_id>;
}