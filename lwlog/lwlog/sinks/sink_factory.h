#pragma once

#include <type_traits>
#include <memory>

#include "fwd.h"

namespace lwlog::sinks
{
	template<typename SinkPolicy>
	class sink_factory
	{
	public:
		template <typename ... SinkParams>
		static sink_ptr request(SinkParams&&... params);
	};

	template<typename SinkPolicy>
	template<typename ... SinkParams>
	sink_ptr sink_factory<SinkPolicy>::request(SinkParams&&... params)
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