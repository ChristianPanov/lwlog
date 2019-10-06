#pragma once

#include "../core.h"
#include "../details/file_helper.h"
#include "sink.h"

namespace lwlog::sinks
{
	class LWLOG_API file_sink : public sink
	{
	public:
		virtual ~file_sink() = default;

		void init_log_file(std::string_view file_name, std::string_view path_str, std::size_t file_size_limit = 10240);
		void sink_it(std::string_view message, level log_level) override;

	private:
		details::file_helper m_file;
		std::size_t m_file_size_limit;
	};
}

