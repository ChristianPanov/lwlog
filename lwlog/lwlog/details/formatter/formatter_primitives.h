#pragma once

namespace lwlog::details::formatter_primitives
{
	struct attribute_key
	{
		std::string verbose;
		std::string shortened;
		bool operator==(const attribute_key& other) const noexcept;
	};

	struct attribute_t
	{
		std::string verbose;
		std::string shortened;
		std::string value;
	};

	struct attribute_key_hasher
	{
		std::size_t operator()(const attribute_key& key) const;
	};

	inline bool attribute_key::operator==(const attribute_key& other) const noexcept
	{
		return ((verbose == other.verbose) || (shortened == other.shortened) ||
			(verbose == other.shortened) || (shortened == other.verbose));
	}

	inline std::size_t attribute_key_hasher::operator()(const attribute_key& key) const
	{
		return std::hash<std::string>{}(key.verbose) ^ std::hash<std::string>{}(key.shortened);
	}
}