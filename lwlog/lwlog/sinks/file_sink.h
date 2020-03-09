#pragma once

#include "../core.h"
#include "sink.h"
#include "../details/file_helper.h"

namespace lwlog::sinks
{
	class LWLOG_API file_sink : public sink
	{
	public:
		file_sink();
		virtual ~file_sink();

		static void init_log_file(std::string_view file_name, std::string_view path, std::size_t file_size_limit = 20480);
		virtual void sink_it(std::string_view message) override;

	private:
		static inline std::size_t m_file_size_limit;
		static inline details::file_helper m_file;
	};
}
