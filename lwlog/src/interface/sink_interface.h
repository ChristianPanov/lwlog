#pragma once

namespace lwlog::interface
{
	class sink
	{
	public:
		virtual ~sink() = default;

	public:
		virtual void sink_it(const details::log_message&) = 0;

	public:
		virtual void set_pattern(std::string_view) = 0;
		virtual void add_attribute(details::flag_pair, details::attrib_value) = 0;
		virtual void set_level_filter(level) = 0;
		virtual bool should_sink(level) const = 0;
		virtual details::pattern& pattern() = 0;
	};
}

namespace lwlog
{
	using sink_ptr = std::shared_ptr<interface::sink>;
	using sink_list = std::initializer_list<sink_ptr>;
}