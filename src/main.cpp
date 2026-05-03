#include <iostream>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Uso: soundgen <comando> [opciones]\n";
        std::cout << "Ejemplo: soundgen generate --wave sine --freq 440\n";
        return 1;
    }

    const std::string subcommand = argv[1];

    if (subcommand == "generate") {
        std::cout << "Comando: generate (aún no implementado)\n";
    } else {
        std::cerr << "Error: comando desconocido '" << subcommand << "'\n";
        return 1;
    }

    return 0;
}