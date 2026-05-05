#pragma once

#include "AudioBuffer.h"
#include <optional>
#include <string>

namespace soundgen {

    // Tipos de onda disponibles
    // enum class (scoped enum) — evita colisiones de nombres
    // WaveType::Sine, no simplemente Sine
    enum class WaveType {
        Sine,
        Square,
        Saw
    };

    // Parámetros para la generación — agrupados en un struct
    // En lugar de pasar 5 argumentos sueltos a una función,
    // los agrupamos. Esto se llama "Parameter Object pattern".
    // Ventaja: si agregamos --amplitude mañana, no rompemos
    // ninguna firma de función existente.
    struct GeneratorConfig {
        WaveType waveType   = WaveType::Sine;
        double   frequency  = 440.0;   // Hz
        double   duration   = 1.0;     // segundos
        float    amplitude  = 0.8f;    // [0.0, 1.0]
        uint32_t sampleRate = 44100;   // Hz
    };

    class WaveGenerator {
    public:
        // Punto de entrada principal
        [[nodiscard]] static AudioBuffer generate(const GeneratorConfig& config);

        // Convierte "sine" - WaveType::Sine
        // Retorna std::nullopt si el string no es válido
        [[nodiscard]] static std::optional<WaveType> parseWaveType(const std::string& str);

    private:
        // Generadores internos — reciben phase en [0, 2π]
        // retornan sample en [-1.0, 1.0]
        [[nodiscard]] static float sineSample(double phase);
        [[nodiscard]] static float squareSample(double phase);
        [[nodiscard]] static float sawSample(double phase);
    };

} // namespace soundgen