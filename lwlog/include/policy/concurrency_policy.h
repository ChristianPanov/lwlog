#pragma once

namespace lwlog
{
    struct spsc_model_policy {};
    struct mpsc_model_policy {};

    struct block_overflow_policy        { static constexpr bool block_on_full{ true };  };
    struct discard_new_overflow_policy  { static constexpr bool block_on_full{ false }; };
}