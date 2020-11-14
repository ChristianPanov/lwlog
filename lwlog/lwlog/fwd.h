#pragma once

namespace std
{
	template<class _Ty>
	class shared_ptr;
}

namespace lwlog
{
	enum class sink_level;
}

namespace lwlog::sinks
{
	class sink;
}

namespace lwlog::interface
{
	class logger;
}

namespace lwlog::details::formatter_primitives
{
	struct attribute_t;
}

namespace lwlog::primitives
{
	using attribute_t = details::formatter_primitives::attribute_t;
	using sink_ptr = std::shared_ptr<sinks::sink>;
	using logger_ptr = interface::logger*;
}