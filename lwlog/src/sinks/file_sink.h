#pragma once

#include "sink.h"
#include "details/file_writer.h"

namespace lwlog::sinks
{
	template<typename ThreadingPolicy>
	class file_sink 
		: public sink<uncolored_policy, ThreadingPolicy>
		, public details::file_writer
	{
	public:
		file_sink() = default;
		explicit file_sink(std::string_view path) : details::file_writer(path) {}
		void sink_it(std::string_view message) override 
		{
			details::file_writer::write(message.data());
		}
	};
}