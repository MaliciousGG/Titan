#include "Tests/TestRunner.h"

#include <iostream>

void FTestRunner::AddResult(const std::string& Name, const bool bPassed, const std::string& Message)
{
    Results.push_back({ Name, bPassed, Message });
}

int FTestRunner::RunSummary() const
{
    int FailedCount = 0;

    for (const auto& [Name, bPassed, Message] : Results)
    {
        if (bPassed)
        {
            std::cout << "[PASS] " << Name << '\n';
        }
        else
        {
            ++FailedCount;
            std::cout << "[FAIL] " << Name;

            if (!Message.empty())
            {
                std::cout << " - " << Message;
            }

            std::cout << '\n';
        }
    }

    std::cout << "\nTotal: " << Results.size()
              << " | Failed: " << FailedCount
              << '\n';

    return FailedCount == 0 ? 0 : 1;
}