#include <iostream>
#include <vector>
#include "../includes/mbs/frontend/lexer.h"
#include "../includes/mbs/frontend/parser.h"

int main() {
    std::cout << "\nmb-script v0.0.1\n" << std::endl;
    std::string cmd;

    // Infinite cmd loop
    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, cmd);
        std::cout << "CMD: '" << cmd << "'" << std::endl;

        if (cmd == "exit") {
            std::cout << "Bye!" << std::endl;
            break;
        }

        mbs::Parser parser;
        parser.parse(cmd);
        std::cout << parser.toString();
        // for (auto token : tokens) {
        //     std::cout << token << std::endl;
        // }
    }

    return 0;
}
