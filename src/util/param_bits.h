// Luanti
// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright (C) 2026 sfence <sfence.software@gmail.com>

#pragma once

#include <climits>
#if _MSC_VER
#include <intrin.h> // For popcnt
#endif

inline unsigned popcount(unsigned b)
{
#if _MSC_VER
	return __popcnt(b);
#else
	return __builtin_popcount(b);
#endif
}

template<typename T>
class ParamBits {
public:
	static_assert(static_cast<T>(-1) > static_cast<T>(0),
			"Param bits only work with unsigned integer types");

	ParamBits(): m_mask(0), m_offset(0) {}
	ParamBits(u8 width, u8 offset)
	{
		configure(width, offset);
	}
	ParamBits(const ParamBits&) = default;
	ParamBits& operator=(const ParamBits&) = default;

  inline void configure(u8 width, u8 offset)
  {
    // Truncate to the type width to avoid undefined behavior.
		unsigned bit_count = sizeof(T) * CHAR_BIT;
		offset = MYMIN(offset, bit_count);
		width = MYMIN(width, bit_count - offset);
		m_mask = ((width < bit_count ? 1 << width : 0) - 1) << (offset % bit_count);
		m_offset = offset % bit_count;
  }
  inline bool isValid() const { return m_mask != 0; }

	inline u8 getWidth() const { return popcount(m_mask); }
	inline u8 getOffset() const { return m_offset; }

	inline T get(T bits) const
	{
		return (bits & m_mask) >> m_offset;
	}

	inline T set(T bits, T value) const
	{
		bits &= ~m_mask;
		bits |= (value << m_offset) & m_mask;
		return bits;
	}

private:
	T m_mask;
	u8 m_offset;
};