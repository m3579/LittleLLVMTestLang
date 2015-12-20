#include <iostream>

#include <Parser.hpp>

#include "MyParser.hpp"

using namespace parser;
using namespace ast;

int main()
{
    Parser parser = getParser(getLexer("1+2"));
    std::shared_ptr<SyntaxTree> tree(parser.createSyntaxTree());
    tree->print("");
}
