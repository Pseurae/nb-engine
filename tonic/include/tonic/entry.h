#pragma once

#include "tonic/engine.h"

namespace tonic
{
extern App *CreateApplication();
}

int main(int argc, char *argv[])
{
    auto app = tonic::CreateApplication();
    tonic::Engine::Instance().Run(app);
    delete app;
    return 0;
}