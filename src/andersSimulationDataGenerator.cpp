#include "andersSimulationDataGenerator.h"
#include "andersAnalyzerSettings.h"

#include <AnalyzerHelpers.h>

andersSimulationDataGenerator::andersSimulationDataGenerator()
:	mSerialText( "My first analyzer, woo hoo!" ),
	mStringIndex( 0 )
{
}

andersSimulationDataGenerator::~andersSimulationDataGenerator()
{
}

void andersSimulationDataGenerator::Initialize( U32 simulation_sample_rate, andersAnalyzerSettings* settings )
{
}

U32 andersSimulationDataGenerator::GenerateSimulationData( U64 largest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel )
{
	U64 adjusted_largest_sample_requested = AnalyzerHelpers::AdjustSimulationTargetSample( largest_sample_requested, sample_rate, mSimulationSampleRateHz );

	while( mSerialSimulationData.GetCurrentSampleNumber() < adjusted_largest_sample_requested )
	{
		CreateSerialByte();
	}

	*simulation_channel = &mSerialSimulationData;
	return 1;
}

void andersSimulationDataGenerator::CreateSerialByte()
{
}
