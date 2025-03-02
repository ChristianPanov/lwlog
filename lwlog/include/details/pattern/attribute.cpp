#include "attribute.h"

namespace lwlog::details
{
	attribute::attribute(std::string_view flag, attrib_value value, const attrib_callback_t& callback)
		: flag{ flag }
		, value{ value }
		, value_conv_callback{ callback }
	{}

	attribute::attribute(std::string_view flag, attrib_value value)
		: flag{ flag }
		, value{ value }
	{
		value_conv_callback = [value](char* buffer, std::size_t size) {
			switch (value.index())
			{
			case 0:	convert_to_chars(buffer, size, std::get<0>(value).get()); break;
			case 1:	convert_to_chars(buffer, size, std::get<1>(value).get()); break;
			case 2:	convert_to_chars(buffer, size, std::get<2>(value).get()); break;
			case 3:	convert_to_chars(buffer, size, std::get<3>(value).get()); break;
			case 4:	convert_to_chars(buffer, size, std::get<4>(value).get()); break;
			}
		};
	}
}