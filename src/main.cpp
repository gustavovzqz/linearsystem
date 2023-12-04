#include "linearsystem.h"
#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        LinearSystem d{};
        d.outputData();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        // Adicione o código de tratamento de exceção aqui, se necessário
    }

    return 0;
}
