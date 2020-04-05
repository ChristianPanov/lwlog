#pragma once

#include "core.h"
#include "fwd.h"

namespace lwlog::interface
{
	class LWLOG_API level_visibility
	{
	public:
		virtual ~level_visibility() = default;
		virtual void set_level_visibility(std::initializer_list<sink_level>) = 0;
	};
}