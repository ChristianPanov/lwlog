#pragma once

#include <string>
#include <vector>

namespace lwlog::details
{
	struct chunk_t
	{
		chunk_t() = default;
		chunk_t(std::size_t size);
		void store(std::string_view data);
		bool is_full() const;
		std::string& data();

	private:
		std::size_t m_size{ 0 };
		std::size_t m_elements{ 0 };
		std::string m_chunk_buffer;
	};

	class conjugate_memory_buffer
	{
	public:
		conjugate_memory_buffer() = default;
		conjugate_memory_buffer(std::size_t chunk_size, std::size_t chunks);
		void store(std::string_view data);
		std::string output(std::size_t pos);
		std::size_t chunks() const;

	private:
		std::size_t m_pos{ 0 };
		std::size_t m_chunks{ 0 };
		std::vector<chunk_t> m_chunk_buffer;
	};
}