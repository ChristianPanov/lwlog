#pragma once

#include "lwlog/fwd.h"

namespace lwlog::primitives
{
	using attribute_t	= details::formatter_primitives::attribute_t;
	using sink_ptr		= std::shared_ptr<interface::sink>;
	using sink_list		= std::initializer_list<sink_ptr>;
	using logger_ptr	= interface::logger*;
}
