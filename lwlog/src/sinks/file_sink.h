#pragma once

#include "sink.h"
#include "details/file_writer.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class file_sink 
		: public sink<uncolored_policy, ThreadingPolicy>
		, private details::file_writer
	{
	private:
		using sink_t = sink<uncolored_policy, ThreadingPolicy>;

	public:
		file_sink() = default;
		explicit file_sink(std::string_view path);
		~file_sink() override;

	public:
		void sink_it(const details::record& record) override;

	private:
		std::vector<details::record> m_messages;
	};

	template<typename ThreadingPolicy>
	file_sink<ThreadingPolicy>::file_sink(std::string_view path)
		: details::file_writer(path) 
	{}

	template<typename ThreadingPolicy>
	file_sink<ThreadingPolicy>::~file_sink()
	{
		for (const auto& record : m_messages)
			details::file_writer::write(sink_t::m_pattern.compile(record));
	}

	template<typename ThreadingPolicy>
	void file_sink<ThreadingPolicy>::sink_it(const details::record& record)
	{
		m_messages.push_back(record);
	}
}