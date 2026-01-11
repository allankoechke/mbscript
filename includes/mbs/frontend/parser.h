#ifndef MBS_PARSER_H
#define MBS_PARSER_H

#include <iostream>
#include <string>
#include "ast.h"
#include "lexer.h"
#include "token.h"

namespace mbs {
    class Parser {
    public:
        Parser() = default;

        void parse(const std::string &input) {
            m_tokens = lexer.lex(input);
            while (!isEOF()) {
                m_root.addNode(parseExpr());
            }
        }

        std::string toString() {
            return m_root.toString();
        }

    private:
        std::unique_ptr<AstNode> parseExpr() {
            return parseOr();
        }

        std::unique_ptr<AstNode> parseOr() {
            auto left = parseAnd();
            while (!isEOF() && (peek().type == TokenType::TOK_OR || peek().type == TokenType::TOK_AND)) {
                auto op = advance().value;
                auto right = parseAnd();
                left = std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
            }
            return left;
        }

        std::unique_ptr<AstNode> parseAnd() {
            auto left = parseEquality();
            while (!isEOF() && (peek().type == TokenType::TOK_OR || peek().type == TokenType::TOK_AND)) {
                auto op = advance().value;
                auto right = parseEquality();
                left = std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
            }
            return left;
        }

        std::unique_ptr<AstNode> parseEquality() {
            auto left = parseRelational();
            while (!isEOF() && (peek().type == TokenType::TOK_EQUALS || peek().type == TokenType::TOK_NOT_EQUALS)) {
                auto op = advance().value;
                auto right = parseRelational();
                left = std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
            }
            return left;
        }

        std::unique_ptr<AstNode> parseRelational() {
            auto left = parseAdd();
            while (!isEOF()
                   && (
                       peek().type == TokenType::TOK_LESS
                       || peek().type == TokenType::TOK_LESS_OR_EQUALS
                       || peek().type == TokenType::TOK_GREATER
                       || peek().type == TokenType::TOK_GREATER_OR_EQUALS
                   )
            ) {
                auto op = advance().value;
                auto right = parseAdd();
                left = std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
            }
            return left;
        }

        std::unique_ptr<AstNode> parseAdd() {
            auto left = parseMul();

            while (!isEOF()
                   && (
                       peek().type == TokenType::TOK_PLUS
                       || peek().type == TokenType::TOK_MINUS
                   )
            ) {
                auto op = advance().value;
                auto right = parseMul();
                left = std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
            }

            return left;
        }

        std::unique_ptr<AstNode> parseMul() {
            auto left = parseExponents();

            while (!isEOF()
                   && (
                       peek().type == TokenType::TOK_MUL
                       || peek().type == TokenType::TOK_DIV
                       || peek().type == TokenType::TOK_MOD
                   )
            ) {
                auto op = advance().value;
                auto right = parseExponents();
                left = std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
            }

            return left;
        }

        std::unique_ptr<AstNode> parseExponents() {
            auto left = parseUnary();
            if (!isEOF() && (peek().type == TokenType::TOK_POW)) {
                auto op = advance().value;
                auto right = parseExponents(); // Right Associative
                return std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
            }

            return left;
        }

        std::unique_ptr<AstNode> parseUnary() {
            if (
                !isEOF() && (
                    peek().type == TokenType::TOK_MINUS
                    || peek().type == TokenType::TOK_PLUS
                    || peek().type == TokenType::TOK_NOT
                )) {
                auto op = advance().value;
                auto right = parseUnary(); // Right Associative
                return std::make_unique<UnaryExpr>(std::move(right), op);
            }
            return parsePrimary();
        }

        std::unique_ptr<AstNode> parsePrimary() {
            switch (peek().type) {
                case TokenType::TOK_NULL:
                    return parseNull();
                case TokenType::TOK_NUMBER:
                    return parseNumber();
                case TokenType::TOK_STRING:
                    return parseString();
                case TokenType::TOK_IDENT:
                    return parseIdent();
                case TokenType::TOK_TRUE:
                case TokenType::TOK_FALSE:
                    return parseBool();
                case TokenType::TOK_OPEN_PAREN: {
                    auto open_paren = advance(); // Consume open paren
                    auto left = parseExpr();
                    expect(TokenType::TOK_CLOSE_PAREN,
                           std::format("Expected `)` closing parens to match one on line {}",
                                       open_paren.pos.line
                           )
                    );
                    return left;
                }
                default: {
                    throw std::runtime_error(std::format("Unsupported Token: {}", tokenTypeToString(peek().type)));
                };
            }
        }

        std::unique_ptr<AstNode> parseNull() {
            advance();
            return std::make_unique<NullLiteral>();
        }

        std::unique_ptr<AstNode> parseNumber() {
            try {
                double num = std::stof(advance().value);
                return std::make_unique<NumberLiteral>(num);
            } catch (const std::exception &e) {
                std::cerr << "Parser Error: " << e.what() << std::endl;
                throw;
            }
        }

        std::unique_ptr<AstNode> parseString() {
            return std::make_unique<StringLiteral>(advance().value);
        }

        std::unique_ptr<AstNode> parseIdent() {
            return std::make_unique<IdentifierExpr>(advance().value);
        }

        std::unique_ptr<AstNode> parseBool() {
            return std::make_unique<BooleanLiteral>(advance().type == TokenType::TOK_TRUE);
        }

        bool isEOF() {
            return m_tokens.empty() || peek().type == TokenType::TOK_EOF || m_current >= m_tokens.size();
        }

        const Token &peek() {
            return m_tokens.at(m_current);
        }

        const Token &advance() {
            return m_tokens.at(m_current++);
        }

        void expect(const TokenType &tokenType, const std::string &error) {
            if (isEOF() || peek().type != tokenType) {
                throw std::runtime_error(error);
            }

            advance();
        }

        AstRoot m_root;
        std::vector<Token> m_tokens;

        Lexer lexer;
        int m_current = 0;
    };
}

#endif //MBS_PARSER_H
