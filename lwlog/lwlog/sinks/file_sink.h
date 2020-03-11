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
		~file_sink();

		virtual void sink_it(std::string_view message) override;
		static void init_log_file(std::string_view path_str, int file_size_limit = -1);

	private:
		static inline int m_file_size_limit;
		static inline details::file_helper m_file;
	};
}
