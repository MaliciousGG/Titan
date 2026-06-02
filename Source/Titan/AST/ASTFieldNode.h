#pragma once

#include <string>

#include "AstNode.h"

struct FASTFieldNode : FASTNode
{
    std::string Name; 
    std::string TypeName;
    std::string DefaultValue;
};