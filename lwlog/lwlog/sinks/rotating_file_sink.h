#pragma once

#include "../core.h"
#include "sink.h"
#include "../details/file_helper.h"

namespace lwlog::sinks
{
	class LWLOG_API rotating_file_sink : public sink
	{
	public:
		rotating_file_sink();
		~rotating_file_sink();

		virtual void sink_it(std::string_view message) override;
		static void init_log_file(std::string_view path_str, int file_size_limit, int rotations);

	private:
		static void rotate();

	private:
		static inline int m_file_size_limit;
		static inline int m_rotations;
		static inline int m_index;
		static inline std::string m_base_name;
		static inline details::file_helper m_file;
	};
}