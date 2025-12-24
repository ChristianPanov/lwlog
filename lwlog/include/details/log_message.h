#pragma once

#include "details/source_meta.h"

namespace lwlog::details
{
	struct log_message
	{
		template<typename T>
		log_message(T msg, const source_meta& meta = source_meta::current())
			: message{ msg }
			, meta{ meta }
		{}

		std::string_view message{};
		const source_meta meta{};
	};
}