#pragma once

#include "configuration.h"
#include "source_meta.h"
#include "os/datetime.h"
#include "os/os.h"

namespace lwlog::details
{
	struct record_base
	{
		record_base() = default;
		record_base(std::string_view message, level log_level, const source_meta& meta)
			: message{ message }
			, log_level{ log_level }
			, meta{ meta }
		{}

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
		record(std::string_view message, level log_level, const source_meta& meta)
			: record_base{ message, log_level, meta }
		{}

		const os::time_point_base& time_point() const override
		{
			return dynamic_cast<const os::time_point_base&>(m_time_point);
		}

		const os::execution_context_base& exec_context() const override
		{
			return dynamic_cast<const os::execution_context_base&>(m_execution_context);
		}

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