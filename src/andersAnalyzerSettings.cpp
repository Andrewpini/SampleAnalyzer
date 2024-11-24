#include "andersAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


andersAnalyzerSettings::andersAnalyzerSettings()
:
	// mInputChannel( UNDEFINED_CHANNEL ),
 	mReadTriggerChannel(UNDEFINED_CHANNEL),
	mPin1Channel(UNDEFINED_CHANNEL),
	mPin2Channel(UNDEFINED_CHANNEL),
	mPin3Channel(UNDEFINED_CHANNEL),
	mPin4Channel(UNDEFINED_CHANNEL)
	// mBitRate( 9600 ),
	// mInputChannelInterface(),
	// mBitRateInterface()
{
	mReadTriggerChannelInterface.reset(new AnalyzerSettingInterfaceChannel());
	mReadTriggerChannelInterface->SetTitleAndTooltip("Read Trigger", "Select the read trigger channel");
	mReadTriggerChannelInterface->SetChannel(mReadTriggerChannel);

	mPin1ChannelInterface.reset(new AnalyzerSettingInterfaceChannel());
	mPin1ChannelInterface->SetTitleAndTooltip("Pin 1", "Select the channel for Pin 1 (LSB)");
	mPin1ChannelInterface->SetChannel(mPin1Channel);

	mPin2ChannelInterface.reset(new AnalyzerSettingInterfaceChannel());
	mPin2ChannelInterface->SetTitleAndTooltip("Pin 2", "Select the channel for Pin 2");
	mPin2ChannelInterface->SetChannel(mPin2Channel);

	mPin3ChannelInterface.reset(new AnalyzerSettingInterfaceChannel());
	mPin3ChannelInterface->SetTitleAndTooltip("Pin 3", "Select the channel for Pin 3");
	mPin3ChannelInterface->SetChannel(mPin3Channel);

	mPin4ChannelInterface.reset(new AnalyzerSettingInterfaceChannel());
	mPin4ChannelInterface->SetTitleAndTooltip("Pin 4", "Select the channel for Pin 4 (MSB)");
	mPin4ChannelInterface->SetChannel(mPin4Channel);

	// mInputChannelInterface.SetTitleAndTooltip( "Serial", "Standard anders" );
	// mInputChannelInterface.SetChannel( mInputChannel );

	// mBitRateInterface.SetTitleAndTooltip( "Bit Rate (Bits/S)",  "Specify the bit rate in bits per second." );
	// mBitRateInterface.SetMax( 6000000 );
	// mBitRateInterface.SetMin( 1 );
	// mBitRateInterface.SetInteger( mBitRate );

	// AddInterface( &mInputChannelInterface );
	// AddInterface( &mBitRateInterface );
	AddInterface(mReadTriggerChannelInterface.get());
	AddInterface(mPin1ChannelInterface.get());
	AddInterface(mPin2ChannelInterface.get());
	AddInterface(mPin3ChannelInterface.get());
	AddInterface(mPin4ChannelInterface.get());


	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

	ClearChannels();
	// AddChannel( mInputChannel, "Serial", false );
	AddChannel(mReadTriggerChannel, "Read Trigger", false);
	AddChannel(mPin1Channel, "Pin 1", false);
	AddChannel(mPin2Channel, "Pin 2", false);
	AddChannel(mPin3Channel, "Pin 3", false);
	AddChannel(mPin4Channel, "Pin 4", false);
}

andersAnalyzerSettings::~andersAnalyzerSettings()
{
}

bool andersAnalyzerSettings::SetSettingsFromInterfaces()
{
	// mInputChannel = mInputChannelInterface.GetChannel();
	// mBitRate = mBitRateInterface.GetInteger();
	mReadTriggerChannel = mReadTriggerChannelInterface->GetChannel();
	mPin1Channel = mPin1ChannelInterface->GetChannel();
	mPin2Channel = mPin2ChannelInterface->GetChannel();
	mPin3Channel = mPin3ChannelInterface->GetChannel();
	mPin4Channel = mPin4ChannelInterface->GetChannel();

	ClearChannels();
	// AddChannel( mInputChannel, "anders", true );

	// Save the user's selections from the GUI

	AddChannel(mReadTriggerChannel, "Read Trigger", true);
	AddChannel(mPin1Channel, "Pin 1", true);
	AddChannel(mPin2Channel, "Pin 2", true);
	AddChannel(mPin3Channel, "Pin 3", true);
	AddChannel(mPin4Channel, "Pin 4", true);

	return true;
}

void andersAnalyzerSettings::UpdateInterfacesFromSettings()
{
	// mInputChannelInterface.SetChannel( mInputChannel );
	// mBitRateInterface.SetInteger( mBitRate );
	mReadTriggerChannelInterface->SetChannel(mReadTriggerChannel);
	mPin1ChannelInterface->SetChannel(mPin1Channel);
	mPin2ChannelInterface->SetChannel(mPin2Channel);
	mPin3ChannelInterface->SetChannel(mPin3Channel);
	mPin4ChannelInterface->SetChannel(mPin4Channel);
}

void andersAnalyzerSettings::LoadSettings( const char* settings )
{
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	// text_archive >> mInputChannel;
	// text_archive >> mBitRate;
    text_archive >> mReadTriggerChannel;
    text_archive >> mPin1Channel;
    text_archive >> mPin2Channel;
    text_archive >> mPin3Channel;
    text_archive >> mPin4Channel;
	ClearChannels();
	// AddChannel( mInputChannel, "anders", true );
    AddChannel(mReadTriggerChannel, "Read Trigger", true);
    AddChannel(mPin1Channel, "Pin 1", true);
    AddChannel(mPin2Channel, "Pin 2", true);
    AddChannel(mPin3Channel, "Pin 3", true);
    AddChannel(mPin4Channel, "Pin 4", true);
	UpdateInterfacesFromSettings();
}

const char* andersAnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	// text_archive << mInputChannel;
	// text_archive << mBitRate;
    text_archive << mReadTriggerChannel;
    text_archive << mPin1Channel;
    text_archive << mPin2Channel;
    text_archive << mPin3Channel;
    text_archive << mPin4Channel;

	return SetReturnString( text_archive.GetString() );
}