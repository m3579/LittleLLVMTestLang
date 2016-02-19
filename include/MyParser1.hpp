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

SP<Construct> oper1(new Construct("Operator #1", TTYPE_NUMBER, NTYPE_NUMBER));
SP<Construct> oper2(new Construct("Operator #2", TTYPE_NUMBER, NTYPE_NUMBER));

SP<Construct> add(new Construct("Add", TTYPE_PLUS_TOKEN, NTYPE_ADD));
SP<Construct> subtract(new Construct("Subtract", TTYPE_MINUS_TOKEN, NTYPE_SUBTRACT));
SP<Construct> multiply(new Construct("Multiply", TTYPE_ASTERISK, NTYPE_MULTIPLY));
SP<Construct> divide(new Construct("Divide", TTYPE_FORWARD_SLASH, NTYPE_DIVIDE));

SP<Construct> theEnd(new Construct("End", TTYPE_END, NTYPE_NONODE));

void invalidExpression(TokenManager& tm);

Parser getParser(lexer::Lexer myLexer)
{
    Parser myParser(myLexer);

    SP<Construct> add_constr(
        new Construct("Add Construct",
            std::vector<SP<Construct>> {
                oper1, add, oper2
            }));

    SP<ConstructTreeFormNode> add_expr_treeForm(new ConstructTreeFormNode("Add"));
    add_expr_treeForm->subnode("Operator #1");
    add_expr_treeForm->subnode("Operator #2");

    add_constr->treeForm = add_expr_treeForm;

    myParser.addConstruct(add_constr);

    myParser.addConstruct(theEnd);

    return myParser;
}

void invalidExpression(TokenManager& tm)
{
    std::cout << "Error: invalid expression\n";
}

#endif // MYPARSER_HPP_INCLUDED
