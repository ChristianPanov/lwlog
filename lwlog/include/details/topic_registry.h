#pragma once

#include <cstdint>
#include <stack>
#include <string>
#include <vector>

namespace lwlog::details
{
	class topic_registry
	{
	public:
		void set_separator(const char* separator);
		void start_topic(const char* topic);
		void end_topic();

		std::uint8_t topic_index() const;
		const std::vector<std::string_view>& topics() const;

		std::string full_topic(std::uint8_t topic_index) const;

	private:
		std::vector<std::string_view> m_topics;
		const char* m_separator;
		std::uint8_t m_topic_index{ 0 };
	};
}