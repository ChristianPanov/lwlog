#pragma once

#include "sink.h"
#include "details/file_helper.h"

namespace lwlog::sinks
{
	class file_sink : public sink
	{
	public:
		file_sink() = default;
		file_sink(std::string_view path_str, int file_size_limit = -1);
		~file_sink();

		virtual void sink_it(std::string_view message) override;

	private:
		int m_file_size_limit{ 0 };
		details::file_helper m_file;
	};
}
