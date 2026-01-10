#ifndef MBS_LEXER_H
#define MBS_LEXER_H

#include <format>
#include <string>
#include <vector>

#include "token.h"

namespace mbs {
    struct Lexer {
        std::vector<Token> tokens;
        const std::vector<Token> &lex(const std::string &source);

    private:
        void lexNumericals();
        void lexStrings();
        void lexIdentifiers();
        void lexWhitespace();
        void lexOperators();

        void makeToken(const std::string &val, TokenType type, int start);
        void makeToken(const std::string &val, TokenType type, int start, int line);

        [[nodiscard]] bool isEOF() const;
        [[nodiscard]] char peek(int offset = 0) const;

        char advance();
        void expect(char c, const std::string &err);

        int m_current = 0, m_line = 1, m_index = 0;
        std::string m_src; // Source string to lex
    };
};

#endif //MBS_LEXER_H
