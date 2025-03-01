#pragma once

#include <stack>
#include <string>
#include <vector>

namespace lwlog::details
{
	class topic_registry
	{
	public:
		void set_separator(std::string_view separator);
		void start_topic(std::string_view topic);
		void end_topic();

		std::string_view current_topic() const;
		std::string full_topic() const;

	private:
		std::string_view m_current_topic;
		std::string_view m_separator;
		std::vector<std::string_view> m_topics;
	};
}