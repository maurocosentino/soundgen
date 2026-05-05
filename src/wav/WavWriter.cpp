#include "WavWriter.h"

#include <fstream>
#include <stdexcept>
#include <cstring>

namespace soundgen {

template<typename T>
void WavWriter::writeLE(std::ostream& out, T value) {
    // Reinterpretamos el valor como array de bytes
    // y los escribimos en orden little-endian
    char bytes[sizeof(T)];
    std::memcpy(bytes, &value, sizeof(T));
    out.write(bytes, sizeof(T));
}

void WavWriter::write(const AudioBuffer& buffer, const std::string& filePath) {

    if (buffer.samples.empty())
        throw std::runtime_error("No se puede escribir un buffer vacio");

    // std::ios::binary es crítico — sin esto en Windows
    // los bytes '\n' se traducen a '\r\n', corrompiendo el binario
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("No se pudo crear el archivo: " + filePath);

    // --- Calculamos tamaños ---
    const uint32_t numSamples    = static_cast<uint32_t>(buffer.samples.size());
    const uint16_t blockAlign    = static_cast<uint16_t>(
                                       buffer.numChannels * (BITS_PER_SAMPLE / 8));
    const uint32_t byteRate      = buffer.sampleRate * blockAlign;
    const uint32_t dataChunkSize = numSamples * (BITS_PER_SAMPLE / 8);
    const uint32_t fmtChunkSize  = 16;
    const uint32_t riffChunkSize = 4               // "WAVE"
                                 + 8 + fmtChunkSize  // "fmt " chunk
                                 + 8 + dataChunkSize; // "data" chunk

    // --- RIFF header ---
    file.write("RIFF", 4);
    writeLE(file, riffChunkSize);
    file.write("WAVE", 4);

    // --- fmt chunk ---
    file.write("fmt ", 4);
    writeLE(file, fmtChunkSize);
    writeLE(file, PCM_FORMAT);
    writeLE(file, buffer.numChannels);
    writeLE(file, buffer.sampleRate);
    writeLE(file, byteRate);
    writeLE(file, blockAlign);
    writeLE(file, BITS_PER_SAMPLE);

    // --- data chunk ---
    file.write("data", 4);
    writeLE(file, dataChunkSize);

    // --- samples: float → int16_t ---
    for (float sample : buffer.samples) {
        const auto pcm = static_cast<int16_t>(sample * INT16_MAX_F);
        writeLE(file, pcm);
    }

    if (!file.good())
        throw std::runtime_error("Error escribiendo el archivo WAV");
}

} // namespace soundgen