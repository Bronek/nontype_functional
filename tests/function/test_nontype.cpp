#include "common_callables.h"

#include <memory>
#include <optional>

namespace
{

struct A
{
    A() = default;
    A(int a) : val{a} {}

    int add(int a)
    {
        val += a;
        return val;
    }

    void set(int a) &noexcept { val = a; }

    int val = 0;
};

int neg(A const &a) noexcept
{
    return -a.val;
}

} // namespace
