#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Token.h"

class FLexer
{
public:
    explicit FLexer(const std::string& InSource);

    std::vector<FToken> Tokenize();

private:
    char Peek() const;
    char PeekNext() const;
    char Advance();

    bool IsAtEnd() const;

    void SkipWhitespace();
    void SkipLineComment();
    void SkipBlockComment();

    FToken MakeToken(ETokenType Type, const std::string& Text) const;
    FToken MakeUnknownToken(const std::string& Text) const;

    FToken ReadIdentifier();
    FToken ReadNumber();
    FToken ReadString();
    FToken ReadCharacter();

    ETokenType ResolveKeyword(const std::string& Text) const;

    bool IsIdentifierStart(char Character) const;
    bool IsIdentifierPart(char Character) const;
    bool IsDigit(char Character) const;
    bool IsWhitespace(char Character) const;

private:
    std::string Source;
    size_t Position = 0;

    uint32_t Line = 1;
    uint32_t Column = 1;
};