#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace Shengine {
    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
    };
}

#define CORE_ERROR(...) Shengine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_INFO(...) Shengine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...) Shengine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_TRACE(...) Shengine::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define CORE_ASSERT(x, msg) if(!(x)) CORE_ERROR(msg)