#pragma once
#include <filesystem>
#include <string>
#include <fstream>
#include <vector>

class WavAnalyzer
{
    struct AnalayzeData
    {
        int MinSamples = 0;
        int MaxSamples = 0;
        int CounterViaZero = 0;
        int CounterSamples = 0;
        float LastAmplitude = 0.0f;
    };

public:

	WavAnalyzer(std::string Path) : PathToWav(Path) {};
	~WavAnalyzer();

	struct AnalyzeRes
	{
		std::vector<std::pair<unsigned int, unsigned int>> ResArr;
	};

    struct WavHeader
    {
        char chunkId[4]{0,0,0,0};
        __uint32_t chunkSize=0;
        char format[4]{0,0,0,0};
        char subchunk1Id[4]{0,0,0,0};
        __uint32_t subchunk1Size = 0;
        __uint16_t audioFormat = 0;
        __uint16_t numChannels = 0;
        __uint32_t sampleRate = 0;
        // Кол-во байт, переданных за секунду воспроизведения
        __uint32_t byteRate = 0;
        // Количество байт для блока из сэмплов аудиодорожек
        __uint16_t blockAlign = 0;
        __uint16_t bitsPerSample = 0;
        char subchunk2Id[4]{0,0,0,0};
        // Всего байт, выделенных под звук
        __uint32_t subchunk2Size = 0;
    };

	AnalyzeRes Analyze();

private:

    std::filesystem::path PathToWav;
    std::ifstream File;
    WavHeader Header{};
    unsigned int blocksAmm = 0;

    void Open();
    void Close();
    float GetAmplitude(bool* BuffBlock);
};

