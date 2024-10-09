#pragma once

#include <stack>
#include <string>

#include "configuration.h"

namespace lwlog::details
{
	struct topic_registry_base
	{
		virtual ~topic_registry_base() = default;

		virtual std::string_view current_topic() const = 0;
		virtual std::string full_topic() const = 0;
	};

	template<typename TopicPolicy>
	class topic_registry : public topic_registry_base {};

	template<>
	class topic_registry<enable_topics> : public topic_registry_base
	{
	public:
		void set_separator(std::string_view separator);
		void start_topic(std::string_view topic);
		void end_topic();

		std::string_view current_topic() const override;
		std::string full_topic() const override;

	private:
		std::string_view m_current_topic;
		std::string_view m_separator;
		std::vector<std::string_view> m_topics;
	};

	template<>
	struct topic_registry<disable_topics> : public topic_registry_base
	{
		void set_separator(std::string_view) const;
		void start_topic(std::string_view) const;
		void end_topic() const;

		std::string_view current_topic() const override;
		std::string full_topic() const override;
	};
}

#include "topic_registry_impl.h"