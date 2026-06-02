#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Token.h"

class FLexer
{
public:
    explicit FLexer(std::string  InSource);

    std::vector<FToken> Tokenize();

private:
    [[nodiscard]] char Peek() const;
    [[nodiscard]] char PeekNext() const;
    char Advance();

    [[nodiscard]] bool IsAtEnd() const;

    void SkipWhitespace();
    void SkipLineComment();
    void SkipBlockComment();

    [[nodiscard]] FToken MakeToken(ETokenType Type, const std::string& Text) const;
    [[nodiscard]] FToken MakeUnknownToken(const std::string& Text) const;

    FToken ReadIdentifier();
    FToken ReadNumber();
    FToken ReadString();
    FToken ReadCharacter();

    [[nodiscard]] ETokenType ResolveKeyword(const std::string& Text) const;

    [[nodiscard]] bool IsIdentifierStart(char Character) const;
    [[nodiscard]] bool IsIdentifierPart(char Character) const;
    [[nodiscard]] bool IsDigit(char Character) const;
    [[nodiscard]] bool IsWhitespace(char Character) const;

private:
    std::string Source;
    size_t Position = 0;

    uint32_t Line = 1;
    uint32_t Column = 1;
};