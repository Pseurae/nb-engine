#include "NB/ECS/Manager.h"
#include "NB/ECS/internal.h"

#include "NB/ECS/Component.h"
#include "NB/ECS/Entity.h"
#include "NB/ECS/System.h"

namespace NB::ECS
{
Manager::~Manager()
{
    for (auto &[id, system] : m_SystemPool)
        system->OnShutdown();
}

void Manager::UpdateAll()
{
    for (auto &[id, system] : m_SystemPool)
        system->OnUpdate();
}

[[nodiscard]] EntityID Manager::CreateEntity()
{
    auto entityId = GetEntityID();
    m_Entities.insert({ entityId, {0} });
    return entityId;
}

[[nodiscard]] ComponentMask &Manager::GetEntityComponentMask(EntityID e)
{
    auto it = m_Entities.find(e);
    return it->second;
}
}