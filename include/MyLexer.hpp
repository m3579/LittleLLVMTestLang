#ifndef MYLEXER_HPP_INCLUDED
#define MYLEXER_HPP_INCLUDED

#include <iostream>

#include <Lexer.hpp>
#include <TokenType.h>

using namespace scanner;
using namespace token;

createTokenType(TTYPE_NUMBER);
createTokenType(TTYPE_PLUS_TOKEN);
createTokenType(TTYPE_END);

const std::string NUMBER_CHARS = "1234567890";

lexer::Lexer getLexer(std::string text)
{
    lexer::Lexer myLexer(text);

    myLexer.addTest(
        [] (Scanner& sc)
        {
            if (NUMBER_CHARS.find(sc.getCurrentChar()) != std::string::npos) {
                return Token(sc.getLineNumber(), sc.getColumnNumber(), std::string(1, sc.getCurrentChar()), TTYPE_NUMBER);
            }
            return Token();
        }
    );

    myLexer.addTest(
        [] (Scanner& sc)
        {
            if (sc.getCurrentChar() == '+') {
                Token t = Token(sc.getLineNumber(), sc.getColumnNumber(), "+", TTYPE_PLUS_TOKEN);
                return t;
            }
            return Token();
        }
    );

    myLexer.addTest(
        [] (Scanner& sc)
        {
            if (sc.getCurrentChar() == '\0') {
                sc.finished = true;
                return Token(sc.getLineNumber(), sc.getColumnNumber(), "\0", TTYPE_END);
            }
            return Token();
        }
    );

    return myLexer;
}

#endif // MYLEXER_HPP_INCLUDED
