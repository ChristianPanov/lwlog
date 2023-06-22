#pragma once

namespace lwlog::details
{
	struct formatter
	{
		virtual ~formatter() = default;
		virtual void format(std::string&, const record&) const = 0;

		template<typename T> static void format_attribute(std::string& pattern, const flag_pair& flags, T value);
		template<typename T> static void format_attribute(std::string& pattern, std::string_view flag, T value);

		template<> static void format_attribute<void*>(std::string&, const flag_pair&, void*);
		template<> static void format_attribute<void*>(std::string&, std::string_view, void*);
	};
}

#include "formatter_impl.h"