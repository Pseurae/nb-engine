#pragma once

#include <cstddef>

namespace NB::ECS
{
// Entity
using EntityID = std::size_t;

inline constexpr EntityID INVALID_ENTITY_ID = 0;
inline constexpr EntityID PLAYER_ENTITY_ID = 1;

// Component
using ComponentID = std::size_t;

inline constexpr ComponentID INVALID_COMPONENT_ID = 0;
inline constexpr std::size_t MAX_COMPONENTS = 128;

// System
using SystemID = std::size_t;
inline constexpr SystemID INVALID_SYSTEM_ID = 0;
inline constexpr std::size_t MAX_SYSTEMS = 32;
}