#pragma once

#include <cstddef>

namespace lwlog
{
	template<std::size_t Limit> struct pattern_limit	{ static constexpr std::size_t Value{ Limit }; };
	template<std::size_t Limit> struct message_limit	{ static constexpr std::size_t Value{ Limit }; };
	template<std::size_t Limit> struct argument_limit	{ static constexpr std::size_t Value{ Limit }; };
	template<std::size_t Limit> struct arg_count_limit	{ static constexpr std::size_t Value{ Limit }; };
	template<std::size_t Limit> struct padding_limit	{ static constexpr std::size_t Value{ Limit }; };
	template<std::size_t Limit> struct conv_limit		{ static constexpr std::size_t Value{ Limit }; };

	template<
		typename PatternLimit,
		typename MessageLimit,
		typename ArgumentLimit,
		typename ArgCountLimit,
		typename PaddingLimit,
		typename ConvLimit
	> struct memory_buffer_limits
	{
		static_assert(std::is_same_v<PatternLimit, pattern_limit<PatternLimit::Value>>,
			"PatternLimit must be of type pattern_limit.");
		static_assert(std::is_same_v<MessageLimit, message_limit<MessageLimit::Value>>,
			"MessageLimit must be of type message_limit.");
		static_assert(std::is_same_v<ArgumentLimit, argument_limit<ArgumentLimit::Value>>,
			"ArgumentLimit must be of type argument_limit.");
		static_assert(std::is_same_v<ArgCountLimit, arg_count_limit<ArgCountLimit::Value>>,
			"ArgCountLimit must be of type arg_count_limit.");
		static_assert(std::is_same_v<PaddingLimit, padding_limit<PaddingLimit::Value>>,
			"PaddingLimit must be of type padding_limit.");
		static_assert(std::is_same_v<ConvLimit, conv_limit<ConvLimit::Value>>,
			"ConvLimit must be of type conv_limit.");

		static constexpr std::size_t cached_pattern{ PatternLimit::Value };
		static constexpr std::size_t pattern{ PatternLimit::Value };
		static constexpr std::size_t message{ MessageLimit::Value };
		static constexpr std::size_t argument{ ArgumentLimit::Value };
		static constexpr std::size_t arg_count{ ArgCountLimit::Value };
		static constexpr std::size_t padding{ PaddingLimit::Value };
		static constexpr std::size_t conversion{ ConvLimit::Value };
	};

	using default_pattern_limit = pattern_limit<512>;
	using default_message_limit = message_limit<256>;
	using default_argument_limit = argument_limit<24>;
	using default_arg_count_limit = arg_count_limit<10>;
	using default_padding_limit = padding_limit<24>;
	using default_conv_limit = conv_limit<64>;

	using default_memory_buffer_limits = memory_buffer_limits<
		default_pattern_limit,
		default_message_limit,
		default_argument_limit,
		default_arg_count_limit,
		default_padding_limit,
		default_conv_limit
	>;
}