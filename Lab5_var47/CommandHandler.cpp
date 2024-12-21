#include <iostream>
#include <sstream>


void HandleCommand(const std::string& command) {

    std::istringstream iss(command);
    std::string main_subcommand, id, subcommand;
    iss >> main_subcommand >> id >> subcommand;

    if (main_subcommand == "Create") {
        std::cout << "Выполняется первая подкоманда Create" << std::endl;
    } else if (main_subcommand == "Exec") {
        std::cout << "Выполняется первая подкоманда Exec" << std::endl;
    } else if (main_subcommand == "Kill") {
        std::cout << "Выполняется первая подкоманда Kill" << std::endl;
    } else {
        std::cout << "Неизвестная первая подкоманда" << std::endl;
        exit(1);
    }

}
