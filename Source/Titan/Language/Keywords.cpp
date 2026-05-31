#include "Language/Keywords.h"

namespace Titan::Language
{
    const std::unordered_map<std::string, ETokenType> Keywords =
    {
        { "struct", ETokenType::KeywordStruct },
        { "fn", ETokenType::KeywordFn },
        { "return", ETokenType::KeywordReturn },

        { "true", ETokenType::KeywordTrue },
        { "false", ETokenType::KeywordFalse }
    };

    bool IsKeyword(const std::string& Text)
    {
        return Keywords.contains(Text);
    }

    ETokenType ResolveKeyword(const std::string& Text)
    {
        const auto Iterator = Keywords.find(Text);

        if (Iterator != Keywords.end())
        {
            return Iterator->second;
        }

        return ETokenType::Identifier;
    }
}