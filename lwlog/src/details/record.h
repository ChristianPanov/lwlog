#pragma once

#include "source_meta.h"
#include "os/datetime.h"
#include "os/os.h"

namespace lwlog::details
{
	struct record
	{
		record() = default;
		record(std::string_view message, level t_level, const source_meta& meta)
			: message{ message }
			, level{ t_level }
			, meta{ meta }
		{}

		std::string_view		message;
		level					level;
		source_meta				meta;
		os::time_point			time_point{};
		os::execution_context	execution_context{};
	};
}