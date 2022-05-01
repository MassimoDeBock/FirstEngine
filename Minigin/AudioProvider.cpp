#include "MiniginPCH.h"
#include "AudioProvider.h"
#include "SoundEvent.h"
#include <SDL_mixer.h>
#include <unordered_map>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

struct dae::AudioProvider::Audio_Impl {
	Audio_Impl()
	{
	}
	struct SoundEvent {
		SoundEvent(SoundEventType SoundEvent, int soundID) :m_SoundEvent(SoundEvent), m_SoundID(soundID) {};
		SoundEventType m_SoundEvent;
		int m_SoundID;
	};
	std::jthread m_SoundThread;
	std::unordered_map<int, Mix_Chunk*> m_Sounds{};
	std::mutex frontMutex, backMutex;

	std::mutex m;
	std::condition_variable cv;

	std::queue<SoundEvent> m_SoundQueue{};
};

dae::AudioProvider::AudioProvider()
{
	pimpl = std::make_unique<AudioProvider::Audio_Impl>();
	pimpl->m_SoundThread = std::jthread([this]() {this->dae::AudioProvider::ProcessQueue(); });
}

dae::AudioProvider::~AudioProvider()
{
}

void dae::AudioProvider::PlaySound(int soundID)
{
	pimpl->backMutex.lock();
	pimpl->m_SoundQueue.push(Audio_Impl::SoundEvent(SoundEventType::SoundPlay, soundID));
	pimpl->backMutex.unlock();

	SignalThread();
	//Mix_GroupChannel(Mix_PlayChannel(-1, pimpl->m_Sounds.find(soundID)->second, 0), soundID);
	std::cout << pimpl->m_SoundQueue.size() << std::endl;
}

void dae::AudioProvider::StopSound(int soundID)
{
	pimpl->backMutex.lock();
	pimpl->m_SoundQueue.push(Audio_Impl::SoundEvent(SoundEventType::SoundStop, soundID));
	pimpl->backMutex.unlock();
	//int channel{-1};
	//do{
	//	channel = Mix_GroupAvailable(soundID);
	//	Mix_GroupChannel(channel, -1); //remove tag
	//	Mix_HaltChannel(channel);
	//} while (channel != -1);
}

void dae::AudioProvider::StopAllSounds()
{
	pimpl->backMutex.lock();
	pimpl->m_SoundQueue.push(Audio_Impl::SoundEvent(SoundEventType::SoundStopAll, 0));
	pimpl->backMutex.unlock();
	//Mix_HaltChannel(-1);
}

void dae::AudioProvider::LoadSound(int soundID, const std::string& path)
{
	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_Chunk* sample{ Mix_LoadWAV(path.c_str()) };
	if (!sample) {
		std::cout << "error loading sound\n";
		std::cout << Mix_GetError() << std::endl;
	}
	pimpl->m_Sounds.insert(std::make_pair(soundID, sample));
}

void dae::AudioProvider::ProcessQueue()
{

	for (; true;) {
		std::unique_lock lk(pimpl->m);
		std::cout << (pimpl->m_SoundQueue.size() > 0) << std::endl;
		pimpl->cv.wait(lk, [&] {return pimpl->m_SoundQueue.size() > 0; });
		std::cout << "loop" << std::endl;
		pimpl->frontMutex.lock();
		auto front = pimpl->m_SoundQueue.front();
		switch (front.m_SoundEvent)
		{
		case dae::SoundEventType::SoundPlay:
			Mix_GroupChannel(Mix_PlayChannel(-1, pimpl->m_Sounds.find(front.m_SoundID)->second, 0), front.m_SoundID);
			break;
		case dae::SoundEventType::SoundStop:
		{
			int channel{ -1 };
			do {
				channel = Mix_GroupAvailable(front.m_SoundID);
				Mix_GroupChannel(channel, -1); //remove tag
				Mix_HaltChannel(channel);
			} while (channel != -1);
		}
		break;
		case dae::SoundEventType::SoundStopAll:
			Mix_HaltChannel(-1);
			break;
		default:
			break;
		}
		pimpl->m_SoundQueue.pop();
		pimpl->frontMutex.unlock();

		lk.unlock();
		pimpl->cv.notify_all();
	}
}


void dae::AudioProvider::SignalThread()
{
	pimpl->cv.notify_all();
	std::cout << "signall all" << std::endl;
}
