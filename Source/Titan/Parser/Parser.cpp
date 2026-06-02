#include "Parser.h"

FParser::FParser(const std::vector<FToken>& InTokens)
    : Tokens(InTokens)
{
} 

FASTStructNode FParser::ParseStruct()
{
    FASTStructNode StructNode;
    StructNode.Type = EASTNodeType::Struct;
    
    Match(ETokenType::KeywordStruct);
    
    const FToken& NameToken = Peek();
    Match(ETokenType::Identifier);
    
    StructNode.Name = NameToken.Text;
    
    Match(ETokenType::OpenBrace);
    
    while (!Check(ETokenType::CloseBrace) && !Check(ETokenType::EndOfFile))
    {
        FASTFieldNode FieldNode;
        
        const FToken& FieldNameToken = Peek();
        Match(ETokenType::Identifier);
        
        FieldNode.Name = FieldNameToken.Text;
        
        Match(ETokenType::Colon);
        
        const FToken& TypeToken = Peek();
        Match(ETokenType::Identifier);
        
        FieldNode.TypeName = TypeToken.Text;
        
        if (Match(ETokenType::Assign))
        {
            const FToken& DefaultValueToken = Peek();
            
            if (Match(ETokenType::IntegerLiteral) ||
                Match(ETokenType::FloatLiteral) ||
                Match(ETokenType::StringLiteral) ||
                Match(ETokenType::CharacterLiteral) ||
                Match(ETokenType::KeywordTrue) ||
                Match(ETokenType::KeywordFalse) 
            )
            {
                FieldNode.DefaultValue = DefaultValueToken.Text;
            }
        }
        Match(ETokenType::Semicolon);
        
        StructNode.Fields.push_back(FieldNode);
    }
    
    Match(ETokenType::CloseBrace);
    
    return StructNode;
}

const FToken& FParser::Peek() const
{
    return Tokens[Position];
}

const FToken& FParser::Advance()
{
    if (Position < Tokens.size())
    {
        ++Position;
    }
    
    return Tokens[Position];
}

bool FParser::Match(const ETokenType Type)
{
    if (!Check(Type))
    {
        return false;
    }
    
    Advance();
    
    return true;
}

bool FParser::Check(const ETokenType Type) const
{
    return Peek().Type == Type;
}