#pragma once

#include <cstdint>

namespace lwlog
{
	enum class level : std::uint8_t;
}

namespace lwlog::sinks
{
	template<bool EnableAnsiColors, typename ThreadingPolicy>
	class sink;
}

namespace lwlog::interface
{
	class logger;
	class sink;
}

namespace lwlog::details
{
	struct formatter;
	struct flag_pair;
	struct source_meta;
}