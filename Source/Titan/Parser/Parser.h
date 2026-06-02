#pragma once

#include <string>
#include <vector>

#include "Token.h"
#include "ASTStructNode.h"

class FParser
{
public:
    explicit FParser(const std::vector<FToken>& InTokens);
    
    FASTStructNode ParseStruct();
    
private:
    const FToken& Peek() const;
    const FToken& Advance();
    
    bool Match(ETokenType Type);
    bool Check(ETokenType Type) const;
    
private:
    std::vector<FToken> Tokens;
    size_t Position = 0;
};
