
#ifndef PSTL_BENCH_ELEM_T_H
#define PSTL_BENCH_ELEM_T_H

#ifndef PSTL_ELEM_T
// If PSTL_ELEM_T is not defined, default to float
#define PSTL_ELEM_T float
#endif

namespace pstl
{
	using elem_t = PSTL_ELEM_T;
} // namespace pstl

#endif //PSTL_BENCH_ELEM_T_H
