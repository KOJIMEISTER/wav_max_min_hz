#include "WavAnalyzer.h"
#include <iostream>

void PrintRes(const WavAnalyzer::AnalyzeRes& Res)
{
	int Counter = 0;
	for (const auto& Channel : Res.ResArr)
	{
		std::cout << "\nChannel #" << ++Counter << " max-Hz: " << Channel.first << " min-Hz: " << Channel.second;
	}
}

int main(int Amm, char* Params[])
{
	if (Amm == 2)
	{
		auto Res = WavAnalyzer(Params[1]).Analyze();
		PrintRes(Res);
	}
	else
	{
		std::cout << "\nPlease enter correct path to file.";
		return 1;
	}
	return 0;
}