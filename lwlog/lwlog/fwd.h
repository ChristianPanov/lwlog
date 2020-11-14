#pragma once

namespace std
{
	template <class _Ty>
	class shared_ptr;
}

namespace lwlog
{
	enum class sink_level;
}

namespace lwlog::sinks
{
	class sink;
	using sink_ptr = std::shared_ptr<sink>;
}

namespace lwlog::interface
{
	class logger;
	using logger_ptr = logger*;
}

namespace lwlog::details::formatter_primitives
{
	struct attribute_t;
}

namespace lwlog::details
{
	using attribute_t = formatter_primitives::attribute_t;
}
