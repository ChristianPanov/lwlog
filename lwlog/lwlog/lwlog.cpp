#include "lwlog.h"
#include "registry.h"
#include "formatter.h"
#include "print.h"

namespace lwlog
{
	logger::logger(std::string_view logger_name)
		: m_logger_name(logger_name)
		, m_pattern("[%d, %x] [%l] [%n]: %v")
		, m_level(level::all)
		, m_backtrace_messages(0)
		, m_is_backtrace_enabled(false)
	{
		set_level_visibility(m_level);

		if (registry::is_registry_automatic() == true)
		{
			registry::register_logger(*this);
		}
	}

	void logger::set_level_visibility(level logLevel)
	{
		if (logLevel == level::all)
		{
			m_level = level::info | level::warning 
				| level::error | level::critical | level::debug;
		}
		else if (logLevel == level::none)
		{
			m_level = level::none;
		}
		else
		{
			m_level = logLevel;
		}
	}

	void logger::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
	}

	void logger::backtrace(std::size_t buffer_size)
	{
		m_is_backtrace_enabled = true;
		m_backtrace_buffer.reserve(buffer_size);
	}

	void logger::set_backtrace_stamp(std::string_view stamp)
	{
		m_backtrace_stamp = stamp;
	}

	void logger::display_backtrace()
	{
		for (const auto& i : m_backtrace_buffer)
		{
			lwlog::print("{0}{1}\n", m_backtrace_stamp, i);
		}
	}

	void logger::delete_backtrace()
	{
		m_backtrace_messages = 0;
		m_backtrace_buffer.clear();
	}

	void logger::push_in_backtrace_buffer(std::string_view message)
	{
		if (m_is_backtrace_enabled == true)
		{
			m_backtrace_messages++;
			if (m_backtrace_messages <= m_backtrace_buffer.capacity())
			{
				m_backtrace_buffer.emplace_back(message);
			}
		}
	}

	void logger::log(std::string_view message, level log_level)
	{
		m_message = message;

		formatter::insert_pattern_data({"%logger_name%",	"%n"}, m_logger_name);
		formatter::insert_pattern_data({"%message%",		"%v"}, m_message);
		formatter::insert_pattern_data({"%log_level%",		"%l"}, m_level_string);
		formatter::insert_pattern_data({"%log_level_abr%",	"%L"}, std::string(1, toupper(m_level_string[0])));

		if (static_cast<std::underlying_type_t<level>>(m_level)
			& static_cast<std::underlying_type_t<level>>(log_level))
		{
			lwlog::print("{0} \n", formatter::format(m_pattern));
		}

		push_in_backtrace_buffer(formatter::format(m_pattern));
	}

	void logger::info(std::string_view message)
	{
		m_level_string = "info";
		log(message, level::info);
	}

	void logger::warning(std::string_view message)
	{
		m_level_string = "warning";
		log(message, level::warning);
	}

	void logger::error(std::string_view message)
	{
		m_level_string = "error";
		log(message, level::error);
	}

	void logger::critical(std::string_view message)
	{
		m_level_string = "critical";
		log(message, level::critical);
	}

	void logger::debug(std::string_view message)
	{
		m_level_string = "debug";
		log(message, level::debug);
	}

	inline std::string logger::get_name() const
	{
		return m_logger_name;
	}

	inline std::string logger::get_pattern() const
	{
		return m_pattern;
	}
}