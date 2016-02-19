#ifndef MYLEXER2_HPP_INCLUDED
#define MYLEXER2_HPP_INCLUDED

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


#include <Lexer.hpp>

using namespace lexer;
using namespace scanner;
using namespace token;

// Syntax:
// let var = value

namespace TType
{
    createTokenType(IDENTIFIER);

    createTokenType(SPACE);

    createTokenType(END);

    namespace Keyword
    {
        createTokenType(LET);
    }

    namespace Operator
    {
        createTokenType(ASSIGNMENT_OP);
    }

    namespace Value
    {
        createTokenType(NUMBER);
    }
}

std::string IDENTIFIER_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

// values are a single digit long
std::string NUMBER_CHARS = "0123456789";

Lexer getLexer(std::string text)
{
    Lexer lexr(text);

    lexr.addTest(
        [] (Scanner& sc)
        {
            if (sc.getCurrentChar() == 'l') {
                int lineNumber = sc.getLineNumber();
                int columnNumber = sc.getColumnNumber();

                if (sc.fetchNextChar() == 'e') {
                    sc.moveToNextChar();
                    if (sc.fetchNextChar() == 't') {
                        sc.moveToNextChar();
                        return Token(lineNumber, columnNumber, "let", TType::Keyword::LET);
                    }
                }
            }

            return Token();
        }
    );

    lexr.addTest(
        [] (Scanner& sc)
        {
            if (IDENTIFIER_CHARS.find(sc.getCurrentChar()) != std::string::npos) {
                int lineNumber = sc.getLineNumber();
                int columnNumber = sc.getColumnNumber();

                std::string identifier(1, sc.getCurrentChar());

                while (IDENTIFIER_CHARS.find(sc.fetchNextChar()) != std::string::npos) {
                    identifier += sc.moveToNextChar();
                }

                return Token(lineNumber, columnNumber, identifier, TType::IDENTIFIER);
            }

            return Token();
        }
    );

    lexr.addTest(
        [] (Scanner& sc)
         {
             if (sc.getCurrentChar() == '=') {
                return Token(sc.getLineNumber(), sc.getColumnNumber(), "=", TType::Operator::ASSIGNMENT_OP);
             }

             return Token();
         }
    );

    lexr.addTest(
        [] (Scanner& sc)
        {
            if (NUMBER_CHARS.find(sc.getCurrentChar()) != std::string::npos)
            {
                return Token(sc.getLineNumber(), sc.getColumnNumber(), std::string(1, sc.getCurrentChar()), TType::Value::NUMBER);
            }

            return Token();
        }
    );

    lexr.addTest(
        [] (Scanner& sc)
         {
            if (sc.getCurrentChar() == ' ') {
                return Token(sc.getLineNumber(), sc.getColumnNumber(), " ", TType::SPACE);
            }

            return Token();
         }
    );

    lexr.addTest(
        [] (Scanner& sc)
        {
            if (sc.getCurrentChar() == '\0') {
                sc.finished = true;
                return Token(sc.getLineNumber(), sc.getColumnNumber(), "\0", TType::END);
            }

            return Token();
        }
    );

    return lexr;
}

#endif // MYLEXER2_HPP_INCLUDED
