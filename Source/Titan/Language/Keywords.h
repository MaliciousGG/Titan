#pragma once

#include <string>
#include <unordered_map>

#include "Lexer/Token.h"

namespace Titan::Language
{
    extern const std::unordered_map<std::string, ETokenType> Keywords;

    bool IsKeyword(const std::string& Text);

    ETokenType ResolveKeyword(const std::string& Text);
}