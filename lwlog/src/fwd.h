#pragma once

namespace lwlog
{
	enum class level : std::uint8_t;
}

namespace lwlog::sinks
{
	template<typename ColorPolicy, typename ThreadingPolicy>
	class sink;
}

namespace lwlog::interface
{
	class logger;
	class sink;
}

namespace lwlog::details
{
	struct flag_pair;
	struct source_meta;
}