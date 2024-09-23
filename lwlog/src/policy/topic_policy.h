#pragma once

#include <stack>
#include <string>

#include "configuration.h"

namespace lwlog
{
	template<typename TopicPolicy>
	struct topic_registry {};

	template<>
	struct topic_registry<enable_topics>
	{
		using container = std::stack<std::string_view>;

		static void start_topic(std::string_view topic, container& registry);
		static void end_topic(container& registry);
		static std::string_view current_topic(container& registry)
		{
			return registry.top();
		}
	};

	template<>
	struct topic_registry<disable_topics>
	{
		using container = struct {};

		static void start_topic(std::string_view, container&);
		static void end_topic(container&);
		static std::string_view current_topic(container&)
		{
			return {};
		}
	};
}

#include "topic_policy_impl.h"