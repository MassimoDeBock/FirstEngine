#pragma once
#include "NullAudioProvider.h"

namespace dae {
	class Locator
	{
	public: 
		static void initialize() { m_AudioService = &nullAudioService; }
		static Audio_API& getAudio() {
			return *m_AudioService;
		}

		static void provide(Audio_API* service) {
			if (service == 0)
			{
				m_AudioService = &nullAudioService;
			}
			else {
			m_AudioService = service;
			}
		}
	private:
		static Audio_API* m_AudioService;
		static NullAudioProvider nullAudioService;
	};
}

//https://gameprogrammingpatterns.com/service-locator.html