#pragma once
#include "Audio_API.h"

namespace dae {
    class AudioProvider :
        public Audio_API
    {
    public:
        virtual void PlaySound(int soundID);
        virtual void StopSound(int soundID);
        virtual void StopAllSounds();

    private:
        struct Audio_Impl;
        std::unique_ptr<Audio_Impl> pimpl;
    };
}