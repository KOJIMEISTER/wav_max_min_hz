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
        char chunkId[4];
        unsigned long chunkSize;
        char format[4];
        char subchunk1Id[4];
        unsigned long subchunk1Size;
        unsigned short audioFormat;
        unsigned short numChannels;
        unsigned long sampleRate;
        // Кол-во байт, переданных за секунду воспроизведения
        unsigned long byteRate;
        // Количество байт для блока из сэмплов аудиодорожек
        unsigned short blockAlign;
        unsigned short bitsPerSample;
        char subchunk2Id[4];
        // Всего байт, выделенных под звук
        unsigned long subchunk2Size;
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

