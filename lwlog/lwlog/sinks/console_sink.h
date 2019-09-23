#pragma once

#include "../core.h"
#include "sink.h"

namespace lwlog::sinks
{
	class LWLOG_API console_sink : public sink
	{
	public:
		console_sink();
		virtual ~console_sink() = default;

		void log(std::string_view message, level log_level) override;

		void set_level_visibility(level log_level);
		void set_pattern(std::string_view pattern);

	private:
		std::string m_pattern;
		level m_level;
	};
}