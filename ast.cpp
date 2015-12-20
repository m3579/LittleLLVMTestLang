/*
 * ast.cpp
 *
 * /CompilerFrameworkInCPP/Sources/ast.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Dec 20, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include "TokenManager.hpp"
#include "ast.hpp"

namespace ast
{
    AstManipulationAction symbolFoundDoNothing = [] (parser::TokenManager& tm) { };
}
