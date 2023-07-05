#include "attribute.h"

namespace lwlog::details
{
	attribute::attribute(std::string_view flag, attrib_value value, attrib_callback_t callback)
		: flag{ flag }
		, value{ value }
		, callback{ std::move(callback) }
	{}

	attribute::attribute(std::string_view flag, attrib_value value)
		: flag{ flag }
		, value{ value }
	{
		callback = [value]() -> const char* {
			switch (value.index())
			{
			case 0:	return std::to_string(std::get<0>(value).get()).data();
			case 1:	return std::to_string(std::get<1>(value).get()).data();
			case 2:	return std::to_string(std::get<2>(value).get()).data();
			case 3:	return std::get<3>(value).get().data();
			case 4:	return std::get<4>(value).get().data();
			}
		};
	}
}