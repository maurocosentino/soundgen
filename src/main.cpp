#include <iostream>
#include "audio/AudioBuffer.h"
#include "audio/WaveGenerator.h"
#include "wav/WavWriter.h"

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
        config.duration  = 2.0;

        std::cout << "Generando audio...\n";
        soundgen::AudioBuffer buffer = soundgen::WaveGenerator::generate(config);

        std::cout << "Samples: " << buffer.size() << "\n";
        std::cout << "Duracion: " << buffer.durationSeconds() << "s\n";

        std::cout << "Escribiendo tone.wav...\n";
        soundgen::WavWriter::write(buffer, "tone.wav");

        std::cout << "Listo!\n";

    } else {
        std::cerr << "Error: comando desconocido '" << subcommand << "'\n";
        return 1;
    }

    return 0;
}