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

SP<Symbol> oper1(new Symbol(TTYPE_NUMBER, "Operator #1", symbolFoundDoNothing, NTYPE_NUMBER));
SP<Symbol> oper2(new Symbol(TTYPE_NUMBER, "Operator #2", symbolFoundDoNothing, NTYPE_NUMBER));

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

    SP<Construct> add_constr(
        new Construct(
            std::vector<SP<Symbol>> {
                oper1, add, oper2
            }));

    SP<ConstructTreeForm> add_expr_treeForm("Add");
    add_expr_treeForm.subnode("Operator #1");
    add_expr_treeForm.subnode("Operator #2");

    add_constr.treeForm = add_expr_treeForm;

    myParser.addConstruct(add_constr);

    myParser.addConstruct(SP<Construct>(new Construct(theEnd)));

    return myParser;
}


#endif // MYPARSER_HPP_INCLUDED
