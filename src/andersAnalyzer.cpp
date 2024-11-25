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

static bool try_advancing( AnalyzerChannelData* pin )
{
    if( !pin->WouldAdvancingCauseTransition( 10000 ) )
    {
        pin->Advance( 10000 );
        return true;
    }
    else if( pin->GetBitState() == BIT_HIGH )
    {
        pin->AdvanceToNextEdge();
        return true;
    }
    else
    {
        pin->AdvanceToNextEdge();
        return false;
    }
}


void andersAnalyzer::WorkerThread()
{
    auto* read_trigger = GetAnalyzerChannelData( mSettings.mReadTriggerChannel );
    auto* pin1 = GetAnalyzerChannelData( mSettings.mPin1Channel );
    auto* pin2 = GetAnalyzerChannelData( mSettings.mPin2Channel );
    auto* pin3 = GetAnalyzerChannelData( mSettings.mPin3Channel );
    auto* pin4 = GetAnalyzerChannelData( mSettings.mPin4Channel );

    U64 wrt_start = 0;
    U64 wrt_end = 0;
    U8 state = 0xff; // Unknown state from start

    for( ;; )
    {
        if( try_advancing( read_trigger ) )
        {
            Frame frame;
            frame.mData1 = state;
            frame.mFlags = 0;
            frame.mStartingSampleInclusive = wrt_start;
            frame.mEndingSampleInclusive = read_trigger->GetSampleNumber();
            mResults->AddFrame( frame );
            mResults->CommitResults();
            ReportProgress( frame.mEndingSampleInclusive );
        }
        else
        {
            wrt_start = read_trigger->GetSampleNumber();
            pin1->AdvanceToAbsPosition( read_trigger->GetSampleNumber() );
            pin2->AdvanceToAbsPosition( read_trigger->GetSampleNumber() );
            pin3->AdvanceToAbsPosition( read_trigger->GetSampleNumber() );
            pin4->AdvanceToAbsPosition( read_trigger->GetSampleNumber() );
            state = ( pin1->GetBitState() == BIT_HIGH ? 1 : 0 ) << 0;  // Pin 1 (LSB)
            state |= ( pin2->GetBitState() == BIT_HIGH ? 1 : 0 ) << 1; // Pin 2
            state |= ( pin3->GetBitState() == BIT_HIGH ? 1 : 0 ) << 2; // Pin 3
            state |= ( pin4->GetBitState() == BIT_HIGH ? 1 : 0 ) << 3; // Pin 4 (MSB)

            if( read_trigger->GetBitState() == BIT_HIGH )
                read_trigger->AdvanceToNextEdge();
        }
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
