# WAV_MAX_MIN_HZ

![License](https://img.shields.io/github/license/KOJIMEISTER/wav_max_min_hz)
![CMake](https://img.shields.io/badge/CMake-3.14%2B-blue.svg)
![C++](https://img.shields.io/badge/C++-20-blue.svg)

## Overview

**WAV_MAX_MIN_HZ** is a console-based application designed to analyze WAV audio files. It processes each channel of the WAV file and outputs the minimum and maximum frequencies of the sine wave signal detected in each channel.

## Features

- **Multi-Channel Analysis:** Supports WAV files with multiple audio channels.
- **Frequency Detection:** Accurately detects and reports the minimum and maximum frequencies of sine waves in each channel.
- **User-Friendly Console Interface:** Simple command-line usage for quick analysis.
- **Cross-Platform:** Built using C++20 and CMake for compatibility across different operating systems.

## Installation

### Prerequisites

- **C++20 Compiler:** Ensure you have a C++20 compatible compiler installed (e.g., GCC, Clang, MSVC).
- **CMake:** Version 3.14 or higher.

### Building from Source

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/KOJIMEISTER/wav_max_min_hz.git
   cd wav_max_min_hz
   ```

2. **Create a Build Directory:**
   ```bash
   mkdir build
   cd build
   ```

3. **Generate Build Files with CMake:**
   ```bash
   cmake ..
   ```

4. **Build the Project:**
   ```bash
   cmake --build .
   ```

   After a successful build, the executable `wavanalyze` (or `wavanalyze.exe` on Windows) will be available in the build directory.

## Usage

Run the executable from the command line, providing the path to the WAV file you wish to analyze.

```bash
./wavanalyze "path_to_your_file.wav"
```

### Example

```bash
./wavanalyze "C:/Music/sample.wav"
```

**Output:**
```
Channel #1 max-Hz: 440 min-Hz: 220
Channel #2 max-Hz: 450 min-Hz: 210
```

## License

This project is licensed under the [MIT License](LICENSE). You are free to use, modify, and distribute this software as per the terms of the license.

## Contributing

Contributions are welcome! If you have suggestions for improvements or found a bug, please open an issue or submit a pull request.

## Author

**Nikita** © 2024

## Contact

For any inquiries or feedback, please open an issue on the [GitHub repository](https://github.com/KOJIMEISTER/wav_max_min_hz).

```
