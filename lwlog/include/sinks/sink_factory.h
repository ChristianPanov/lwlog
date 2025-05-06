#pragma once

namespace lwlog::sinks
{
	template<typename BufferLimits, typename Sink>
	class sink_factory
	{
	public:
		template<typename... SinkParams>
		static sink_ptr<BufferLimits> request(SinkParams&&... params);
	};

	template<typename BufferLimits, typename Sink>
	template<typename... SinkParams>
	[[nodiscard]] sink_ptr<BufferLimits> sink_factory<BufferLimits, Sink>::request(SinkParams&&... params)
	{
		if constexpr (std::is_constructible_v<Sink, SinkParams...>)
		{
			return std::make_shared<Sink>(std::forward<SinkParams>(params)...);
		}
		else if constexpr (std::is_default_constructible_v<Sink>)
		{
			return std::make_shared<Sink>();
		}
		return sink_ptr<BufferLimits>{};
	}
}