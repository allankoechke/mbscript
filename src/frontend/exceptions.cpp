#include "../../includes/mbs/frontend/exceptions.h"

mbs::LexerException::LexerException(const std::string &msg, Token token)
    : std::runtime_error(msg),
      m_token(std::move(token)),
      m_msg(msg),
      m_err(std::format("Lexer Error: {}\nLine: {}, Start: {}, End: {}",
                        m_msg == std::string{'\0'}
                            ? ""
                            : m_msg,
                        m_token.pos.line, m_token.pos.start, m_token.pos.end)) {
}

char const *mbs::LexerException::what() const noexcept {
    return m_err.c_str();
}
