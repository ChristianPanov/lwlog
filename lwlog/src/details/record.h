#pragma once

#include "configuration.h"
#include "source_meta.h"
#include "os/time_point.h"
#include "os/os.h"

namespace lwlog::details
{
	struct record_base
	{
		record_base() = default;
		record_base(std::string_view message, level log_level, const source_meta& meta);

		virtual const os::time_point_base& time_point() const = 0;
		virtual const os::execution_context_base& exec_context() const = 0;

		std::string_view message;
		level log_level;
		source_meta meta;
	};

	template<typename Config>
	struct record : public record_base
	{
		record() = default;
		record(std::string_view message, level log_level, const source_meta& meta);

		const os::time_point_base& time_point() const override;
		const os::execution_context_base& exec_context() const override;

	private:
		os::time_point<
			typename Config::time_t,
			typename Config::local_time_t,
			typename Config::precise_units_t
		> m_time_point{};

		os::execution_context<
			typename Config::thread_id_t,
			typename Config::process_id_t
		> m_execution_context{};
	};
}

#include "record_impl.h"