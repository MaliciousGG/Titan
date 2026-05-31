#include "Tests/TestRunner.h"

int main()
{
    FTestRunner Runner;

    RunLexerTests(Runner);

    return Runner.RunSummary();
}