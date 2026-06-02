#pragma once

#include <cstdint>
#include <string>

enum class ETokenType : uint8_t
{
    Unknown,
    EndOfFile,

    Identifier,
    
    IntegerLiteral,
    FloatLiteral,
    StringLiteral,
    CharacterLiteral,

    KeywordStruct,
    KeywordFn,
    KeywordReturn,
    KeywordTrue,
    KeywordFalse,

    Colon,
    Semicolon,
    Comma,
    Dot,
    Question,

    Assign,

    OpenParen,
    CloseParen,
    OpenBrace,
    CloseBrace,

    Arrow
};

struct FToken
{
    ETokenType Type = ETokenType::Unknown;
    std::string Text;

    uint32_t Line = 1;
    uint32_t Column = 1;
};
