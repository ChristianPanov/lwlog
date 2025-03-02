#pragma once

namespace lwlog::interface
{
	template<typename Config, typename BufferLimits>
	class sink
	{
	public:
		virtual ~sink() = default;

	public:
		virtual void sink_it(const details::record<Config, BufferLimits>&) = 0;

	public:
		virtual bool should_sink(level) const = 0;
		virtual void set_level_filter(level) = 0;
		virtual void set_pattern(std::string_view) = 0;
		virtual void add_attribute(std::string_view, details::attrib_value) = 0;
		virtual void add_attribute(std::string_view, details::attrib_value, const details::attrib_callback_t&) = 0;
	};
}

namespace lwlog
{
	template<typename Config, typename BufferLimits>
	using sink_ptr = std::shared_ptr<interface::sink<Config, BufferLimits>>;

	template<typename Config, typename BufferLimits>
	using sink_list = std::initializer_list<sink_ptr<Config, BufferLimits>>;
}