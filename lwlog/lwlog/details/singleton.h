#pragma once

class singleton
{
public:
	singleton() = default;
	singleton(const singleton&) = delete;
	singleton(singleton&&) = delete;
	singleton& operator=(const singleton&) = delete;
	singleton& operator=(singleton&&) = delete;
};