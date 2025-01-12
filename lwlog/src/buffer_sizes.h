#pragma once

#include <cstddef>

namespace lwlog
{
	template<std::size_t BufferSize> struct pattern_buffer_size { static constexpr std::size_t Size{ BufferSize }; };
	template<std::size_t BufferSize> struct message_buffer_size { static constexpr std::size_t Size{ BufferSize }; };
	template<std::size_t BufferSize> struct padding_buffer_size { static constexpr std::size_t Size{ BufferSize }; };
	template<std::size_t BufferSize> struct conv_buffer_size { static constexpr std::size_t Size{ BufferSize }; };

	template<
		typename PatternBufferSize,
		typename MessageBufferSize,
		typename PaddingBufferSize,
		typename ConvBufferSize
	> struct memory_buffer_sizes
	{
		static_assert(std::is_same_v<PatternBufferSize, pattern_buffer_size<PatternBufferSize::Size>>,
			"PatternBufferSize must be of type pattern_buffer_size.");
		static_assert(std::is_same_v<MessageBufferSize, message_buffer_size<MessageBufferSize::Size>>,
			"MessageBufferSize must be of type message_buffer_size.");
		static_assert(std::is_same_v<PaddingBufferSize, padding_buffer_size<PaddingBufferSize::Size>>,
			"PaddingBufferSize must be of type padding_buffer_size.");
		static_assert(std::is_same_v<ConvBufferSize, conv_buffer_size<ConvBufferSize::Size>>,
			"ConvBufferSize must be of type conv_buffer_size.");

		static constexpr std::size_t cached_pattern{ PatternBufferSize::Size };
		static constexpr std::size_t pattern{ PatternBufferSize::Size };
		static constexpr std::size_t message{ MessageBufferSize::Size };
		static constexpr std::size_t padding{ PaddingBufferSize::Size };
		static constexpr std::size_t conversion{ ConvBufferSize::Size };
	};

	using default_pattern_buffer_size = pattern_buffer_size<512>;
	using default_message_buffer_size = message_buffer_size<256>;
	using default_padding_buffer_size = padding_buffer_size<24>;
	using default_conv_buffer_size = conv_buffer_size<64>;

	using default_memory_buffer_sizes = memory_buffer_sizes<
		default_pattern_buffer_size,
		default_message_buffer_size,
		default_padding_buffer_size,
		default_conv_buffer_size
	>;
}