#pragma once

class NonCopyable
{
	NonCopyable() = default;
	NonCopyable& operator=(NonCopyable&&) = delete;
	NonCopyable(const NonCopyable&) = delete;
};