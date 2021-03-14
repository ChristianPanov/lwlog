#pragma once

#include "fwd.h"

namespace lwlog::primitives
{
	using sink_ptr = std::shared_ptr<interface::sink>;
	using sink_list	= std::initializer_list<sink_ptr>;
	using logger_ptr = interface::logger*;
}