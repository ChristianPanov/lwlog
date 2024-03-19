#pragma once

namespace lwlog::details
{
	inline const std::unordered_map<std::string_view, std::string_view> color_data =
	{
		{ ".black(",			"\u001b[30m"	},
		{ ".grey(",				"\u001b[37m"	},
		{ ".red(",				"\u001b[31;1m"	},
		{ ".green(",			"\u001b[32;1m"	},
		{ ".yellow(",			"\u001b[33;1m"	},
		{ ".blue(",				"\u001b[34;1m"	},
		{ ".magenta(",			"\u001b[35;1m"	},
		{ ".cyan(",				"\u001b[36;1m"	},
		{ ".white(",			"\u001b[37;1m"	},

		{ ".dark_grey(",		"\u001b[30;1m"	},
		{ ".dark_red(",			"\u001b[31m"	},
		{ ".dark_green(",		"\u001b[32m"	},
		{ ".dark_yellow(",		"\u001b[33m"	},
		{ ".dark_blue(",		"\u001b[34m"	},
		{ ".dark_magenta(",		"\u001b[35m"	},
		{ ".dark_cyan(",		"\u001b[36m"	},

		{ ".bg_black(",			"\u001b[40m"	},
		{ ".bg_grey(",			"\u001b[47m"	},
		{ ".bg_red(",			"\u001b[41;1m"	},
		{ ".bg_green(",			"\u001b[42;1m"	},
		{ ".bg_yellow(",		"\u001b[43;1m"	},
		{ ".bg_blue(",			"\u001b[44;1m"	},
		{ ".bg_magenta(",		"\u001b[45;1m"	},
		{ ".bg_cyan(",			"\u001b[46;1m"	},
		{ ".bg_white(",			"\u001b[47;1m"	},

		{ ".bg_dark_grey(",		"\u001b[40;1m"	},
		{ ".bg_dark_red(",		"\u001b[41m"	},
		{ ".bg_dark_green(",	"\u001b[42m"	},
		{ ".bg_dark_yellow(",	"\u001b[43m"	},
		{ ".bg_dark_blue(",		"\u001b[44m"	},
		{ ".bg_dark_magenta(",	"\u001b[45m"	},
		{ ".bg_dark_cyan(",		"\u001b[46m"	}
	};
}