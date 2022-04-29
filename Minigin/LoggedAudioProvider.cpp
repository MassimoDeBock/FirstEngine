#include "MiniginPCH.h"
#include "LoggedAudioProvider.h"

dae::LoggedAudioProvider::LoggedAudioProvider(Audio_API& wrapped)
	: m_Wrapped(wrapped)
{
}

void dae::LoggedAudioProvider::PlaySound(int soundID)
{
	Log("play sound" + soundID);
	m_Wrapped.PlaySound(soundID);
}

void dae::LoggedAudioProvider::StopSound(int soundID)
{
	Log("stop sound " + soundID);
	m_Wrapped.StopSound(soundID);
}

void dae::LoggedAudioProvider::StopAllSounds()
{
	Log("stop all sound");
	m_Wrapped.StopAllSounds();
}

void dae::LoggedAudioProvider::Log(const char* message)
{
	std::cout << "AudioLog: \"" << message << "\"\n";
}
