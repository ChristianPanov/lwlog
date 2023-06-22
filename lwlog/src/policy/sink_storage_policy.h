#pragma once

namespace lwlog
{
	template<typename... Args>
	struct static_storage_policy
	{
		using storage_t = std::array<
			sink_ptr, 
			sizeof...(Args)
		>;

		template<typename Iterator>
		[[deprecated("Static storage logger doesn't implement that function")]]
		static void insert_range(storage_t&, Iterator, Iterator) {}
		[[deprecated("Static storage logger doesn't implement that function")]]
		static void add_sink(storage_t&, sink_ptr) {}
		[[deprecated("Static storage logger doesn't implement that function")]]
		static void remove_sink(storage_t&, sink_ptr) {}
	};

	template<typename... Args>
	struct dynamic_storage_policy
	{
		using storage_t = std::vector<sink_ptr>;

		template<typename Iterator>
		static void insert_range(storage_t& storage, Iterator begin, Iterator end);
		static void add_sink(storage_t& storage, sink_ptr sink);
		static void remove_sink(storage_t& storage, sink_ptr sink);
	};
}

#include "sink_storage_policy_impl.h"