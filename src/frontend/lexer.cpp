#include "../../includes/mbs/frontend/lexer.h"
#include "../../includes/mbs/frontend/exceptions.h"

#include <iostream>

const std::vector<mbs::Token> &mbs::Lexer::lex(const std::string &source) {
    tokens.clear();
    m_src = source;
    m_line = 1;
    m_current = 0;

    // Iterate over all chars
    while (!isEOF()) {
        if (std::isdigit(peek())) lexNumericals();
        else if (peek() == '"' || peek() == '\'') lexStrings();
        else if (std::isalpha(peek()) || peek() == '_') lexIdentifiers();
        else if (std::isspace(peek())) lexWhitespace();
        else if (peek() == '(') {
            advance();
            makeToken("(", TokenType::TOK_OPEN_PAREN, m_current - 1);
        } else if (peek() == ')') {
            advance();
            makeToken(")", TokenType::TOK_CLOSE_PAREN, m_current - 1);
        } else if (peek() == '.') {
            advance();
            makeToken(".", TokenType::TOK_DOT, m_current - 1);
        } else if (peek() == '?') {
            advance();
            makeToken("?", TokenType::TOK_QUESTION, m_current - 1);
        } else if (peek() == ':') {
            advance();
            makeToken(":", TokenType::TOK_COLON, m_current - 1);
        } else lexOperators();
    }

    // Add EOF token
    makeToken("EOF", TokenType::TOK_EOF, m_current);

    return tokens;
}

void mbs::Lexer::lexNumericals() {
    const int _start = m_current;
    std::string num;

    // TODO check for num.num.num ...

    // Support the following structure ..
    // 123 // 123.456 // 123.to_u8() // 123.456.abs() // 123.123.floor() // etc
    while (std::isdigit(peek()) || peek() == '.') {
        num += advance();
    }

    makeToken(num, TokenType::TOK_NUMBER, _start);
}

void mbs::Lexer::lexStrings() {
    // Support both single quoted strings 'abc' and
    // double-quoted strings "abc"
    const int _start = m_current, _line = m_line;
    std::string str;

    const char quote = advance(); // Consume opening quotation mark
    while (!isEOF() && peek() != quote) {
        // Check for strings spanning multiple lines
        if (peek() == '\n') {
            m_line++;
            m_index = 0;
        }
        str += advance();
    }

    expect(quote, std::format("Expected `{}` to terminate string starting at line {}, pos {}",
                              quote, _line, _start));

    tokens.emplace_back(
        Token{
            .value = str,
            .pos{.start = _start, .end = m_current, .line = _line},
            .type = TokenType::TOK_STRING
        }
    );
}

void mbs::Lexer::lexIdentifiers() {
    // Support c style token naming
    const int _start = m_current, _line = m_line;
    std::string ident;

    while (!isEOF() && std::isalnum(peek()) || peek() == '_') {
        ident += advance();
    }

    if (ident == "true")
        makeToken(ident, TokenType::TOK_TRUE, _start);
    else if (ident == "false")
        makeToken(ident, TokenType::TOK_FALSE, _start);
    else if (ident == "nil")
        makeToken(ident, TokenType::TOK_NULL, _start);
    else
        makeToken(ident, TokenType::TOK_IDENT, _start);
}

void mbs::Lexer::lexWhitespace() {
    while (isspace(peek())) {
        if (peek() == '\n') {
            m_line++;
            m_index = 0;
        }
        advance(); // Move to the next token
    }
}

