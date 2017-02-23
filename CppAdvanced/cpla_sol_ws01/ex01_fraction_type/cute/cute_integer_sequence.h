/*********************************************************************************
 * This file is part of CUTE.
 *
 * CUTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CUTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CUTE.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2016 Felix Morgner
 *
 *********************************************************************************/

#include "cute_determine_version.h"

#ifndef CUTE_INTEGER_SEQUENCE_H_
#define CUTE_INTEGER_SEQUENCE_H_

#ifdef USE_STD14
#include <utility>
namespace cute {
	using std::index_sequence;
	using std::index_sequence_for;
}
#else
#include <cstdint>
namespace cute {
	namespace do_not_use_this_namespace {
		template<typename IntType, IntType ...Ints>
		struct integer_sequence {
			using type = integer_sequence;
			using value_type = IntType;
			static constexpr std::size_t size() { return sizeof...(Ints); }
		};

		template<typename, typename, typename>
		struct flatten;

		template<typename IntType, IntType ...Lhs, IntType ...Rhs>
		struct flatten<IntType, integer_sequence<IntType, Lhs...>, integer_sequence<IntType, Rhs...>>
			: integer_sequence<IntType, Lhs..., (sizeof...(Lhs) + Rhs)...> {};

		template<typename IntType, std::size_t Last>
		struct make_integer_sequence;

		template<typename IntType>
		struct make_integer_sequence<IntType, 0>
			: integer_sequence<IntType>{};

		template<typename IntType>
		struct make_integer_sequence<IntType, 1>
			: integer_sequence<IntType, 0>{};

		template<typename IntType, std::size_t Last>
		struct make_integer_sequence
			: flatten<IntType, typename make_integer_sequence<IntType, Last / 2>::type,
			                   typename make_integer_sequence<IntType, Last - Last / 2>::type>::type {};

		template<std::size_t Last>
		using make_index_sequence = make_integer_sequence<std::size_t, Last>;
	}

	template<std::size_t ...Indices>
	using index_sequence = do_not_use_this_namespace::integer_sequence<std::size_t, Indices...>;

	template<typename ...Types>
	using index_sequence_for = do_not_use_this_namespace::make_index_sequence<sizeof...(Types)>;
}
#endif

#endif //CUTE_INTEGER_SEQUENCE_H_
