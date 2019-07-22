#pragma once

class NonMoveable
{
	NonMoveable() = default;
	NonMoveable& operator=(NonMoveable&&) = delete;
	NonMoveable(NonMoveable&&) = delete;
};