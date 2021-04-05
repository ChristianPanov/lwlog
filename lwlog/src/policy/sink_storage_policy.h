#pragma once

namespace lwlog
{
	template<typename... Args>
	struct static_storage_policy
	{
		using storage = std::array<
			sink_ptr,
			sizeof...(Args)
		>;
	};

	template<typename... Args>
	struct dynamic_storage_policy
	{
		using storage = std::vector<
			sink_ptr
		>;
	};

	template<typename... Args>
	using default_storage_policy = dynamic_storage_policy<Args...>;
}