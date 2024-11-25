#ifndef STATE_TRACER_ANALYZER_SETTINGS
#define STATE_TRACER_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class state_tracerAnalyzerSettings : public AnalyzerSettings
{
public:
	state_tracerAnalyzerSettings();
	virtual ~state_tracerAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	Channel mReadTriggerChannel;
	Channel mPin1Channel;
	Channel mPin2Channel;
	Channel mPin3Channel;
	Channel mPin4Channel;

    	std::string mStateStrings[16]; // Array of state strings
protected:
	std::unique_ptr<AnalyzerSettingInterfaceChannel> mReadTriggerChannelInterface;
	std::unique_ptr<AnalyzerSettingInterfaceChannel> mPin1ChannelInterface;
	std::unique_ptr<AnalyzerSettingInterfaceChannel> mPin2ChannelInterface;
	std::unique_ptr<AnalyzerSettingInterfaceChannel> mPin3ChannelInterface;
	std::unique_ptr<AnalyzerSettingInterfaceChannel> mPin4ChannelInterface;

 	std::unique_ptr<AnalyzerSettingInterfaceText> mStateInterfaces[16]; // Interfaces for state strings
};

#endif //STATE_TRACER_ANALYZER_SETTINGS
