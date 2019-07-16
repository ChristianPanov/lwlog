#pragma once

#include <string_view>

#include "utilities.h"
#include "core.h"

class LWLOG_API dispatcher final
{
private:
	dispatcher() {}

public:
	dispatcher(const dispatcher&) = delete;
	dispatcher(dispatcher&&) = delete;
	dispatcher& operator=(const dispatcher&) = delete;
	dispatcher& operator=(dispatcher&&) = delete;

	void dispatch(std::string message);

	static dispatcher& instance()
	{
		static dispatcher s_instance;
		return s_instance;
	}
};