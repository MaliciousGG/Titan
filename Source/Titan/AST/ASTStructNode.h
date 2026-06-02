#pragma once

#include <string>
#include <vector>

#include "ASTNode.h"
#include "ASTFieldNode.h"

struct FASTStructNode : FASTNode
{
    std::string Name;
    std::vector<FASTFieldNode> Fields;
};
