#pragma once

#include "../core.h"
#include "../details/file_helper.h"
#include "sink.h"

namespace lwlog::sinks
{
	class LWLOG_API file_sink : public virtual sink
	{
	public:
		virtual ~file_sink();

		void init_log_file(std::string_view file_name, std::string_view path, std::size_t file_size_limit = 20480);
		void sink_it(std::string_view message, level log_level) override;

	private:
		details::file_helper m_file;
		std::size_t m_file_size_limit{ 0 };
	};
}
