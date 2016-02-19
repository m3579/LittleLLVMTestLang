#ifndef MYPARSER2_HPP_INCLUDED
#define MYPARSER2_HPP_INCLUDED

/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Feb 17, 2016
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */


#include <Parser.hpp>

#include "MyLexer.hpp"

using namespace lexer;
using namespace parser;
using namespace ast;

createNodeType(NTYPE_ADD);
createNodeType(NTYPE_SUBTRACT);
createNodeType(NTYPE_NUMBER);

Parser getParser(Lexer lexer)
{
    SP<Construct> plus_sign(new Construct("Plus sign", TTYPE_PLUS_TOKEN, NTYPE_ADD));
    SP<Construct> minus_sign(new Construct("Minus sign", TTYPE_MINUS_TOKEN, NTYPE_SUBTRACT));
    SP<Construct> op1(new Construct("Operator 1", TTYPE_NUMBER, NTYPE_NUMBER));
    SP<Construct> op2(new Construct("Operator 2", TTYPE_NUMBER, NTYPE_NUMBER));
    SP<Construct> op3(new Construct("Operator 3", TTYPE_NUMBER, NTYPE_NUMBER));
    SP<Construct> op4(new Construct("Operator 4", TTYPE_NUMBER, NTYPE_NUMBER));

    std::vector<SP<Construct>> minus_constr_components {
        op1, minus_sign, op2
    };
    SP<Construct> minus_constr(new Construct("Minus", minus_constr_components));

    std::vector<SP<Construct>> add_constr_components {
        op3, plus_sign, minus_constr
    };
    SP<Construct> add_constr(new Construct("Add", add_constr_components));

    SP<ConstructTreeFormNode> add_constr_tree(new ConstructTreeFormNode("Plus sign"));
    add_constr_tree->subnode("Operator 3");
    add_constr_tree->subnode("Minus sign");
    add_constr_tree->get("Minus sign")->subnode("Operator 1");
    add_constr_tree->get("Minus sign")->subnode("Operator 2");

    SP<Construct> end_constr(new Construct("End", TTYPE_END, NTYPE_NONODE));

    Parser myParser(lexer);
    myParser.addConstruct(add_constr);
    myParser.addConstruct(end_constr);
    return myParser;
}

#endif // MYPARSER2_HPP_INCLUDED
