#include "Yaof/Core/FpsLimiter.hpp"
#include <cstdio>
#include <chrono>
#include <thread>

namespace yf
{
    void FpsLimiter::tick()
    {
        if (m_firstTick)
        {
            m_startRenderTime = std::chrono::system_clock::now();
            m_firstTick = false;
        }

        const auto endRenderTime = std::chrono::system_clock::now();
        const auto drawTime = std::chrono::duration<float, std::milli>(endRenderTime - m_startRenderTime).count();
        const auto sleepTime = 1000.0f / m_framesPerSecond - drawTime;

        if (m_enable && sleepTime > 0.0f)
        {
            m_deltaTime = drawTime + sleepTime;
            std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int32_t>(sleepTime) * 1000));
        }
        else
        {
            m_deltaTime = drawTime;
        }

#ifdef DEBUG
        static auto fpsTime = 0.0f;
        static uint32_t fps = 0;
        fpsTime += std::chrono::duration<float, std::milli>(std::chrono::system_clock::now() - m_startRenderTime).
            count();
        ++fps;

        if (fpsTime >= 1000.0)
        {
            printf("FPS: %.2f\n", fps * 1000.0 / fpsTime);

            fpsTime = 0.0;
            fps = 0;
        }
#endif

        m_startRenderTime = std::chrono::system_clock::now();
    }

    void FpsLimiter::setEnable(bool const enable)
    {
        m_enable = enable;

        if (m_enable)
        {
            m_firstTick = true;
        }
    }

    void FpsLimiter::setFramesPersecond(uint32_t const framesPerSecond)
    {
        m_framesPerSecond = framesPerSecond;
    }

    uint32_t FpsLimiter::getFramesPerSecond() const
    {
        return m_framesPerSecond;
    }

    float FpsLimiter::getDeltaTime() const
    {
        return m_deltaTime / 1000.0f;
    }

    FpsLimiter::FpsLimiter() :
        m_enable(false),
        m_firstTick(false),
        m_deltaTime(0.0f)
    {
    }
}
