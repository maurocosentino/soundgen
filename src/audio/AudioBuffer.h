#pragma once

#include <vector>
#include <cstdint>

namespace soundgen {

    struct AudioBuffer {
        std::vector<float> samples;
        uint32_t sampleRate;
        uint16_t numChannels;

        [[nodiscard]] size_t size() const {
            return samples.size();
        }

        [[nodiscard]] double durationSeconds() const {
            if (sampleRate == 0) return 0.0;
            return static_cast<double>(samples.size()) / static_cast<double>(sampleRate);
        }
    };

} // namespace soundgen