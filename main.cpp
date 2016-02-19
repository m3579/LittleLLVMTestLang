#include <iostream>

#include <Parser.hpp>
#include <utilities.h>

#include "MyParser3.hpp"

using namespace parser;
using namespace ast;
using namespace pointer;

int main()
{
    try {
        Parser parser = getParser(getLexer("let var 1"));
        SP<SyntaxTree> tree(parser.createSyntaxTree());
        tree->print("");
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << "\n";
    }
}
