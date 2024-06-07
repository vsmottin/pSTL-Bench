#pragma once

#ifndef PSTL_ELEM_T
// If PSTL_ELEM_T is not defined, default to double
#define PSTL_ELEM_T double
#endif

namespace pstl
{
	using elem_t = PSTL_ELEM_T;
} // namespace pstl
