#include "Tests/TestRunner.h"

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

bool ParserTest_BasicStruct()
{
    const std::string Source = R"(
struct Player
{
    Health: f32 = 100.0;
}
)";

    FLexer Lexer(Source);
    const std::vector<FToken> Tokens = Lexer.Tokenize();

    FParser Parser(Tokens);
    const FASTStructNode StructNode = Parser.ParseStruct();

    return StructNode.Name == "Player" &&
           StructNode.Fields.size() == 1 &&
           StructNode.Fields[0].Name == "Health" &&
           StructNode.Fields[0].TypeName == "f32" &&
           StructNode.Fields[0].DefaultValue == "100.0";
}

void RunParserTests(FTestRunner& Runner)
{
    Runner.AddResult(
        "Parser.BasicStruct",
        ParserTest_BasicStruct(),
        "Expected parser to parse basic struct with one field"
    );
}