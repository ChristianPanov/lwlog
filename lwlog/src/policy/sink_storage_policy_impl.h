#pragma once

namespace lwlog
{
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
		{
			if (storage[i] == sink) storage.erase(storage.begin() + i);
		}
	}
}