#ifndef STATE_TRACER_ANALYZER_H
#define STATE_TRACER_ANALYZER_H

#include <Analyzer.h>
#include "state_tracerAnalyzerSettings.h"
#include "state_tracerAnalyzerResults.h"
#include "state_tracerSimulationDataGenerator.h"
#include <memory>

class ANALYZER_EXPORT state_tracerAnalyzer : public Analyzer2
{
public:
	state_tracerAnalyzer();
	virtual ~state_tracerAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	state_tracerAnalyzerSettings mSettings;
	std::unique_ptr<state_tracerAnalyzerResults> mResults;
	AnalyzerChannelData* mSerial;

	state_tracerSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //STATE_TRACER_ANALYZER_H
