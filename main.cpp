#include <iostream>

#include <Parser.hpp>

#include "MyParser.hpp"

using namespace parser;
using namespace ast;
using namespace pointer;

int main()
{
    Parser parser = getParser(getLexer("1*2+3"));
    SP<SyntaxTree> tree(parser.createSyntaxTree());
    tree->print("");
}
