#include <locale>
#include <algorithm>

#include "color_compiler.h"
#include "details/color.h"

namespace lwlog::details
{
	std::unordered_map<std::string_view, const char*> color_compiler::m_data =
	{
		{"^black^",			color::foreground_black()},		{"^br_black^",		color::foreground_br_black()},
		{"^red^",			color::foreground_red()},		{"^br_red^",		color::foreground_br_red()},
		{"^green^",			color::foreground_green()},		{"^br_green^",		color::foreground_br_green()},
		{"^yellow^",		color::foreground_yellow()},	{"^br_yellow^",		color::foreground_br_yellow()},
		{"^blue^",			color::foreground_blue()},		{"^br_blue^",		color::foreground_br_blue()},
		{"^magenta^",		color::foreground_magenta()},	{"^br_magenta^",	color::foreground_br_magenta()},
		{"^cyan^",			color::foreground_cyan()}, 		{"^br_cyan^",		color::foreground_br_cyan()},
		{"^white^",			color::foreground_white()},		{"^br_white^",		color::foreground_br_white()},

		{"^bg_black^",		color::background_black()},		{"^bg_br_black^",	color::background_br_black()},
		{"^bg_red^",		color::background_red()},		{"^bg_br_red^",		color::background_br_red()},
		{"^bg_green^",		color::background_green()},		{"^bg_br_green^",	color::background_br_green()},
		{"^bg_yellow^",		color::background_yellow()},	{"^bg_br_yellow^",	color::background_br_yellow()},
		{"^bg_blue^",		color::background_blue()},		{"^bg_br_blue^",	color::background_br_blue()},
		{"^bg_magenta^",	color::background_magenta()},	{"^bg_br_magenta^", color::background_br_magenta()},
		{"^bg_cyan^",		color::background_cyan()},		{"^bg_br_cyan^",	color::background_br_cyan()},
		{"^bg_white^",		color::background_white()},		{"^bg_br_white^",	color::background_br_white()}
	};

	void color_compiler::compile(std::string& str)
	{
		if (strstr(str.data(), "^"))
		{
			terminate_scopes(str);
			compile_basic(str);
			compile_rgb(str);
		}
	}

	void color_compiler::drop_flags(std::string& str)
	{
		while (strstr(str.data(), "^"))
		{
			std::size_t first_pos = str.find_first_of('^');
			std::size_t last_pos = str.find('^', first_pos + 1);
			str.erase(first_pos, last_pos - first_pos + 1);
		}
	}

	void color_compiler::compile_rgb(std::string& str)
	{
		for (const auto& flag : parse_rgb_flags(str))
		{
			while (strstr(str.data(), flag.data()))
			{
				str.replace(str.find(flag), flag.length(), to_ansiec(flag.data()));
			}
		}
	}

	void color_compiler::compile_basic(std::string& str)
	{
		for (const auto& [key, value] : m_data)
		{
			while (strstr(str.data(), key.data()))
			{
				str.replace(str.find(key), key.length(), value);
			}
		}
	}

	void color_compiler::terminate_scopes(std::string& str)
	{
		while (strstr(str.data(), "^reset^"))
		{
			str.replace(str.find("^reset^"), 7, color::reset());
		}
	}

	std::vector<std::string> color_compiler::parse_rgb_flags(const std::string& str)
	{
		std::vector<std::string> buff;
		std::size_t pos = str.find("^", 0);
		while (pos != std::string::npos)
		{
			if (std::isdigit(str[pos + 1]))
			{
				std::size_t end_pos = str.find("^", pos + 1);
				buff.push_back(str.substr(pos, end_pos - pos + 1));
				pos = str.find("^", end_pos + 1);
			}
			else pos = str.find("^", pos + 1);
		}
		return buff;
	}

	std::string_view color_compiler::to_ansiec(const std::string& flag)
	{
		std::string stripped = flag.substr(1, flag.size() - 2);
		std::string ansiec = "\u001b[38;2;" + stripped + "m";
		std::replace(ansiec.begin(), ansiec.end(), ':', ';');
		return ansiec;
	}
}