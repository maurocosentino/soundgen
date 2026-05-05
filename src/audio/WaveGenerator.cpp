#include "WaveGenerator.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>

// M_PI no es estándar C++ — lo definimos nosotros
// Más portable que depender de extensiones GNU
static constexpr double PI     = 3.14159265358979323846;
static constexpr double TWO_PI = 2.0 * PI;

namespace soundgen {

AudioBuffer WaveGenerator::generate(const GeneratorConfig& config) {

    // Validación antes de hacer cualquier cosa
    if (config.frequency <= 0.0)
        throw std::invalid_argument("La frecuencia debe ser positiva");
    if (config.duration <= 0.0)
        throw std::invalid_argument("La duracion debe ser positiva");
    if (config.sampleRate == 0)
        throw std::invalid_argument("El sample rate no puede ser cero");

    // Calculamos cuántos samples necesitamos
    const auto totalSamples = static_cast<size_t>(
        config.duration * static_cast<double>(config.sampleRate)
    );

    // Construimos el buffer
    AudioBuffer buffer;
    buffer.sampleRate  = config.sampleRate;
    buffer.numChannels = 1;
    buffer.samples.reserve(totalSamples); // pre-aloca memoria

    // Phase accumulator
    const double phaseIncrement = TWO_PI * config.frequency
                                  / static_cast<double>(config.sampleRate);
    double phase = 0.0;

    for (size_t i = 0; i < totalSamples; ++i) {

        float sample = 0.0f;

        switch (config.waveType) {
            case WaveType::Sine:   sample = sineSample(phase);   break;
            case WaveType::Square: sample = squareSample(phase); break;
            case WaveType::Saw:    sample = sawSample(phase);    break;
        }

        // Aplicamos amplitud y clampeamos por seguridad
        sample = std::clamp(sample * config.amplitude, -1.0f, 1.0f);
        buffer.samples.push_back(sample);

        // Avanzamos la fase
        phase += phaseIncrement;

        // Wrap: mantenemos phase en [0, 2π]
        // Sin esto, después de millones de samples
        // la precisión del float se degrada
        if (phase >= TWO_PI)
            phase -= TWO_PI;
    }

    return buffer;
}

// --- Generadores privados ---

float WaveGenerator::sineSample(double phase) {
    return static_cast<float>(std::sin(phase));
}

float WaveGenerator::squareSample(double phase) {
    return (phase < PI) ? 1.0f : -1.0f;
}

float WaveGenerator::sawSample(double phase) {
    return static_cast<float>(1.0 - (phase / PI));
}

std::optional<WaveType> WaveGenerator::parseWaveType(const std::string& str) {
    if (str == "sine")   return WaveType::Sine;
    if (str == "square") return WaveType::Square;
    if (str == "saw")    return WaveType::Saw;
    return std::nullopt;
}

} // namespace soundgen