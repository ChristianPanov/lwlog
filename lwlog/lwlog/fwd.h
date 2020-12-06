#pragma once

namespace std
{
	template<class _Ty>
	class shared_ptr;
	template<class _Ty, class _Alloc = allocator<_Ty>>
	class vector;
}

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

namespace lwlog::details::formatter_primitives
{
	struct attribute_t;
}

namespace lwlog::primitives
{
	using attribute_t = details::formatter_primitives::attribute_t;
	using sink_ptr = std::shared_ptr<interface::sink>;
	using logger_ptr = interface::logger*;
}