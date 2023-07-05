#pragma once

namespace lwlog
{
	struct colored_policy	{ static constexpr bool is_colored{ true }; };
	struct uncolored_policy { static constexpr bool is_colored{ false }; };
}