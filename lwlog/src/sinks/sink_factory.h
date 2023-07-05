#pragma once

namespace lwlog::sinks
{
	template<typename Sink>
	class sink_factory
	{
	public:
		template<typename... SinkParams>
		static constexpr sink_ptr request(SinkParams&&... params);
	};

	template<typename Sink>
	template<typename... SinkParams>
	[[nodiscard("This method is supposed to be initialized to a sink object")]]
	constexpr sink_ptr sink_factory<Sink>::request(SinkParams&&... params)
	{
		if constexpr (std::is_constructible_v<Sink, SinkParams...>)
		{
			return std::make_shared<Sink>(std::forward<SinkParams>(params)...);
		}
		else if constexpr (std::is_default_constructible_v<Sink>)
		{
			return std::make_shared<Sink>();
		}
		return sink_ptr{};
	}
}