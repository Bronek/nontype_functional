#include "std23/constant_wrapper.hpp"
#include "std23/function_ref.h"
#include "std23/move_only_function.h"

#include <concepts>
#include <type_traits>

using namespace std23;

static constexpr struct foo_t final
{
    constexpr auto operator()(auto &&...args) const -> int
        requires(std::integral<std::remove_cvref_t<decltype(args)>> && ...)
    {
        return (0 + ... + args);
    }

    constexpr auto operator()(auto &&...args) const -> int
        requires(std::integral<
                     decltype(std::remove_cvref_t<decltype(args)>::value)> &&
                 ...)
    {
        return sizeof...(args);
    }

} foo = {};

static constexpr struct baz_t final
{
    static constexpr int value = 2;
} baz = {};

auto main() -> int
{
    function_ref<int(baz_t)> fn(cw<foo>);
    assert(fn(baz) == 2); // assertion failure
}
