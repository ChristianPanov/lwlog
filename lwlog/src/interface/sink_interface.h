#pragma once

namespace lwlog::interface
{
	class sink
	{
	public:
		virtual ~sink() = default;

	public:
		virtual void sink_it(std::string_view) = 0;

	public:
		virtual void set_pattern(std::string_view) = 0;
		virtual void set_level_filter(level) = 0;
		virtual bool should_sink(level) const = 0;
		virtual details::pattern& pattern() = 0;
	};
}