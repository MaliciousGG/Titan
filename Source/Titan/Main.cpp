#include "Tests/TestRunner.h"

int main()
{
    FTestRunner Runner;

    RunLexerTests(Runner);
    RunParserTests(Runner);

    return Runner.RunSummary();
}