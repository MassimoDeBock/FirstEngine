#pragma once

namespace dae {
	class Audio_API
	{
	public:
		virtual ~Audio_API() {}
		virtual void PlaySound(int soundID) = 0;
		virtual void StopSound(int soundID) = 0;
		virtual void StopAllSounds() = 0;
	};

}