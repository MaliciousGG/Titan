#include "Lexer.h"
#include "Token.h"
#include "Keywords.h"


FLexer::FLexer(const std::string& InSource)
    : Source(InSource)
{}

std::vector<FToken> FLexer::Tokenize()
{
    std::vector<FToken> Tokens;

    while (!IsAtEnd())
    {
        SkipWhitespace();

        if (IsAtEnd())
        {
            break;
        }

        const char Current = Peek();

        if (Current == '/' && PeekNext() == '/')
        {
            Advance(); // /
            Advance(); // /
            SkipLineComment();
            continue;
        }

        if (Current == '/' && PeekNext() == '*')
        {
            Advance(); // /
            Advance(); // *
            SkipBlockComment();
            continue;
        }

        if (IsIdentifierStart(Current))
        {
            Tokens.push_back(ReadIdentifier());
            continue;
        }

        if (IsDigit(Current))
        {
            Tokens.push_back(ReadNumber());
            continue;
        }

        const uint32_t StartLine = Line;
        const uint32_t StartColumn = Column;

        switch (Current)
        {
            case '{':
                Advance();
                Tokens.push_back({ ETokenType::OpenBrace, "{", StartLine, StartColumn });
                break;

            case '}':
                Advance();
                Tokens.push_back({ ETokenType::CloseBrace, "}", StartLine, StartColumn });
                break;

            case '(':
                Advance();
                Tokens.push_back({ ETokenType::OpenParen, "(", StartLine, StartColumn });
                break;

            case ')':
                Advance();
                Tokens.push_back({ ETokenType::CloseParen, ")", StartLine, StartColumn });
                break;

            case ':':
                Advance();
                Tokens.push_back({ ETokenType::Colon, ":", StartLine, StartColumn });
                break;

            case ';':
                Advance();
                Tokens.push_back({ ETokenType::Semicolon, ";", StartLine, StartColumn });
                break;

            case ',':
                Advance();
                Tokens.push_back({ ETokenType::Comma, ",", StartLine, StartColumn });
                break;

            case '.':
                Advance();
                Tokens.push_back({ ETokenType::Dot, ".", StartLine, StartColumn });
                break;

            case '?':
                Advance();
                Tokens.push_back({ ETokenType::Question, "?", StartLine, StartColumn });
                break;

            case '=':
                Advance();
                Tokens.push_back({ ETokenType::Assign, "=", StartLine, StartColumn });
                break;

            case '-':
                Advance();

                if (Peek() == '>')
                {
                    Advance();
                    Tokens.push_back({ ETokenType::Arrow, "->", StartLine, StartColumn });
                }
                else
                {
                    Tokens.push_back({ ETokenType::Unknown, "-", StartLine, StartColumn });
                }

                break;

            case '"':
                Tokens.push_back(ReadString());
                break;

            case '\'':
                Tokens.push_back(ReadCharacter());
                break;

            default:
            {
                const std::string UnknownText(1, Advance());
                Tokens.push_back({ ETokenType::Unknown, UnknownText, StartLine, StartColumn });
                break;
            }
        }
    }

    Tokens.push_back({ ETokenType::EndOfFile, "", Line, Column });

    return Tokens;
}

char FLexer::Peek() const
{
    if (IsAtEnd())
    {
        return '\0';
    }

    return Source[Position];
}

char FLexer::PeekNext() const
{
    if (Position + 1 >= Source.size())
    {
        return '\0';
    }

    return Source[Position + 1];
}

char FLexer::Advance()
{
    if (IsAtEnd())
    {
        return '\0';
    }

    char Current = Source[Position];
    ++Position;

    if (Current == '\n')
    {
        ++Line;
        Column = 1;
    }
    else
    {
        ++Column;
    }

    return Current;
}

bool FLexer::IsAtEnd() const
{
    return Position >= Source.size();
}

void FLexer::SkipWhitespace()
{
    while(!IsAtEnd())
    {
        char Current = Peek();

        if (!IsWhitespace(Current))
        {
            break;
        }

        Advance();
    }
}

