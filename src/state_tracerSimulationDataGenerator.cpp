#include "state_tracerSimulationDataGenerator.h"
#include "state_tracerAnalyzerSettings.h"

#include <AnalyzerHelpers.h>

state_tracerSimulationDataGenerator::state_tracerSimulationDataGenerator()
:	mSerialText( "My first analyzer, woo hoo!" ),
	mStringIndex( 0 )
{
}

state_tracerSimulationDataGenerator::~state_tracerSimulationDataGenerator()
{
}

void state_tracerSimulationDataGenerator::Initialize( U32 simulation_sample_rate, state_tracerAnalyzerSettings* settings )
{
}

U32 state_tracerSimulationDataGenerator::GenerateSimulationData( U64 largest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel )
{
	U64 adjusted_largest_sample_requested = AnalyzerHelpers::AdjustSimulationTargetSample( largest_sample_requested, sample_rate, mSimulationSampleRateHz );

	while( mSerialSimulationData.GetCurrentSampleNumber() < adjusted_largest_sample_requested )
	{
		CreateSerialByte();
	}

	*simulation_channel = &mSerialSimulationData;
	return 1;
}

void state_tracerSimulationDataGenerator::CreateSerialByte()
{
}
