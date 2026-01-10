#ifndef MBSCRIPT_EXCEPTIONS_H
#define MBSCRIPT_EXCEPTIONS_H
#include <string>

#include "token.h"

namespace mbs {
    struct LexerException : std::runtime_error {
        LexerException(const std::string &msg, Token token);

        [[nodiscard]] char const *what() const noexcept override;

    private:
        Token m_token;
        std::string m_msg;
        std::string m_err;
    };
}

#endif //MBSCRIPT_EXCEPTIONS_H