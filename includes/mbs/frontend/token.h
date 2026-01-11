#ifndef MBSCRIPT_UTILS_H
#define MBSCRIPT_UTILS_H

#include <format>
#include <ostream>
#include <string>

enum class TokenType;

namespace mbs {
    enum class TokenType {
        // LITERALS
        TOK_STRING, // "abc" or 'abc'
        TOK_NUMBER, // 123 or 123.45
        TOK_TRUE, // true
        TOK_FALSE, // false
        TOK_NULL, // nil

        // MISC
        TOK_IDENT,
        TOK_OPEN_PAREN, // '('
        TOK_CLOSE_PAREN, // ')'
        TOK_DOT, // '.'
        TOK_COLON, // ':'
        TOK_COMMA, // ','
        TOK_QUESTION, // '?'

        // UNARY
        TOK_NEGATE, // -a
        TOK_NOT, // !a
        TOK_INC, // x++
        TOK_DEC, // x--

        // BINARY
        TOK_PLUS, // a + b
        TOK_MINUS, // a - b
        TOK_MUL, // a * b
        TOK_DIV, // a / b
        TOK_MOD, // a % b
        TOK_POW, // a ** b or a ^ b

        // COMPARISON BINARY
        TOK_EQUALS, // a == b
        TOK_NOT_EQUALS, // a != b
        TOK_LESS, // a < b
        TOK_GREATER, // a > b
        TOK_LESS_OR_EQUALS, // a <= b
        TOK_GREATER_OR_EQUALS, // a >= b
        TOK_AND, //  a && b
        TOK_OR, // a || b

        // OTHER TOKENS
        TOK_INVALID,

        // End Of File
        TOK_EOF
    };


    std::string tokenTypeToString(TokenType tt);

    struct Token {
        std::string value; // Token Value
        struct Position {
            int start = -1, end = -1, line = -1;
        } pos; // Token position in the input str
        TokenType type = TokenType::TOK_INVALID; // Token type

        friend std::ostream &operator<<(std::ostream &os, const Token &m) {
            os << std::string{"{"} << std::endl;
            os << std::string{"\tvalue: "} << m.value << "," << std::endl;
            os << std::string{"\tpos: { start: "} << m.pos.start << ", end: " << m.pos.end << ", line: " << m.pos.line
                    << " }," << std::endl;
            os << std::string{"\ttype: "} << std::format("{}", tokenTypeToString(m.type)) << std::endl;
            os << std::string{"}"} << std::endl;
            return os;
        }
    };
}

#endif //MBSCRIPT_UTILS_H