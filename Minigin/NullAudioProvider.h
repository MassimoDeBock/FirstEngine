#pragma once
#include "Audio_API.h"

namespace dae {
	class NullAudioProvider :
		public Audio_API
	{
		virtual void PlaySound(int soundID) { soundID; };
		virtual void StopSound(int soundID) { soundID; };
		virtual void StopAllSounds() {};
	};

}