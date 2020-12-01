#pragma once

namespace lwlog::interface
{
	class log_level
	{
	protected:
		~log_level() = default;

	public:
		virtual void info(std::string_view) = 0;
		virtual void warning(std::string_view) = 0;
		virtual void error(std::string_view) = 0;
		virtual void critical(std::string_view) = 0;
		virtual void debug(std::string_view) = 0;
	};
}