#pragma once

#if defined(_MSC_VER) && (_MSC_VER < 1929)
#define BUILTIN_LINE {}
#define BUILTIN_FILE {}
#define BUILTIN_FUNCTION {}
#else
#define BUILTIN_LINE __builtin_LINE()
#define BUILTIN_FILE __builtin_FILE()
#define BUILTIN_FUNCTION __builtin_FUNCTION()
#endif

namespace lwlog::details
{
	struct source_meta
	{
	public:
		constexpr source_meta() = default;

	public:
		static constexpr source_meta current(
			const std::uint32_t line = BUILTIN_LINE,
			std::string_view file = BUILTIN_FILE,
			std::string_view function = BUILTIN_FUNCTION)
		{
			source_meta meta;
			meta.m_line = line;
			meta.m_file = file;
			meta.m_function = function;
			return meta;
		}

		constexpr std::uint32_t line()				const { return m_line; }
		constexpr std::string_view file_name()		const { return m_file; }
		constexpr std::string_view function_name()	const { return m_function; }

	private:
		std::uint32_t m_line{};
		std::string_view m_file;
		std::string_view m_function;
	};
}