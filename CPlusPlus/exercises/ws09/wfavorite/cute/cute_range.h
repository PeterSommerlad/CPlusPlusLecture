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
 * Copyright 2015 Peter Sommerlad
 *
 *********************************************************************************/
#ifndef CUTE_RANGE_H_
#define CUTE_RANGE_H_

#include <iterator>
#include <algorithm>
#ifdef USE_STD11
#include <initializer_list>
#endif
namespace cute{
	template <typename ForwardIterator>
	struct range {
		typedef ForwardIterator const_iterator; // for to_stream dispatch
		typedef typename std::iterator_traits<const_iterator>::value_type value_type;
		const_iterator const b;
		const_iterator const e;
		range(ForwardIterator bb,ForwardIterator ee):b(bb),e(ee){}
		const_iterator begin() const { return b; }
		const_iterator end() const { return e; }
		template <typename RangeOrContainer>
		bool operator==(RangeOrContainer const &other) const{
#if __cplusplus >= 201402L
			return std::equal(begin(),end(),other.begin(),other.end());
#else
			if (std::distance(begin(),end())==std::distance(other.begin(),other.end())){
				return std::equal(begin(),end(),other.begin());
			}
			return false;
#endif
		}
	};
	template <typename ForwardIterator>
	range<ForwardIterator> make_range(ForwardIterator b, ForwardIterator e){
		return range<ForwardIterator>(b,e);
	}

#ifdef USE_STD11
	template <typename Value>
	range<typename std::initializer_list<Value>::iterator>
	make_range(std::initializer_list<Value> const &il){
		return range<typename std::initializer_list<Value>::iterator>(il.begin(),il.end());
	}
#endif
}

#endif /* CUTE_RANGE_H_ */
