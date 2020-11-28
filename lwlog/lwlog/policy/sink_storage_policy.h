#pragma once

#include <array>
#include <vector>

#include "primitives.h"

namespace lwlog
{
	template<typename... Args>
	struct static_storage_policy
	{
		using storage = std::array<
			primitives::sink_ptr,
			sizeof...(Args)
		>;
	};

	template<typename... Args>
	struct dynamic_storage_policy
	{
		using storage = std::vector<
			primitives::sink_ptr
		>;
	};
}