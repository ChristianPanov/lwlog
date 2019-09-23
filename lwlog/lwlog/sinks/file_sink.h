#pragma once

#include "../core.h"
#include "../details/file_helper.h"
#include "sink.h"

namespace lwlog::sinks
{
	class LWLOG_API file_sink : public sink
	{
	public:
		file_sink();
		virtual ~file_sink() = default;

		void init_log_file(std::string_view file_name, std::string_view path_str, std::size_t file_size_limit = 10240);
		void log(std::string_view message, level log_level) override;

		void set_level_visibility(level log_level);
		void set_pattern(std::string_view pattern);

	private:
		std::string m_pattern;
		level m_level{ level::all };
		details::file_helper m_file;
		std::size_t m_file_size_limit;
	};
}

