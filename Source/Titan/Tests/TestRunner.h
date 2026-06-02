#pragma once

#include <string>
#include <vector>

struct FTestResult
{
    std::string Name;
    bool bPassed = false;
    std::string Message;
};

class FTestRunner
{
public:
    void AddResult(const std::string& Name, bool bPassed, const std::string& Message = "");
    [[nodiscard]] int RunSummary() const;

private:
    std::vector<FTestResult> Results;
};

void RunLexerTests(FTestRunner& Runner);
void RunParserTests(FTestRunner& Runner);