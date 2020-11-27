#pragma once

#include "sink.h"
#include "details/file_helper.h"

namespace lwlog::sinks
{
	class file_sink : public sink<uncolored_policy>
	{
	public:
		file_sink() = default;
		file_sink(std::string_view path, std::size_t size_limit = std::size_t{});
		~file_sink();

	public:
		virtual void sink_it(std::string_view message) override;

	private:
		std::size_t m_size_limit{};
		details::file m_file;
	};
}
