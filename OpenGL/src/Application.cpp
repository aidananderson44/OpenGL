#include "Engine.h"
#include "tests/TestSelection.h"

int main(void)
{
    Engine engine;
    engine.Run<test::TestSelection>();
    return 0;
}