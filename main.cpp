#include <tonic/entry.h>

tonic::App *tonic::CreateApplication(const LaunchArguments &launchArguments)
{
    return new tonic::App();
}
