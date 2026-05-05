# SoundGen CLI

Command-line tool for generating WAV audio files from basic waveforms. Built in C++17 with no external dependencies.

## Build

**Requirements:** CMake 3.16+, GCC or Clang with C++17 support.

```bash
git clone https://github.com/maurocosentino/soundgen-cli
cd soundgen-cli
mkdir build && cd build
cmake ..
make
```

## Usage

```bash
./soundgen generate [options]
```

| Flag | Description | Default |
|------|-------------|---------|
| `--wave` | Waveform type: `sine`, `square`, `saw` | `sine` |
| `--freq` | Frequency in Hz | `440` |
| `--duration` | Duration in seconds | `1.0` |
| `--amplitude` | Volume level [0.0–1.0] | `0.8` |
| `--output` | Output file path | `output.wav` |

## Examples

```bash
./soundgen generate --wave sine --freq 440 --duration 2 --output tone.wav
./soundgen generate --wave square --freq 110 --duration 1 --output bass.wav
./soundgen generate --wave saw --freq 880 --amplitude 0.5 --output lead.wav
```

## Architecture

```
src/
├── cli/      → Parses argv into structured data
├── audio/    → Generates float sample buffers
└── wav/      → Serializes buffers to PCM WAV files
```

## Roadmap

- [ ] ADSR envelope
- [ ] Mix multiple waveforms
- [ ] Basic effects (gain, distortion)
- [ ] WAV file reading