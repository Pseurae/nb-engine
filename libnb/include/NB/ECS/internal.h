#pragma once

#include <cstddef>
#include <bitset>
#include <concepts>
#include <type_traits>

#include "NB/Traits.h"

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

using ComponentMask = std::bitset<MAX_COMPONENTS>;

// System
using SystemID = std::size_t;
inline constexpr SystemID INVALID_SYSTEM_ID = 0;
inline constexpr std::size_t MAX_SYSTEMS = 32;

// Component
struct Component {};

template<typename T>
concept ComponentConcept = std::derived_from<T, Component> && !std::same_as<Component, T>;

// System
class Manager;

class ISystem 
{
protected:
    virtual void OnInitialize() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnShutdown() = 0;

    friend class Manager;
};

template<ComponentConcept... Args>
requires (NB::Traits::Parameters::Unique<Args...>)
class System;

template<typename T>
concept SystemConcept = requires(T t){ []<typename... Args>(System<Args...>&){}(t); };
}