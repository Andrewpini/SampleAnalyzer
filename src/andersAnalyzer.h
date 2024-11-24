#ifndef ANDERS_ANALYZER_H
#define ANDERS_ANALYZER_H

#include <Analyzer.h>
#include "andersAnalyzerSettings.h"
#include "andersAnalyzerResults.h"
#include "andersSimulationDataGenerator.h"
#include <memory>

class ANALYZER_EXPORT andersAnalyzer : public Analyzer2
{
public:
	andersAnalyzer();
	virtual ~andersAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	andersAnalyzerSettings mSettings;
	std::unique_ptr<andersAnalyzerResults> mResults;
	AnalyzerChannelData* mSerial;

	andersSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //ANDERS_ANALYZER_H
