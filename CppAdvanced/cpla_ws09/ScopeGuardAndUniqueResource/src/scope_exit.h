#ifndef SCOPE_EXIT_H_
#define SCOPE_EXIT_H_
/*
 * MIT License

Copyright (c) 2016/2017 Eric Niebler, slightly adapted by Peter Sommerlad

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
#include "_scope_guard_common.h"
#include <utility>
#include <limits> // for maxint
// modeled slightly after Andrescu's talk and article(s)


namespace std {
namespace experimental {
// new policy-based exception proof design by Eric Niebler
namespace detail{

struct on_exit_policy
{
    bool execute_{ true };

    void release() noexcept
    {
        execute_ = false;
    }

    bool should_execute() const noexcept
    {
        return execute_;
    }
};


struct on_fail_policy
{
    int ec_ { std::uncaught_exceptions() };

    void release() noexcept
    {
        ec_ = std::numeric_limits<int>::max();
    }

    bool should_execute() const noexcept
    {
        return ec_ < std::uncaught_exceptions();
    }
};

struct on_success_policy
{
    int ec_ { std::uncaught_exceptions() };

    void release() noexcept
    {
        ec_ = -1;
    }

    bool should_execute() const noexcept
    {
        return ec_ >= std::uncaught_exceptions() ;
    }
};
}
template<class EF, class Policy = detail::on_exit_policy>
struct basic_scope_exit;

//PS: It would be nice if just the following would work in C++17
//PS: however, we need a real class for template argument deduction
//PS: and a deduction guide, because the ctors are partially instantiated
//template<class EF>
//using scope_exit = basic_scope_exit<EF, detail::on_exit_policy>;

template<class EF>
struct scope_exit : basic_scope_exit<EF, detail::on_exit_policy>{
	using basic_scope_exit<EF, detail::on_exit_policy>::basic_scope_exit;
};

template <class EF>
scope_exit(EF) -> scope_exit<EF>;

//template<class EF>
//using scope_fail = basic_scope_exit<EF, detail::on_fail_policy>;

template<class EF>
struct scope_fail : basic_scope_exit<EF, detail::on_fail_policy>{
	using basic_scope_exit<EF, detail::on_fail_policy>::basic_scope_exit;
};

template <class EF>
scope_fail(EF) -> scope_fail<EF>;

//template<class EF>
//using scope_success = basic_scope_exit<EF, detail::on_success_policy>;

template<class EF>
struct scope_success : basic_scope_exit<EF, detail::on_success_policy>{
	using basic_scope_exit<EF,detail::on_success_policy>::basic_scope_exit;
};

template <class EF>
scope_success(EF) -> scope_success<EF>;



namespace detail{
// DETAIL:
template<class Policy, class EF>
auto _make_guard(EF &&ef)
{
    return basic_scope_exit<std::decay_t<EF>, Policy>(std::forward<EF>(ef));
}
struct _empty_scope_exit
{
    void release() const noexcept
    {}
};

}

// Requires: EF is Callable
// Requires: EF is nothrow MoveConstructible OR CopyConstructible
template<class EF, class Policy /*= on_exit_policy*/>
class basic_scope_exit :  Policy
{
	static_assert(std::is_invocable_v<EF>,"scope guard must be callable");
    detail::_box<EF> exit_function;

	static auto _make_failsafe(std::true_type, const void *)
    {
        return detail::_empty_scope_exit{};
    }
    template<typename Fn>
    static auto _make_failsafe(std::false_type, Fn *fn)
    {
        return basic_scope_exit<Fn &, Policy>(*fn);
    }
    template<typename EFP>
    using _ctor_from = std::is_constructible<detail::_box<EF>, EFP, detail::_empty_scope_exit>;
    template<typename EFP>
    using _noexcept_ctor_from = std::bool_constant<noexcept(detail::_box<EF>(std::declval<EFP>(), detail::_empty_scope_exit{}))>;
public:
    template<typename EFP, typename = std::enable_if_t<_ctor_from<EFP>::value>>
    explicit basic_scope_exit(EFP &&ef) noexcept(_noexcept_ctor_from<EFP>::value)
      : exit_function(std::forward<EFP>( ef), _make_failsafe(_noexcept_ctor_from<EFP>{}, &ef))
    {}
    basic_scope_exit(basic_scope_exit &&that) noexcept(noexcept(detail::_box<EF>(that.exit_function.move(), that)))
      : Policy(that), exit_function(that.exit_function.move(), that)
    {}
    ~basic_scope_exit() noexcept(noexcept(exit_function.get()()))
    {
        if(this->should_execute())
            exit_function.get()();
    }
	basic_scope_exit(const basic_scope_exit &) = delete;
	basic_scope_exit &operator=(const basic_scope_exit &) = delete;
    basic_scope_exit &operator=(basic_scope_exit &&) = delete;

    using Policy::release;

};

template<class EF, class Policy>
void swap(basic_scope_exit<EF, Policy> &, basic_scope_exit<EF, Policy> &) = delete;


// end (c) Eric Niebler

}
}

#endif /* SCOPE_EXIT_H_ */
