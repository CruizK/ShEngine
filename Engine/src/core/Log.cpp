#pragma once
#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Shengine {

    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stderr_color_mt("CORE");
        s_CoreLogger->set_level(spdlog::level::trace);
    }
}