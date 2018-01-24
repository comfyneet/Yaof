#ifndef YAOF_CORE_FPSMANAGER_HPP
#define YAOF_CORE_FPSMANAGER_HPP

#include <chrono>
#include "Yaof/Misc/Singleton.hpp"

namespace yf
{
    class FpsLimiter;
    YAOF_EXTERN template class YAOF_DLL Singleton<FpsLimiter>;

    class YAOF_DLL FpsLimiter : public Singleton<FpsLimiter>
    {
        friend class Singleton<FpsLimiter>;
    public:
        void tick();

        void setEnable(bool enable);

        void setFramesPersecond(uint32_t framesPerSecond);

        uint32_t getFramesPerSecond() const;

        float getDeltaTime() const;

    private:
        FpsLimiter();

        bool m_enable;

        bool m_firstTick;

        uint32_t m_framesPerSecond = 60;

        float m_deltaTime;

        std::chrono::system_clock::time_point m_startRenderTime;
    };
}

#endif
