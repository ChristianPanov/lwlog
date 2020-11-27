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
	enum class sink_level : std::uint8_t;
}

namespace lwlog::sinks
{
	template<typename ColorPolicy>
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

namespace lwlog::details
{
	using attribute_buffer = std::vector<formatter_primitives::attribute_t>;
}

namespace lwlog::primitives
{
	using attribute_t = details::formatter_primitives::attribute_t;
	using sink_ptr = std::shared_ptr<interface::sink>;
	using logger_ptr = interface::logger*;
}