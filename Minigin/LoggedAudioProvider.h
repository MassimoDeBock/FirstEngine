#pragma once
#include "Audio_API.h"

namespace dae {
	class LoggedAudioProvider :
		public Audio_API
	{
	public:
		LoggedAudioProvider(Audio_API& wrapped);
		virtual void PlaySound(int soundID);
		virtual void StopSound(int soundID);
		virtual void StopAllSounds();

	private:
		void Log(const char* message);
		
		Audio_API &m_Wrapped;
	};
}
