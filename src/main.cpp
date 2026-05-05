#include <iostream>
#include <stdexcept>
#include "cli/CommandParser.h"
#include "audio/WaveGenerator.h"
#include "wav/WavWriter.h"

int main(int argc, char* argv[]) {
    using namespace soundgen;

    try {
        // 1. Parsear argumentos
        const ParsedCommand cmd = CommandParser::parse(argc, argv);

        // 2. Generar audio
        std::cout << "Generando " << cmd.generatorConfig.duration << "s de audio"
                  << " a " << cmd.generatorConfig.frequency << " Hz...\n";

        const AudioBuffer buffer = WaveGenerator::generate(cmd.generatorConfig);

        // 3. Escribir WAV
        std::cout << "Escribiendo: " << cmd.outputPath << "\n";
        WavWriter::write(buffer, cmd.outputPath);

        std::cout << "Listo! ("
                  << buffer.size() << " samples, "
                  << buffer.durationSeconds() << "s)\n";

        return 0;

    } catch (const std::invalid_argument& e) {
        const std::string msg(e.what());
        if (msg == "__help__") return 0;  // salida limpia
        std::cerr << "Error: " << msg << "\n";
        return 1;

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
    }
}