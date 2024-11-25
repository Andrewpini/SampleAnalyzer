#include "state_tracerAnalyzerResults.h"
#include <AnalyzerHelpers.h>
#include "state_tracerAnalyzer.h"
#include "state_tracerAnalyzerSettings.h"
#include <iostream>
#include <fstream>

state_tracerAnalyzerResults::state_tracerAnalyzerResults( state_tracerAnalyzer* analyzer, state_tracerAnalyzerSettings* settings )
:	AnalyzerResults(),
	mSettings( settings ),
	mAnalyzer( analyzer )
{
}

state_tracerAnalyzerResults::~state_tracerAnalyzerResults()
{
}

void state_tracerAnalyzerResults::GenerateBubbleText(U64 frame_index, Channel& channel, DisplayBase display_base)
{
    ClearResultStrings();
    Frame frame = GetFrame(frame_index);

    // Convert the frame's data to a number string
    char number_str[128];
    AnalyzerHelpers::GetNumberString(frame.mData1, display_base, 8, number_str, 128);

    // Map state strings based on frame data
    std::string state_string;
    if (frame.mData1 < 16)
    {
        state_string = mSettings->mStateStrings[frame.mData1];
    }
    else
    {
        state_string = ""; // Default to an empty string
    }

    // Combine the state number string and optional string for the bubble text
    AddResultString(number_str, " ", state_string.c_str());
}

void state_tracerAnalyzerResults::GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id )
{
	std::ofstream file_stream( file, std::ios::out );

	U64 trigger_sample = mAnalyzer->GetTriggerSample();
	U32 sample_rate = mAnalyzer->GetSampleRate();

	file_stream << "Time [s],Value" << std::endl;

	U64 num_frames = GetNumFrames();
	for( U32 i=0; i < num_frames; i++ )
	{
		Frame frame = GetFrame( i );

		char time_str[128];
		AnalyzerHelpers::GetTimeString( frame.mStartingSampleInclusive, trigger_sample, sample_rate, time_str, 128 );

		char number_str[128];
		AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, number_str, 128 );

		file_stream << time_str << "," << number_str << std::endl;

		if( UpdateExportProgressAndCheckForCancel( i, num_frames ) == true )
		{
			file_stream.close();
			return;
		}
	}

	file_stream.close();
}

void state_tracerAnalyzerResults::GenerateFrameTabularText( U64 frame_index, DisplayBase display_base )
{
#ifdef SUPPORTS_PROTOCOL_SEARCH
	Frame frame = GetFrame( frame_index );
	ClearTabularText();

	char number_str[128];
	AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, number_str, 128 );
	AddTabularText( number_str );
#endif
}

void state_tracerAnalyzerResults::GeneratePacketTabularText( U64 packet_id, DisplayBase display_base )
{
	//not supported

}

void state_tracerAnalyzerResults::GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base )
{
	//not supported
}
