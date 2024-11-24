#include "andersAnalyzer.h"
#include "andersAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

andersAnalyzer::andersAnalyzer()
:	Analyzer2(),
	mSettings(),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( &mSettings );
}

andersAnalyzer::~andersAnalyzer()
{
	KillThread();
}

void andersAnalyzer::SetupResults()
{
	// SetupResults is called each time the analyzer is run. Because the same instance can be used for multiple runs, we need to clear the results each time.
	mResults.reset(new andersAnalyzerResults( this, &mSettings ));
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings.mReadTriggerChannel );
}

void andersAnalyzer::WorkerThread()
{

	auto* read_trigger = GetAnalyzerChannelData(mSettings.mReadTriggerChannel);
	auto* pin1 = GetAnalyzerChannelData(mSettings.mPin1Channel);
	auto* pin2 = GetAnalyzerChannelData(mSettings.mPin2Channel);
	auto* pin3 = GetAnalyzerChannelData(mSettings.mPin3Channel);
	auto* pin4 = GetAnalyzerChannelData(mSettings.mPin4Channel);

	if( read_trigger->GetBitState() == BIT_LOW )
		read_trigger->AdvanceToNextEdge();


	U8 data = 0;
	for( ; ; )
	{


		U64 starting_sample = read_trigger->GetSampleNumber();
        U8 number = 0;
        number |= (pin1->GetBitState() == BIT_HIGH ? 1 : 0) << 0; // Pin 1 (LSB)
        number |= (pin2->GetBitState() == BIT_HIGH ? 1 : 0) << 1; // Pin 2
        number |= (pin3->GetBitState() == BIT_HIGH ? 1 : 0) << 2; // Pin 3
        number |= (pin4->GetBitState() == BIT_HIGH ? 1 : 0) << 3; // Pin 4 (MSB)
		read_trigger->AdvanceToNextEdge(); //falling edge -- beginning of the start bit

		read_trigger->AdvanceToNextEdge(); //rising edge -- beginning of the start bit

		Frame frame;
		frame.mData1 = data++;
		frame.mFlags = number;
		frame.mStartingSampleInclusive = starting_sample;
		frame.mEndingSampleInclusive = read_trigger->GetSampleNumber();

		mResults->AddFrame( frame );
		mResults->CommitResults();
		ReportProgress( frame.mEndingSampleInclusive );
	}
}

bool andersAnalyzer::NeedsRerun()
{
	return false;
}

U32 andersAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), &mSettings );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 andersAnalyzer::GetMinimumSampleRateHz()
{
	return 0;
	// return mSettings.mBitRate * 4;
}

const char* andersAnalyzer::GetAnalyzerName() const
{
	return "anders";
}

const char* GetAnalyzerName()
{
	return "anders";
}

Analyzer* CreateAnalyzer()
{
	return new andersAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}
