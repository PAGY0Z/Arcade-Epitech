/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** main
*/

#include "AException.hpp"
#include "Core.hpp"

int main(int argc, char **argv)
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "USAGE: ./arcade graphic_library_path.so" << std::endl;
            throw arcade::MainException("Invalid Argument number", FILE_DATA);
        }
        return arcade::Core(argv[1]).run();
    }
    catch (const arcade::AException &except)
    {
        std::cerr << except.what() << std::endl;
        exit(except.getReturnValue());
    }
    return 0;
}
