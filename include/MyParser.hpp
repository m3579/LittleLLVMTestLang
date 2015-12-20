#ifndef MYPARSER_HPP_INCLUDED
#define MYPARSER_HPP_INCLUDED


#include <Parser.hpp>

#include "MyLexer.hpp"

using namespace parser;
using namespace ast;
using namespace node;

createNodeType(NTYPE_NUMBER);
createNodeType(NTYPE_ADD);

std::shared_ptr<Symbol> number(new Symbol(TTYPE_NUMBER, "Number", emptyAstAction, NTYPE_NUMBER));

std::shared_ptr<Symbol> plusSign(new Symbol(TTYPE_PLUS_TOKEN, "Plus", emptyAstAction, NTYPE_ADD));

std::shared_ptr<Symbol> theEnd(new Symbol(TTYPE_END, "End", [] (TokenManager& tm) { exit = true; }, NTYPE_NONODE));

Parser getParser(lexer::Lexer myLexer)
{
    Parser myParser(myLexer);

    myParser.addSymbol(number);
    number->addNextSymbol(plusSign, 1);
    plusSign->addNextSymbol(number, 0);

    plusSign->noFind =
        [] (TokenManager& tm)
        {
            std::cout << "Error: you need to have either a number after a + sign or nothing at all\n\n";
            exit = true;
        };

    myParser.addSymbol(theEnd);

    return myParser;
}


#endif // MYPARSER_HPP_INCLUDED
