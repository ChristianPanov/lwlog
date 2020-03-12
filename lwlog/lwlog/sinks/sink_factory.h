#pragma once

#include <type_traits>
#include <memory>

#include "../core.h"
#include "sink.h"

namespace lwlog::sinks
{
	template<typename SinkPolicy>
	class LWLOG_API sink_factory
	{
	public:
		template <typename ... SinkParams>
		static std::shared_ptr<sink> request(SinkParams&& ... params);
	};

	template<typename SinkPolicy>
	template<typename ...SinkParams>
	std::shared_ptr<sink> sink_factory<SinkPolicy>::request(SinkParams&& ...params)
	{
		if constexpr (std::is_constructible<SinkPolicy, SinkParams...>::value)
		{
			return std::make_shared<SinkPolicy>(std::forward<SinkParams>(params)...);
		}
		else if constexpr (std::is_default_constructible<SinkPolicy>::value)
		{
			return std::make_shared<SinkPolicy>();
		}
	}
}