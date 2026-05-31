#include "Tests/TestRunner.h"

#include "Lexer/Lexer.h"
#include "Lexer/Token.h"

#include <string>
#include <vector>

namespace
{
    bool HasToken(
        const std::vector<FToken>& Tokens,
        const size_t Index,
        const ETokenType Type,
        const std::string& Text
    )
    {
        return Index < Tokens.size() &&
               Tokens[Index].Type == Type &&
               Tokens[Index].Text == Text;
    }
}

bool LexerTest_EmptySource()
{
    FLexer Lexer("");

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 1 &&
           Tokens[0].Type == ETokenType::EndOfFile;
}

bool LexerTest_WhitespaceOnly()
{
    FLexer Lexer("   \t\r\n   ");

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 1 &&
           Tokens[0].Type == ETokenType::EndOfFile;
}

bool LexerTest_StructKeyword()
{
    FLexer Lexer("struct");

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 2 &&
           HasToken(Tokens, 0, ETokenType::KeywordStruct, "struct") &&
           Tokens[1].Type == ETokenType::EndOfFile;
}

bool LexerTest_Identifier()
{
    FLexer Lexer("Player");

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 2 &&
           HasToken(Tokens, 0, ETokenType::Identifier, "Player") &&
           Tokens[1].Type == ETokenType::EndOfFile;
}

bool LexerTest_IntegerLiteral()
{
    FLexer Lexer("100");

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 2 &&
           HasToken(Tokens, 0, ETokenType::IntegerLiteral, "100") &&
           Tokens[1].Type == ETokenType::EndOfFile;
}

bool LexerTest_FloatLiteral()
{
    FLexer Lexer("100.0");

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 2 &&
           HasToken(Tokens, 0, ETokenType::FloatLiteral, "100.0") &&
           Tokens[1].Type == ETokenType::EndOfFile;
}

bool LexerTest_FieldDeclaration()
{
    FLexer Lexer("Health: f32 = 100.0;");

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 7 &&
           HasToken(Tokens, 0, ETokenType::Identifier, "Health") &&
           HasToken(Tokens, 1, ETokenType::Colon, ":") &&
           HasToken(Tokens, 2, ETokenType::Identifier, "f32") &&
           HasToken(Tokens, 3, ETokenType::Assign, "=") &&
           HasToken(Tokens, 4, ETokenType::FloatLiteral, "100.0") &&
           HasToken(Tokens, 5, ETokenType::Semicolon, ";") &&
           Tokens[6].Type == ETokenType::EndOfFile;
}

bool LexerTest_OptionalType()
{
    FLexer Lexer("Health: f32?;");

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 6 &&
           HasToken(Tokens, 0, ETokenType::Identifier, "Health") &&
           HasToken(Tokens, 1, ETokenType::Colon, ":") &&
           HasToken(Tokens, 2, ETokenType::Identifier, "f32") &&
           HasToken(Tokens, 3, ETokenType::Question, "?") &&
           HasToken(Tokens, 4, ETokenType::Semicolon, ";") &&
           Tokens[5].Type == ETokenType::EndOfFile;
}

bool LexerTest_FunctionArrow()
{
    FLexer Lexer("fn IsAlive() -> bool");

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 7 &&
           HasToken(Tokens, 0, ETokenType::KeywordFn, "fn") &&
           HasToken(Tokens, 1, ETokenType::Identifier, "IsAlive") &&
           HasToken(Tokens, 2, ETokenType::OpenParen, "(") &&
           HasToken(Tokens, 3, ETokenType::CloseParen, ")") &&
           HasToken(Tokens, 4, ETokenType::Arrow, "->") &&
           HasToken(Tokens, 5, ETokenType::Identifier, "bool") &&
           Tokens[6].Type == ETokenType::EndOfFile;
}

