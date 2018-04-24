#ifndef SRC__SCOPE_GUARD_COMMON_H_
#define SRC__SCOPE_GUARD_COMMON_H_
/*
 * MIT License

Copyright (c) 2016/2017 Eric Niebler, adapted by Peter Sommerlad

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
#include <utility>

#include <functional>

namespace std{
namespace experimental{
// contribution by (c) Eric Niebler 2016, adapted by (c) 2017 Peter Sommerlad
namespace detail {
namespace hidden{

// should this helper be standardized? // write testcase where recognizable.
template<typename T>
constexpr std::conditional_t<
    std::is_nothrow_move_assignable_v<T>,
    T &&,
    T const &>
_move_assign_if_noexcept(T &x) noexcept
{
    return std::move(x);
}
}
template<typename T>
class _box
{
    T value;
    _box(T const &t) noexcept(noexcept(T(t)))
      : value(t)
    {}
    _box(T &&t) noexcept(noexcept(T(std::move_if_noexcept(t))))
      : value(std::move_if_noexcept(t))
    {}

public:
    template<typename TT, typename GUARD,
        typename = std::enable_if_t<std::is_constructible_v<T, TT>>>
    explicit _box(TT &&t, GUARD &&guard) noexcept(noexcept(_box(std::forward<TT>(t))))
      : _box(std::forward<TT>(t))
    {
        guard.release();
    }
    T &get() noexcept
    {
        return value;
    }
    T const &get() const noexcept
    {
        return value;
    }
    T &&move() noexcept
    {
        return std::move(value);
    }
    void reset(T const &t) noexcept(noexcept(value = t))
    {
        value = t;
    }
    void reset(T &&t) noexcept(noexcept(value = hidden::_move_assign_if_noexcept(t)))
    {
        value = hidden::_move_assign_if_noexcept(t);
    }

};

template<typename T>
class _box<T &>
{
    std::reference_wrapper<T> value;
public:
    template<typename TT, typename GUARD,
        typename = std::enable_if_t<std::is_convertible_v<TT, T &>>>
    _box(TT &&t, GUARD &&guard) noexcept(noexcept(static_cast<T &>(t)))
      : value(static_cast<T &>(t))
    {
        guard.release();
    }
    T &get() const noexcept
    {
        return value.get();
    }
    T &move() const noexcept
    {
        return get();
    }
    void reset(T &t) noexcept
    {
        value = std::ref(t);
    }
};

}}}


#endif /* SRC__SCOPE_GUARD_COMMON_H_ */
