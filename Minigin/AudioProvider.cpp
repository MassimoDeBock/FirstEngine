#include "MiniginPCH.h"
#include "AudioProvider.h"
#include <SDL_mixer.h>
#include <unordered_map>

struct dae::AudioProvider::Audio_Impl {
	std::unordered_map<int, Mix_Chunk*> m_Sounds;
	
};

void dae::AudioProvider::PlaySound(int soundID)
{
	Mix_GroupChannel(Mix_PlayChannel(-1, pimpl->m_Sounds.find(soundID)->second, 0), soundID);

}

void dae::AudioProvider::StopSound(int soundID)
{
	soundID;
	int channel{-1};
	do{
		channel = Mix_GroupAvailable(soundID);
		Mix_GroupChannel(channel, -1); //remove tag
		Mix_HaltChannel(channel);
	} while (channel != -1);
}

void dae::AudioProvider::StopAllSounds()
{
	Mix_HaltChannel(-1);
}
