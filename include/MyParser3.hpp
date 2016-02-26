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
        createNodeType(INCREMENT_OP);
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
    SP<Construct> let_keyword(new Construct("Keyword - let", TType::Keyword::LET, NType::Keyword::LET, 0, 0));

    // <space>
    SP<Construct> spaceAfterLet(new Construct("Space After Let", TType::SPACE, NType::SPACE, 0, [] (TokenManager& tm) { std::cout << "Error: expected space after let"; tm.exit = true; }));

    // let + <space>
    std::vector<SP<Construct>> letKeywordAndSpaceComponents {
        let_keyword, spaceAfterLet
    };
    SP<Construct> letKeywordAndSpace(new Construct("Keyword - let + Space After Let", letKeywordAndSpaceComponents, 0, 0));

    // var
    SP<Construct> identifier(new Construct("Identifier", TType::IDENTIFIER, NType::IDENTIFIER, 0, 0));

    // =
    std::vector<TokenType> var_dec_op_ttypes {
        TType::Operator::ASSIGNMENT_OP, TType::Operator::INCREMENT_OP
    };
    std::vector<NodeType> var_dec_op_ntypes {
        NType::Operator::ASSIGNMENT_OP, NType::Operator::INCREMENT_OP
    };

    SP<Construct> var_dec_op(new Construct("Var dec operator", var_dec_op_ttypes, var_dec_op_ntypes, 0, 0));
    var_dec_op->notFound = [] (TokenManager& tm) {
        std::cout << "Error: expected operator after variable\n";
        tm.exit = true;
    };

    // value
    SP<Construct> value(new Construct("Value", TType::Value::NUMBER, NType::Value::NUMBER, 0, 0));

    // <space>
    SP<Construct> space(new Construct("Space", TType::SPACE, NType::SPACE, 0, 0));

    // Variable declaration statement
    std::vector<SP<Construct>> var_dec_components {
        letKeywordAndSpace->getOptionalForm(), identifier, space, var_dec_op, space, value
    };

    SP<Construct> var_dec_constr(new Construct("Variable Declaration", var_dec_components, 0, 0));

    SP<ConstructTreeFormNode> var_dec_treeForm(new ConstructTreeFormNode("Var dec operator"));
    var_dec_treeForm->subnode("Identifier");
    var_dec_treeForm->subnode("Value");

    var_dec_constr->treeForm = var_dec_treeForm;

    myParser.addConstruct(var_dec_constr);

    // End
    SP<Construct> end_constr(new Construct("End", TType::END, NType::END, [] (TokenManager& tm) { tm.exit = true; }, 0));

    // TODO: make this form of construct tree form the default
    SP<ConstructTreeFormNode> end_treeForm(new ConstructTreeFormNode("End"));

    end_constr->treeForm = end_treeForm;

    myParser.addConstruct(end_constr);

    return myParser;
}

#endif // MYPARSER3_HPP_INCLUDED
