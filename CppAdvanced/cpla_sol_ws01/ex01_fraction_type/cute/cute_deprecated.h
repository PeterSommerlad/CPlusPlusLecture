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
 * Copyright 2016 Mario Meili, Felix Morgner
 *
 *********************************************************************************/

#ifndef CUTE_DEPRECATED_H_
#define CUTE_DEPRECATED_H_

#if __cplusplus >= 201402L
#define DEPRECATE(orig, repl) [[deprecated ("Use "#repl" instead.")]] inline void orig() {}
#elif defined(__GNUG__)
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#if GCC_VERSION >= 40500 || defined(__clang__)
#define DEPRECATE(orig, repl) __attribute__((deprecated("Use "#repl" instead."))) inline void orig() {}
#else
#define DEPRECATE(orig, repl) __attribute__((deprecated)) inline void orig() {}
#endif
#elif defined(_MSC_VER)
#define DEPRECATE(orig, repl) __declspec(deprecated(#orig" is deprecated, use "#repl" instead.")) inline void orig() {}
#endif

#ifdef DEPRECATE
#define DEPRECATED(name) name()
#endif

#endif /*CUTE_DEPRECATED_H_*/
