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

		virtual const os::execution_context_base& exec_context() const = 0;

		std::string_view		message;
		level					log_level;
		source_meta				meta;
		os::time_point			time_point{};
	};

	template<typename Config>
	struct record : public record_base
	{
		record() = default;
		record(std::string_view message, level log_level, const source_meta& meta)
			: record_base{ message, log_level, meta }
		{}

		const os::execution_context_base& exec_context() const override
		{
			return dynamic_cast<const os::execution_context_base&>(execution_context);
		}

		os::execution_context<
			typename Config::thread_id_t,
			typename Config::process_id_t
		> execution_context{};
	};
}