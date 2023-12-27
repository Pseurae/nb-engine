#include "NB/ECS/Entity.h"
#include "NB/ECS/internal.h"

#include <atomic>

namespace NB::ECS
{
EntityID GetEntityID()
{
    static std::atomic<EntityID> id { PLAYER_ENTITY_ID + 1 };
    return id.fetch_add(1);
}
}