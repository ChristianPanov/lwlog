#pragma once

#include <cstdint>
#include <string_view>

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
		constexpr source_meta(std::uint32_t line, 
			const char* const file, 
			const char* const function);

	public:
		static constexpr source_meta current(
			std::uint32_t line = BUILTIN_LINE, 
			const char* const file = BUILTIN_FILE,
			const char* const function = BUILTIN_FUNCTION);

		constexpr std::uint32_t	line() const;
		constexpr const char* file_path() const;
		constexpr const char* file_name() const;
		constexpr const char* function_name() const;

	private:
		std::uint32_t m_line{};
		const char* m_file{};
		const char* m_function{};
	};
}

#include "source_meta_impl.h"