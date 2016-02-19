#ifndef MYPARSER3_HPP_INCLUDED
#define MYPARSER3_HPP_INCLUDED

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

#include "MyLexer2.hpp"

using namespace parser;
using namespace lexer;
using namespace ast;

namespace NType
{
    createNodeType(IDENTIFIER);

    createNodeType(SPACE);

    createNodeType(END);

    namespace Keyword
    {
        createNodeType(LET);
    }

    namespace Operator
    {
        createNodeType(ASSIGNMENT_OP);
    }

    namespace Value
    {
        createNodeType(NUMBER);
    }
}

// let var = value
Parser getParser(Lexer lexer)
{
    Parser myParser(lexer);

    // let
    SP<Construct> let(new Construct("Keyword - let", TType::Keyword::LET, NType::Keyword::LET));

    // var
    SP<Construct> identifier(new Construct("Identifier", TType::IDENTIFIER, NType::IDENTIFIER));

    // =
    SP<Construct> assignment_op(new Construct("Operator - assignment", TType::Operator::ASSIGNMENT_OP, NType::Operator::ASSIGNMENT_OP));

    // value
    SP<Construct> value(new Construct("Value", TType::Value::NUMBER, NType::Value::NUMBER));

    // <space>
    SP<Construct> space(new Construct("Space", TType::SPACE, NType::SPACE));

    // Variable declaration statement
    std::vector<SP<Construct>> var_dec_components {
        let, space, identifier, space, assignment_op, space, value
    };

    SP<Construct> var_dec_constr(new Construct("Variable Declaration", var_dec_components));

    SP<ConstructTreeFormNode> var_dec_treeForm(new ConstructTreeFormNode("Operator - assignment"));
    var_dec_treeForm->subnode("Identifier");
    var_dec_treeForm->subnode("Value");

    var_dec_constr->treeForm = var_dec_treeForm;

    myParser.addConstruct(var_dec_constr);

    // End
    SP<Construct> end_constr(new Construct("End", TType::END, NType::END));

    SP<ConstructTreeFormNode> end_treeForm(new ConstructTreeFormNode("End"));

    end_constr->treeForm = end_treeForm;

    myParser.addConstruct(end_constr);

    return myParser;
}

#endif // MYPARSER3_HPP_INCLUDED
