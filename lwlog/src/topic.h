#pragma once

#include <stack>
#include <string_view>

namespace lwlog::details
{
	class topic_registry
	{
	public:
		static void push(std::string_view topic);
		static void pop();
		static std::string_view current_topic();

	private:
		static inline std::stack<std::string_view> m_topics{ { "GLOBAL" } };
	};

	inline void topic_registry::push(std::string_view topic)	{ m_topics.push(topic); }
	inline void topic_registry::pop()							{ m_topics.pop(); }
	inline std::string_view topic_registry::current_topic()		{ return m_topics.top(); }
}