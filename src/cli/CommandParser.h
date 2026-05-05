#pragma once

#include "audio/WaveGenerator.h"
#include <string>

namespace soundgen {

    // Resultado del parsing — datos listos para usar
    struct ParsedCommand {
        std::string     subcommand;
        GeneratorConfig generatorConfig;
        std::string     outputPath = "output.wav";
    };

    class CommandParser {
    public:
        // Parsea argc/argv y retorna un ParsedCommand listo
        // Lanza std::invalid_argument si algo es inválido
        [[nodiscard]] static ParsedCommand parse(int argc, char* argv[]);

        // Imprime instrucciones de uso
        static void printUsage(const std::string& programName);
    };

} // namespace soundgen