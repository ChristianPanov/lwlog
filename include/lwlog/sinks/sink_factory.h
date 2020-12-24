#pragma once

#include <type_traits>
#include <memory>

#include "lwlog/fwd.h"

namespace lwlog::sinks
{
	template<typename Sink>
	class sink_factory
	{
	public:
		template <typename... SinkParams>
		static primitives::sink_ptr request(SinkParams&&... params);
	};

	template<typename Sink>
	template<typename... SinkParams>
	[[nodiscard("This method is supposed to be initialized to a sink object")]]
	primitives::sink_ptr sink_factory<Sink>::request(SinkParams&&... params)
	{
		if constexpr (std::is_constructible<Sink, SinkParams...>::value)
		{
			return std::make_shared<Sink>(std::forward<SinkParams>(params)...);
		}
		else if constexpr (std::is_default_constructible<Sink>::value)
		{
			return std::make_shared<Sink>();
		}
		return primitives::sink_ptr{};
	}
}
