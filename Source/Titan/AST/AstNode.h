#pragma once
#include <cstdint>

enum class EASTNodeType : uint8_t
{
    Struct,
    Field
};

struct FASTNode
{
    virtual ~FASTNode()  = default;
    
    EASTNodeType Type;
};