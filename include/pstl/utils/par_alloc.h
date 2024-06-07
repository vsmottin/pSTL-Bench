#pragma once

// Adapted from:
//  https://github.com/STEllAR-GROUP/hpx/blob/fe048ee6e01abedad0a60a0fdc204116419871c3/libs/core/compute_local/include/hpx/compute_local/host/numa_allocator.hpp
//  COPYRIGHT FROM THE ROOT OF THIS CLASS CAN BE FOUND BELOW
//  Copyright (c) 2015 Thomas Heller
//  Copyright (c) 2015-2022 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm>
#include <cstddef>
#include <execution>
#include <limits>

#if defined(PSTL_BENCH_USE_GNU)
#include <parallel/algorithm>
#endif

///////////////////////////////////////////////////////////////////////////////
//
// WARNING: This class is highly experimental, it might not do what you expect
//
///////////////////////////////////////////////////////////////////////////////

namespace pstl
{
	///////////////////////////////////////////////////////////////////////////
	template<typename T, typename Policy>
	class par_alloc
	{
		using POLICY_BASE_TYPE = std::remove_cv_t<std::remove_reference_t<Policy>>;
		using IS_SEQ           = typename std::is_same<POLICY_BASE_TYPE, std::execution::sequenced_policy>;

	public:
		// typedefs
		using value_type      = T;
		using pointer         = value_type *;
		using const_pointer   = value_type const *;
		using reference       = value_type &;
		using const_reference = value_type const &;
		using size_type       = std::size_t;
		using difference_type = std::ptrdiff_t;

		// convert an allocator<T> to allocator<U>
		template<typename U>
		struct rebind
		{
			using other = par_alloc<U, Policy>;
		};

		explicit par_alloc(Policy const & execution_policy) : execution_policy(execution_policy) {}

		par_alloc(par_alloc const & rhs) : execution_policy(rhs.execution_policy) {}

		par_alloc & operator=(par_alloc const & rhs) = delete;

		template<typename U>
		explicit par_alloc(par_alloc<U, Policy> const & rhs) : execution_policy(rhs.execution_policy)
		{}

		// address
		static pointer address(reference r) { return &r; }

		static const_pointer address(const_reference r) { return &r; }

		// memory allocation
		pointer allocate(size_type cnt, void const * = nullptr)
		{
			// allocate memory
			auto p = static_cast<pointer>(::operator new(cnt * sizeof(T)));

			// early exit when we use std::execution::seq because it would be waste of time to seq touch it
			// this already happens by default since vector gets 0 initialized
			if constexpr (IS_SEQ::value) { return p; }

			pointer begin = p;
			pointer end   = begin + cnt;

			// touch first byte of every object using the given strategy
#if defined(PSTL_BENCH_USE_GNU)
			__gnu_parallel::for_each(begin, end, [](T & val) { *reinterpret_cast<char *>(&val) = 0; });
#else
			std::for_each(execution_policy, begin, end, [](T & val) { *reinterpret_cast<char *>(&val) = 0; });
#endif


			// return the overall memory block
			return p;
		}

		void deallocate(pointer p, [[maybe_unused]] size_type cnt) noexcept { ::operator delete(p); }

		// size
		static size_type max_size() noexcept { return (std::numeric_limits<size_type>::max)() / sizeof(T); }

		static void destroy(pointer p) noexcept { p->~T(); }

		friend constexpr bool operator==(par_alloc const &, par_alloc const &) noexcept { return true; }

		friend constexpr bool operator!=(par_alloc const & l, par_alloc const & r) noexcept { return l != r; }

	private:
		template<typename, typename>
		friend class par_alloc;

		Policy const & execution_policy;
	};
} // namespace pstl
