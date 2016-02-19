#include <iostream>

#include <Parser.hpp>

#include "MyParser3.hpp"

using namespace parser;
using namespace ast;
using namespace pointer;

int main()
{
    try {
        Parser parser = getParser(getLexer("let var = 1"));
        SP<SyntaxTree> tree(parser.createSyntaxTree());
        tree->print("");
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << "\n";
        return 1;
    }
}
