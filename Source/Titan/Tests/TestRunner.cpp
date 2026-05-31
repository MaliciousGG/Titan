#include "Tests/TestRunner.h"

#include <iostream>

void FTestRunner::AddResult(const std::string& Name, bool bPassed, const std::string& Message)
{
    Results.push_back({ Name, bPassed, Message });
}

int FTestRunner::RunSummary() const
{
    int FailedCount = 0;

    for (const FTestResult& Result : Results)
    {
        if (Result.bPassed)
        {
            std::cout << "[PASS] " << Result.Name << '\n';
        }
        else
        {
            ++FailedCount;
            std::cout << "[FAIL] " << Result.Name;

            if (!Result.Message.empty())
            {
                std::cout << " - " << Result.Message;
            }

            std::cout << '\n';
        }
    }

    std::cout << "\nTotal: " << Results.size()
              << " | Failed: " << FailedCount
              << '\n';

    return FailedCount == 0 ? 0 : 1;
}