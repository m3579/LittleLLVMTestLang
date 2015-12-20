#ifndef MYPARSER_HPP_INCLUDED
#define MYPARSER_HPP_INCLUDED


#include <Parser.hpp>

#include "MyLexer.hpp"
#include "ast.hpp"

using namespace parser;
using namespace ast;
using namespace node;
using namespace pointer;

createNodeType(NTYPE_NUMBER);
createNodeType(NTYPE_ADD);
createNodeType(NTYPE_SUBTRACT);
createNodeType(NTYPE_MULTIPLY);
createNodeType(NTYPE_DIVIDE);

SP<Symbol> number(new Symbol(TTYPE_NUMBER, "Number", symbolFoundDoNothing, NTYPE_NUMBER));

SP<Symbol> add(new Symbol(TTYPE_PLUS_TOKEN, "Add", symbolFoundDoNothing, NTYPE_ADD));

SP<Symbol> subtract(new Symbol(TTYPE_MINUS_TOKEN, "Subtract", symbolFoundDoNothing, NTYPE_SUBTRACT));

SP<Symbol> multiply(new Symbol(TTYPE_ASTERISK, "Multiply", symbolFoundDoNothing, NTYPE_MULTIPLY));

SP<Symbol> divide(new Symbol(TTYPE_FORWARD_SLASH, "Divide", symbolFoundDoNothing, NTYPE_DIVIDE));

SP<Symbol> theEnd(new Symbol(TTYPE_END, "End", [] (TokenManager& tm) { exit = true; }, NTYPE_NONODE));

void invalidExpression(TokenManager& tm)
{
    std::cout << "Error: invalid expression\n";
}

Parser getParser(lexer::Lexer myLexer)
{
    Parser myParser(myLexer);

    // Expressions
    myParser.addSymbol(number);

    number->addNextSymbol(add, 1);
    add->addNextSymbol(number, 0);
    add->noFind = invalidExpression;

    number->addNextSymbol(subtract, 1);
    subtract->addNextSymbol(number, 0);
    subtract->noFind = invalidExpression;

    number->addNextSymbol(multiply, 1);
    multiply->addNextSymbol(number, 0);
    multiply->noFind = invalidExpression;

    number->addNextSymbol(divide, 1);
    divide->addNextSymbol(number, 0);
    divide->noFind = invalidExpression;

    myParser.addSymbol(theEnd);

    return myParser;
}


#endif // MYPARSER_HPP_INCLUDED