bool LexerTest_BasicStruct()
{
    const std::string Source = R"(
struct Player
{
    Health: f32 = 100.0;
}
)";

    FLexer Lexer(Source);

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 11 &&
           HasToken(Tokens, 0, ETokenType::KeywordStruct, "struct") &&
           HasToken(Tokens, 1, ETokenType::Identifier, "Player") &&
           HasToken(Tokens, 2, ETokenType::OpenBrace, "{") &&
           HasToken(Tokens, 3, ETokenType::Identifier, "Health") &&
           HasToken(Tokens, 4, ETokenType::Colon, ":") &&
           HasToken(Tokens, 5, ETokenType::Identifier, "f32") &&
           HasToken(Tokens, 6, ETokenType::Assign, "=") &&
           HasToken(Tokens, 7, ETokenType::FloatLiteral, "100.0") &&
           HasToken(Tokens, 8, ETokenType::Semicolon, ";") &&
           HasToken(Tokens, 9, ETokenType::CloseBrace, "}") &&
           Tokens[10].Type == ETokenType::EndOfFile;
}

bool LexerTest_StringLiteral()
{
    FLexer Lexer("\"Titan\"");

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 2 &&
           HasToken(Tokens, 0, ETokenType::StringLiteral, "Titan") &&
           Tokens[1].Type == ETokenType::EndOfFile;
}

bool LexerTest_CharacterLiteral()
{
    FLexer Lexer("'A'");

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 2 &&
           HasToken(Tokens, 0, ETokenType::CharacterLiteral, "A") &&
           Tokens[1].Type == ETokenType::EndOfFile;
}

bool LexerTest_LineComment()
{
    FLexer Lexer("// comment\nstruct");

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 2 &&
           HasToken(Tokens, 0, ETokenType::KeywordStruct, "struct") &&
           Tokens[1].Type == ETokenType::EndOfFile;
}

bool LexerTest_BlockComment()
{
    FLexer Lexer("/* comment */ struct");

    const std::vector<FToken> Tokens = Lexer.Tokenize();

    return Tokens.size() == 2 &&
           HasToken(Tokens, 0, ETokenType::KeywordStruct, "struct") &&
           Tokens[1].Type == ETokenType::EndOfFile;
}

void RunLexerTests(FTestRunner& Runner)
{
    Runner.AddResult("Lexer.EmptySource", LexerTest_EmptySource(), "Expected only EOF token");
    Runner.AddResult("Lexer.WhitespaceOnly", LexerTest_WhitespaceOnly(), "Expected whitespace to be skipped");
    Runner.AddResult("Lexer.StructKeyword", LexerTest_StructKeyword(), "Expected struct keyword token");
    Runner.AddResult("Lexer.Identifier", LexerTest_Identifier(), "Expected identifier token");
    Runner.AddResult("Lexer.IntegerLiteral", LexerTest_IntegerLiteral(), "Expected integer literal token");
    Runner.AddResult("Lexer.FloatLiteral", LexerTest_FloatLiteral(), "Expected float literal token");
    Runner.AddResult("Lexer.FieldDeclaration", LexerTest_FieldDeclaration(), "Expected field declaration tokens");
    Runner.AddResult("Lexer.OptionalType", LexerTest_OptionalType(), "Expected optional type tokens");
    Runner.AddResult("Lexer.FunctionArrow", LexerTest_FunctionArrow(), "Expected function arrow tokens");
    Runner.AddResult("Lexer.BasicStruct", LexerTest_BasicStruct(), "Expected basic struct tokens");
    Runner.AddResult("Lexer.StringLiteral", LexerTest_StringLiteral(), "Expected string literal tokens");
    Runner.AddResult("Lexer.CharacterLiteral", LexerTest_CharacterLiteral(), "Expected character literal tokens");
    Runner.AddResult("Lexer.LineComment", LexerTest_LineComment(), "Expected line comment tokens");
    Runner.AddResult("Lexer.BlockComment", LexerTest_BlockComment(), "Expected block comment tokens");
}