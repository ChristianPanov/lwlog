#pragma once

namespace lwlog::interface
{
	template<typename... Args>
	void logger::info(const details::log_message& log_msg, Args&&... args)
	{
		this->info_impl(log_msg, { details::to_raw_string(std::forward<Args>(args))... });
	}

	template<typename... Args>
	void logger::warning(const details::log_message& log_msg, Args&&... args)
	{
		this->warning_impl(log_msg, { details::to_raw_string(std::forward<Args>(args))... });
	}

	template<typename... Args>
	void logger::error(const details::log_message& log_msg, Args&&... args)
	{
		this->error_impl(log_msg, { details::to_raw_string(std::forward<Args>(args))... });
	}

	template<typename... Args>
	void logger::critical(const details::log_message& log_msg, Args&&... args)
	{
		this->critical_impl(log_msg, { details::to_raw_string(std::forward<Args>(args))... });
	}

	template<typename... Args>
	void logger::debug(const details::log_message& log_msg, Args&&... args)
	{
		this->debug_impl(log_msg, { details::to_raw_string(std::forward<Args>(args))... });
	}
}