void FLexer::SkipLineComment()
{
    while (!IsAtEnd() && Peek() != '\n')
    {
        Advance();
    }
}

void FLexer::SkipBlockComment()
{
    while (!IsAtEnd())
    {
        if (Peek() == '*' && PeekNext() == '/')
        {
            Advance(); // *
            Advance(); // /
            return;
        }

        Advance();
    }
}

FToken FLexer::MakeToken(ETokenType Type, const std::string& Text) const
{
    FToken Token;
    Token.Type = Type;
    Token.Text = Text;
    Token.Line = Line;
    Token.Column = Column;

    return Token;
}

FToken FLexer::MakeUnknownToken(const std::string& Text) const
{
    return MakeToken(ETokenType::Unknown, Text);
}

FToken FLexer::ReadIdentifier()
{
    std::string Text;

    const uint32_t StartLine = Line;
    const uint32_t StartColumn = Column;

    while (!IsAtEnd() && IsIdentifierPart(Peek()))
    {
        Text += Advance();
    }

    FToken Token;
    Token.Type = ResolveKeyword(Text);
    Token.Text = Text;
    Token.Line = StartLine;
    Token.Column = StartColumn;

    return Token;
}

FToken FLexer::ReadNumber()
{
    std::string Text;

    const uint32_t StartLine = Line;
    const uint32_t StartColumn = Column;

    bool bFoundDecimal = false;

    while (!IsAtEnd())
    {
        const char Current = Peek();

        if (IsDigit(Current))
        {
            Text += Advance();
            continue;
        }

        if (Current == '.' && !bFoundDecimal && IsDigit(PeekNext()))
        {
            bFoundDecimal = true;
            Text += Advance();
            continue;
        }

        break;
    }

    FToken Token;
    Token.Type = bFoundDecimal
        ? ETokenType::FloatLiteral
        : ETokenType::IntegerLiteral;

    Token.Text = Text;
    Token.Line = StartLine;
    Token.Column = StartColumn;

    return Token;
}

FToken FLexer::ReadString()
{
    std::string Text;

    const uint32_t StartLine = Line;
    const uint32_t StartColumn = Column;

    // Consume opening quote
    Advance();

    while (!IsAtEnd())
    {
        const char Current = Peek();

        if (Current == '"')
        {
            break;
        }

        Text += Advance();
    }

    // Unterminated string
    if (IsAtEnd())
    {
        return MakeUnknownToken(Text);
    }

    // Consume closing quote
    Advance();

    FToken Token;
    Token.Type = ETokenType::StringLiteral;
    Token.Text = Text;
    Token.Line = StartLine;
    Token.Column = StartColumn;

    return Token;
}

FToken FLexer::ReadCharacter()
{
    std::string Text;

    const uint32_t StartLine = Line;
    const uint32_t StartColumn = Column;

    // Consume opening '
    Advance();

    if (IsAtEnd())
    {
        return MakeUnknownToken(Text);
    }

    Text += Advance();

    // Must have closing '
    if (IsAtEnd() || Peek() != '\'')
    {
        return MakeUnknownToken(Text);
    }

    // Consume closing '
    Advance();

    FToken Token;
    Token.Type = ETokenType::CharacterLiteral;
    Token.Text = Text;
    Token.Line = StartLine;
    Token.Column = StartColumn;

    return Token;
}

ETokenType FLexer::ResolveKeyword(const std::string& Text) const
{
    return Titan::Language::ResolveKeyword(Text);
}

bool FLexer::IsIdentifierStart(char Character) const
{
    return (Character >= 'A' && Character <= 'Z') ||
           (Character >= 'a' && Character <= 'z') ||
           Character == '_';
}

bool FLexer::IsIdentifierPart(char Character) const
{
    return IsIdentifierStart(Character) || IsDigit(Character);
}

bool FLexer::IsDigit(char Character) const
{
    return Character >= '0' && Character <= '9';
}

bool FLexer::IsWhitespace(char Character) const
{
    return Character == ' ' ||
           Character == '\t' ||
           Character == '\r' ||
           Character == '\n';
}
