#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <string_view>

#include "core.h"
#include "detail.h"
#include "utilities.h"
#include "datetime.h"
#include "registry.h"

namespace lwlog
{
	enum class log_level
	{
		all =		(1 << 0),
		info =		(1 << 1),
		warning =	(1 << 2),
		error =		(1 << 3),
		critical =	(1 << 4),
		debug =		(1 << 5),
		none =		(1 << 6)
	};

	static log_level operator |(log_level lhs, log_level rhs)
	{
		return static_cast<log_level> (
			static_cast<std::underlying_type<log_level>::type>(lhs)
			| static_cast<std::underlying_type<log_level>::type>(rhs)
			);
	}

	static log_level operator &(log_level lhs, log_level rhs)
	{
		return static_cast<log_level> (
			static_cast<std::underlying_type<log_level>::type>(lhs)
			& static_cast<std::underlying_type<log_level>::type>(rhs)
			);
	}

	class LWLOG_API logger final
	{
	private:
		std::string m_message;
		std::string m_loggerName;
		std::string m_pattern;
		std::string m_logLevel;
		log_level m_logLevelVisibility;

	public:
		logger() = delete;
		logger(const logger&) = delete;
		logger(logger&&) = delete;
		logger& operator=(const logger&) = delete;
		logger& operator=(logger&&) = delete;

		explicit logger(std::string_view name);
		virtual ~logger() = default;

		void set_logLevel_visibility(log_level logLevel);
		void set_pattern(std::string_view pattern);

		void info(std::string_view message);
		void warning(std::string_view message);
		void error(std::string_view message);
		void critical(std::string_view message);
		void debug(std::string_view message);

		inline std::string get_name() const { return m_loggerName; }
		inline std::string get_pattern() const { return m_pattern; }
	};
}
