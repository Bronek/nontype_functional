#include "std23/constant_wrapper.hpp"
#include "std23/function_ref.h"
#include "std23/move_only_function.h"
#include <type_traits>

using namespace std23;

static constexpr struct foo_t final
{
    constexpr auto operator()(auto &&...args) const -> int
    {
        return (0 + ... + args);
    }
} foo = {};

static auto bar0() -> int;
static auto bar1() -> int;

auto main() -> int
{
    static_assert(foo() == 0);
    static_assert(foo(1) == 1);
    static_assert(foo(1, 2) == 3);
    static_assert(std::is_invocable_r_v<int, foo_t const, int>);
    static_assert(std::is_same_v<decltype(foo), foo_t const>);
    static_assert(std::is_same_v<decltype(cw<foo>)::value_type, foo_t>);
    function_ref<int(int)> fn(cw<foo>);
    return fn(bar0());
}

static constexpr struct baz_t final
{
    static constexpr int value = 1;

    constexpr operator int() const noexcept { return 12; }
} baz = {};

auto bar0() -> int
{
    constexpr auto fn0 = cw<foo>;
    static_assert(fn0() == 0);
    static_assert(fn0(baz) == 1);
    static_assert(fn0(baz, baz, baz) == 3);
    static_assert(fn0(baz, baz, baz) == cw<3>);

    move_only_function<int()> fn1(cw<foo>);
    move_only_function<int(baz_t)> fn2(cw<foo>);
    move_only_function<int(baz_t, baz_t, baz_t)> fn3(cw<foo>);
    return fn2(baz);
}

auto bar1() -> int
{
    constexpr auto fn0 = cw<foo>;
    static_assert(fn0() == 0);
    static_assert(fn0(baz) == 1);
    static_assert(fn0(baz, baz, baz) == 3);
    static_assert(fn0(baz, baz, baz) == cw<3>);

    function_ref<int()> fn1(cw<foo>);
    function_ref<int(baz_t)> fn2(cw<foo>);
    function_ref<int(baz_t, baz_t, baz_t)> fn3(cw<foo>);
    return fn2(baz);
}
