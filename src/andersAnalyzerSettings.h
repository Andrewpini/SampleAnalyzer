#ifndef ANDERS_ANALYZER_SETTINGS
#define ANDERS_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class andersAnalyzerSettings : public AnalyzerSettings
{
public:
	andersAnalyzerSettings();
	virtual ~andersAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();


	// Channel mInputChannel;
	// U32 mBitRate;
	Channel mReadTriggerChannel;
	Channel mPin1Channel;
	Channel mPin2Channel;
	Channel mPin3Channel;
	Channel mPin4Channel;

    	std::string mStateStrings[16]; // Array of state strings
protected:
	// AnalyzerSettingInterfaceChannel	mInputChannelInterface;
	// AnalyzerSettingInterfaceInteger	mBitRateInterface;
	std::unique_ptr<AnalyzerSettingInterfaceChannel> mReadTriggerChannelInterface;
	std::unique_ptr<AnalyzerSettingInterfaceChannel> mPin1ChannelInterface;
	std::unique_ptr<AnalyzerSettingInterfaceChannel> mPin2ChannelInterface;
	std::unique_ptr<AnalyzerSettingInterfaceChannel> mPin3ChannelInterface;
	std::unique_ptr<AnalyzerSettingInterfaceChannel> mPin4ChannelInterface;


 	std::unique_ptr<AnalyzerSettingInterfaceText> mStateInterfaces[16]; // Interfaces for state strings
	// std::unique_ptr<AnalyzerSettingInterfaceText> mState0Interface; // Text input interface
};

#endif //ANDERS_ANALYZER_SETTINGS
