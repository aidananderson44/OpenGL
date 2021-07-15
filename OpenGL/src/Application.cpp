#include "Engine.h"
#include "tests/TestSelection.h"
#include <cassert>
int main(void)
{
    assert(_WIN32);
    Engine engine;
    engine.Run<test::TestSelection>();
    return 0;
}