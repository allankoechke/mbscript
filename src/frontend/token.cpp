#include "../../includes/mbs/frontend/token.h"

std::string mbs::toString(const TokenType tt) {
    std::string name;
    switch (tt) {
        case TokenType::TOK_STRING:
            name = "TokenType::TOK_STRING";
            break;
        case TokenType::TOK_NUMBER:
            name = "TokenType::TOK_NUMBER";
            break;
        case TokenType::TOK_TRUE:
            name = "TokenType::TOK_TRUE";
            break;
        case TokenType::TOK_FALSE:
            name = "TokenType::TOK_FALSE";
            break;
        case TokenType::TOK_NULL:
            name = "TokenType::TOK_NULL";
            break;
        case TokenType::TOK_IDENT:
            name = "TokenType::TOK_IDENT";
            break;
        case TokenType::TOK_OPEN_PAREN:
            name = "TokenType::TOK_OPEN_PAREN";
            break;
        case TokenType::TOK_CLOSE_PAREN:
            name = "TokenType::TOK_CLOSE_PAREN";
            break;
        case TokenType::TOK_DOT:
            name = "TokenType::TOK_DOT";
            break;
        case TokenType::TOK_COLON:
            name = "TokenType::TOK_COLON";
            break;
        case TokenType::TOK_COMMA:
            name = "TokenType::TOK_COMMA";
            break;
        case TokenType::TOK_QUESTION:
            name = "TokenType::TOK_QUESTION";
            break;
        case TokenType::TOK_NEGATE:
            name = "TokenType::TOK_NEGATE";
            break;
        case TokenType::TOK_NOT:
            name = "TokenType::TOK_NOT";
            break;
        case TokenType::TOK_INC:
            name = "TokenType::TOK_INC";
            break;
        case TokenType::TOK_DEC:
            name = "TokenType::TOK_DEC";
            break;
        case TokenType::TOK_PLUS:
            name = "TokenType::TOK_PLUS";
            break;
        case TokenType::TOK_MINUS:
            name = "TokenType::TOK_MINUS";
            break;
        case TokenType::TOK_MUL:
            name = "TokenType::TOK_MUL";
            break;
        case TokenType::TOK_DIV:
            name = "TokenType::TOK_DIV";
            break;
        case TokenType::TOK_MOD:
            name = "TokenType::TOK_MOD";
            break;
        case TokenType::TOK_POW:
            name = "TokenType::TOK_POW";
            break;
        case TokenType::TOK_EQUALS:
            name = "TokenType::TOK_EQUALS";
            break;
        case TokenType::TOK_NOT_EQUALS:
            name = "TokenType::TOK_NOT_EQUALS";
            break;
        case TokenType::TOK_LESS:
            name = "TokenType::TOK_LESS";
            break;
        case TokenType::TOK_GREATER:
            name = "TokenType::TOK_GREATER";
            break;
        case TokenType::TOK_LESS_OR_EQUALS:
            name = "TokenType::TOK_LESS_OR_EQUALS";
            break;
        case TokenType::TOK_GREATER_OR_EQUALS:
            name = "TokenType::TOK_GREATER_OR_EQUALS";
            break;
        case TokenType::TOK_AND:
            name = "TokenType::TOK_AND";
            break;
        case TokenType::TOK_OR:
            name = "TokenType::TOK_OR";
            break;
        case TokenType::TOK_EOF:
            name = "TokenType::TOK_EOF";
            break;
        default:
            name = "TokenType::TOK_INVALID";
    }

    return name;
}
