#pragma once
#include "Audio_API.h"

namespace dae {
    class AudioProvider :
        public Audio_API
    {
    public:
        AudioProvider();
        ~AudioProvider();
        virtual void PlaySound(int soundID);
        virtual void StopSound(int soundID);
        virtual void StopAllSounds();
        virtual void LoadSound(int soundID, const std::string& path);

    private:
        struct Audio_Impl;
        std::unique_ptr<Audio_Impl> pimpl;


        void ProcessQueue();
        void SignalThread();
    };
}