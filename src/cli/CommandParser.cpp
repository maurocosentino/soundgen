#include "CommandParser.h"

#include <iostream>
#include <stdexcept>
#include <string>

namespace soundgen {

ParsedCommand CommandParser::parse(int argc, char* argv[]) {

    if (argc < 2) {
        printUsage(argv[0]);
        throw std::invalid_argument("Falta el subcomando");
    }

    ParsedCommand cmd;
    cmd.subcommand = argv[1];

    if (cmd.subcommand == "--help" || cmd.subcommand == "-h") {
        printUsage(argv[0]);
        throw std::invalid_argument("__help__");
    }

    if (cmd.subcommand != "generate") {
        throw std::invalid_argument(
            "Subcomando desconocido: '" + cmd.subcommand + "'"
        );
    }

    // Parseamos flags: --flag valor
    for (int i = 2; i < argc; ++i) {
        const std::string flag(argv[i]);

        if (flag == "--wave" && i + 1 < argc) {
            ++i;
            auto maybeWave = WaveGenerator::parseWaveType(argv[i]);
            if (!maybeWave.has_value()) {
                throw std::invalid_argument(
                    "Tipo de onda invalido: '" + std::string(argv[i]) +
                    "'. Opciones: sine, square, saw"
                );
            }
            cmd.generatorConfig.waveType = *maybeWave;

        } else if (flag == "--freq" && i + 1 < argc) {
            ++i;
            try {
                cmd.generatorConfig.frequency = std::stod(argv[i]);
            } catch (...) {
                throw std::invalid_argument(
                    "Frecuencia invalida: " + std::string(argv[i])
                );
            }
            if (cmd.generatorConfig.frequency <= 0.0)
                throw std::invalid_argument("La frecuencia debe ser positiva");

        } else if (flag == "--duration" && i + 1 < argc) {
            ++i;
            try {
                cmd.generatorConfig.duration = std::stod(argv[i]);
            } catch (...) {
                throw std::invalid_argument(
                    "Duracion invalida: " + std::string(argv[i])
                );
            }
            if (cmd.generatorConfig.duration <= 0.0)
                throw std::invalid_argument("La duracion debe ser positiva");

        } else if (flag == "--amplitude" && i + 1 < argc) {
            ++i;
            try {
                cmd.generatorConfig.amplitude = std::stof(argv[i]);
            } catch (...) {
                throw std::invalid_argument(
                    "Amplitud invalida: " + std::string(argv[i])
                );
            }
            if (cmd.generatorConfig.amplitude < 0.0f ||
                cmd.generatorConfig.amplitude > 1.0f)
                throw std::invalid_argument("La amplitud debe estar entre 0.0 y 1.0");

        } else if (flag == "--output" && i + 1 < argc) {
            ++i;
            cmd.outputPath = argv[i];

        } else if (flag == "--help" || flag == "-h") {
            printUsage(argv[0]);
            throw std::invalid_argument("__help__");

        } else {
            throw std::invalid_argument("Flag desconocido: " + flag);
        }
    }

    return cmd;
}

void CommandParser::printUsage(const std::string& programName) {
    std::cout << "\nSoundGen CLI — Generador de audio WAV\n\n"
              << "Uso:\n"
              << "  " << programName << " generate [opciones]\n\n"
              << "Opciones:\n"
              << "  --wave      <sine|square|saw>  Tipo de onda (default: sine)\n"
              << "  --freq      <Hz>               Frecuencia en Hz (default: 440)\n"
              << "  --duration  <segundos>         Duracion (default: 1.0)\n"
              << "  --amplitude <0.0-1.0>          Amplitud (default: 0.8)\n"
              << "  --output    <archivo.wav>      Archivo de salida (default: output.wav)\n"
              << "  --help, -h                     Muestra esta ayuda\n\n"
              << "Ejemplos:\n"
              << "  " << programName << " generate --wave sine --freq 440 --duration 2 --output tone.wav\n"
              << "  " << programName << " generate --wave square --freq 110 --duration 1 --output bass.wav\n"
              << "  " << programName << " generate --wave saw --freq 880 --amplitude 0.5 --output lead.wav\n\n";
}

} // namespace soundgen