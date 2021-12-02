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
		static void insert_range(storage_t&, Iterator, Iterator end) {}
		[[deprecated("Static storage logger doesn't implement that function")]]
		static void add_sink(storage_t& storage, sink_ptr sink) {}
		[[deprecated("Static storage logger doesn't implement that function")]]
		static void remove_sink(storage_t& storage, sink_ptr sink) {}
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

	template<typename... Args>
	template<typename Iterator>
	void dynamic_storage_policy<Args...>::insert_range(storage_t& storage, Iterator begin, Iterator end)
	{
		storage.insert(storage.end(), begin, end);
	}

	template<typename... Args>
	void dynamic_storage_policy<Args...>::add_sink(storage_t& storage, sink_ptr sink)
	{
		storage.push_back(sink);
	}

	template<typename... Args>
	void dynamic_storage_policy<Args...>::remove_sink(storage_t& storage, sink_ptr sink)
	{
		for (std::size_t i = 0; i < storage.size(); ++i)
			if (storage[i] == sink)
				storage.erase(storage.begin() + i);
	}
}