void mbs::Lexer::lexOperators() {
    const int _start = m_current;
    const char op = advance();

    if (op == '+') {
        if (peek() == '+') {
            // ++ operator
            makeToken("++", TokenType::TOK_INC, _start);
            advance(); // Consume last '+'
        } else {
            // + operator
            makeToken("+", TokenType::TOK_PLUS, _start);
        }
    } else if (op == '-') {
        if (peek() == '-') {
            // -- operator
            makeToken("--", TokenType::TOK_DEC, _start);
            advance(); // Consume last '-'
        } else {
            // - operator
            makeToken("-", TokenType::TOK_MINUS, _start);
        }
    } else if (op == '*') {
        if (peek() == '*') {
            // ** operator
            makeToken("**", TokenType::TOK_POW, _start);
            advance(); // Consume last '*'
        } else {
            // * operator
            makeToken("*", TokenType::TOK_MUL, _start);
        }
    } else if (op == '/') {
        // / operator
        makeToken("/", TokenType::TOK_DIV, _start);
    } else if (op == '^') {
        // ^ operator
        makeToken("^", TokenType::TOK_POW, _start);
    } else if (op == '%') {
        // % operator
        makeToken("%", TokenType::TOK_MOD, _start);
    } else if (op == '=') {
        if (peek() == '=') {
            // == operator
            makeToken("==", TokenType::TOK_EQUALS, _start);
            advance(); // Consume last '='
        } // For now, we don't support assignment OP
        else {
            throw LexerException{
                "Assignment operator not allowed!",
                {
                    .value = std::string{peek()},
                    .pos = {m_current, m_current, m_line}
                }
            };
        }
    } else if (op == '>') {
        if (peek() == '=') {
            // >= operator
            makeToken(">=", TokenType::TOK_GREATER_OR_EQUALS, _start);
            advance(); // Consume last '='
        } else {
            // > operator
            makeToken(">", TokenType::TOK_GREATER, _start);
        }
    } else if (op == '<') {
        if (peek() == '=') {
            // <= operator
            makeToken("<=", TokenType::TOK_LESS_OR_EQUALS, _start);
            advance(); // Consume last '*'
        } else {
            // < operator
            makeToken("<", TokenType::TOK_LESS, _start);
        }
    } else if (op == '!') {
        if (peek() == '=') {
            // != operator
            makeToken("!=", TokenType::TOK_NOT_EQUALS, _start);
            advance(); // Consume last '='
        } else {
            // ! operator
            makeToken("!", TokenType::TOK_NOT, _start);
        }
    } else if (op == '&') {
        if (peek() == '&') {
            // && operator
            makeToken("&&", TokenType::TOK_AND, _start);
            advance(); // Consume last '&'
        } else {
            // Throw an error, we expected a second '&'
            throw LexerException{
                "Expected `&` after `&` token to form BITWISE AND token!",
                {
                    .value = std::string{peek()},
                    .pos = {m_current, m_current, m_line}
                }
            };
        }
    } else if (op == '|') {
        if (peek() == '|') {
            // || operator
            makeToken("||", TokenType::TOK_OR, _start);
            advance(); // Consume last '|'
        } else {
            // Throw an error, we expected a second '|'
            throw LexerException{
                "Expected `|` after `|` token to form BITWISE OR token!",
                {
                    .value = std::string{peek()},
                    .pos = {m_current, m_current, m_line}
                }
            };
        }
    } else {
        // If we reached here, probably having an invalid token!
        // Let's throw a Lexer exception.
        throw LexerException{
            "Unknown Token",
            {
                .value = std::string{peek()},
                .pos = {m_current, m_current, m_line}
            }
        };
    }
}

void mbs::Lexer::makeToken(const std::string &val, const TokenType type, const int start) {
    makeToken(val, type, start, m_line);
}

void mbs::Lexer::makeToken(const std::string &val, const TokenType type, const int start, const int line) {
    tokens.emplace_back(Token{
        .value = val,
        .pos{.start = start, .end = m_current, .line = line},
        .type = type
    });
}

bool mbs::Lexer::isEOF() const {
    return m_current >= m_src.size();
}

char mbs::Lexer::peek(const int offset) const {
    if (isEOF() || m_current + offset >= m_src.size())
        return '\0';

    return m_src[m_current + offset];
}

char mbs::Lexer::advance() {
    return m_src[m_current++];
}

void mbs::Lexer::expect(const char c, const std::string &err) {
    if (!isEOF() && peek() == c) {
        advance();
        return;
    }

    throw LexerException{
        err.empty() ? std::format("Expected `{}` token!", c) : err,
        Token{
            .value = std::string{peek()},
            .pos{
                .start = m_current,
                .end = m_current,
                .line = m_line
            }
        }
    };
}
