#pragma once

#include "audio/AudioBuffer.h"
#include <string>

namespace soundgen {

    class WavWriter {
    public:
        // Escribe un AudioBuffer a disco en formato WAV PCM 16-bit
        // Lanza std::runtime_error si no puede crear el archivo
        static void write(const AudioBuffer& buffer, const std::string& filePath);

    private:
        static constexpr uint16_t PCM_FORMAT      = 1;
        static constexpr uint16_t BITS_PER_SAMPLE = 16;
        static constexpr float    INT16_MAX_F     = 32767.0f;

        // Escribe cualquier tipo como little-endian al stream
        template<typename T>
        static void writeLE(std::ostream& out, T value);
    };

} // namespace soundgen