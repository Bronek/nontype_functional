#include "common_callables.h"

#include <optional>

using T = move_only_function<int() const>;

suite nttp_callable = []
{
    using namespace bdd;
};

using U = move_only_function<int(A)>;
