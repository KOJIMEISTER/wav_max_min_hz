#include "WavAnalyzer.h"
#include <iostream>

void WavAnalyzer::Open()
{
	if (!File.is_open())
	{
        File.open(PathToWav, std::ios::binary | std::ios::in);
		if (!File.is_open())
		{
			std::cout << "\nWrong file path or name!";
		}
	}
}

void WavAnalyzer::Close()
{
	if (File.is_open())
	{
		File.close();
	}
}

// Работает только для точности амплитуды 4 байт
// TODO: Реализовать обработку амплитуды любой точности
float WavAnalyzer::GetAmplitude(bool* BuffSample)
{
	// Только для амплитуды разрадности 4 байт
	float Amplitude = *((float*)BuffSample);
	return Amplitude;
}

WavAnalyzer::~WavAnalyzer()
{
	if (File.is_open())
	{
		Close();
	}
}

WavAnalyzer::AnalyzeRes WavAnalyzer::Analyze()
{
	AnalyzeRes Res{};
	std::vector<AnalayzeData> ChannelsData;
	Open();
	if (!File.is_open())
	{
		std::cout << "\nFile is not open!";
		return Res;
	}
	File.read((char*)&Header, sizeof(WavHeader));
	for (int i = 0; i < Header.numChannels; ++i)
	{
		Res.ResArr.push_back({ 0,0 });
		ChannelsData.push_back({});
	}
	blocksAmm = Header.subchunk2Size / Header.blockAlign;
	bool* BuffBlock = new bool[Header.bitsPerSample * Header.numChannels];
    for (unsigned int i = 0; i < blocksAmm; ++i)
	{
		File.read((char*)BuffBlock, Header.blockAlign);
		for (int j = 0; j < Header.numChannels; ++j)
		{
			// Работает только для амплитуды точности 4 байт
			float Amplitude = GetAmplitude(BuffBlock + j * Header.bitsPerSample / 8);
			// Считаем сколько сэмплов синусойда проходит, перед тем как пройти два раза через 0, первое полное колебание занимает 3 прохода, остальные 2
			++ChannelsData[j].CounterSamples;
			// Фиксируем, когда синусойда проходит через 0
            if ((Amplitude == 0.0f) || (Amplitude < -0.0f) && (ChannelsData[j].LastAmplitude > +0.0f)
                || (Amplitude > +0.0f) && (ChannelsData[j].LastAmplitude < -0.0f))
			{
				if (++ChannelsData[j].CounterViaZero == 3)
				{
					ChannelsData[j].CounterViaZero = 1;
					if (ChannelsData[j].CounterSamples > ChannelsData[j].MaxSamples or ChannelsData[j].MaxSamples == 0)
					{
						ChannelsData[j].MaxSamples = ChannelsData[j].CounterSamples;
					}
					if (ChannelsData[j].CounterSamples < ChannelsData[j].MinSamples or ChannelsData[j].MinSamples == 0)
					{
						ChannelsData[j].MinSamples = ChannelsData[j].CounterSamples;
					}
					ChannelsData[j].CounterSamples = 1;
				}
			}
			ChannelsData[j].LastAmplitude = Amplitude;
		}
	}
	Close();
	for (int i = 0; i < Header.numChannels; ++i)
	{
		// Т.к. частота 44100 сэмплов в секунду, то находим время полного колебания, 
		// разделив мин и макс сэмплов на 44100.
		// Т.к. частота = 1/T, где T = N/t, и где t = (мин или макс сэмплов)/44100, и где N = 1,
		// то частота синусойды = 44100/(мин или макс сэмплов)
		Res.ResArr[i].first = (float)Header.sampleRate / (float)ChannelsData[i].MinSamples;
		Res.ResArr[i].second = (float)Header.sampleRate / (float)ChannelsData[i].MaxSamples;
	}
	delete[] BuffBlock;
	return Res;
}
