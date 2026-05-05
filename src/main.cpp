#include <iostream>
#include "audio/AudioBuffer.h"
#include "audio/WaveGenerator.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Uso: soundgen <comando> [opciones]\n";
        return 1;
    }

    const std::string subcommand = argv[1];

    if (subcommand == "generate") {

        soundgen::GeneratorConfig config;
        config.waveType  = soundgen::WaveType::Sine;
        config.frequency = 440.0;
        config.duration  = 1.0;

        soundgen::AudioBuffer buffer = soundgen::WaveGenerator::generate(config);

        std::cout << "Buffer generado:\n";
        std::cout << "  Samples: "   << buffer.size()            << "\n";
        std::cout << "  Duracion: "  << buffer.durationSeconds() << "s\n";
        std::cout << "  Primeros 5 valores:\n";

        for (size_t i = 0; i < 5; ++i) {
            std::cout << "    [" << i << "] = " << buffer.samples[i] << "\n";
        }

    } else {
        std::cerr << "Error: comando desconocido '" << subcommand << "'\n";
        return 1;
    }

    return 0;
}