#ifndef STATE_TRACER_SIMULATION_DATA_GENERATOR
#define STATE_TRACER_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class state_tracerAnalyzerSettings;

class state_tracerSimulationDataGenerator
{
public:
	state_tracerSimulationDataGenerator();
	~state_tracerSimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, state_tracerAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	state_tracerAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSerialByte();
	std::string mSerialText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSerialSimulationData;

};
#endif //STATE_TRACER_SIMULATION_DATA_GENERATOR