#ifndef ANDERS_SIMULATION_DATA_GENERATOR
#define ANDERS_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class andersAnalyzerSettings;

class andersSimulationDataGenerator
{
public:
	andersSimulationDataGenerator();
	~andersSimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, andersAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	andersAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSerialByte();
	std::string mSerialText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSerialSimulationData;

};
#endif //ANDERS_SIMULATION_DATA_GENERATOR