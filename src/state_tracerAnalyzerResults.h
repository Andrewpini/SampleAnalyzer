#ifndef STATE_TRACER_ANALYZER_RESULTS
#define STATE_TRACER_ANALYZER_RESULTS

#include <AnalyzerResults.h>

class state_tracerAnalyzer;
class state_tracerAnalyzerSettings;

class state_tracerAnalyzerResults : public AnalyzerResults
{
public:
	state_tracerAnalyzerResults( state_tracerAnalyzer* analyzer, state_tracerAnalyzerSettings* settings );
	virtual ~state_tracerAnalyzerResults();

	virtual void GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base );
	virtual void GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id );

	virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base );
	virtual void GeneratePacketTabularText( U64 packet_id, DisplayBase display_base );
	virtual void GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base );

protected: //functions

protected:  //vars
	state_tracerAnalyzerSettings* mSettings;
	state_tracerAnalyzer* mAnalyzer;
};

#endif //STATE_TRACER_ANALYZER_RESULTS
