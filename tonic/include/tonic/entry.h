#pragma once

#include "tonic/engine.h"

namespace tonic
{
using LaunchArguments = std::vector<std::string>;
extern App *CreateApplication(const LaunchArguments &launchArguments);
}

int main(int argc, char *argv[])
{
    auto app = tonic::CreateApplication(tonic::LaunchArguments(argv, argv + argc));
    tonic::Engine::Instance().Run(app);
    delete app;
    return 0;
}