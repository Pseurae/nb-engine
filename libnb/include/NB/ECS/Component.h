#pragma once

#include <cstdint>
#include <concepts>
#include <type_traits>
#include <vector>
#include <unordered_map>
#include <bitset>

#include "NB/ECS/internal.h"

namespace NB::ECS
{
struct Component {};

template<typename T>
concept ComponentConcept = std::derived_from<T, Component> && !std::same_as<Component, T>;

namespace details
{
struct component_id_impl
{
private:
    [[nodiscard]] static ComponentID Next() 
    {
        static ComponentID counter = INVALID_COMPONENT_ID;

        if (counter >= MAX_COMPONENTS)
            return INVALID_COMPONENT_ID;

        return ++counter;
    }
public:
    template<ComponentConcept T>
    static inline ComponentID value = Next();
};
}

using ComponentMask = std::bitset<MAX_COMPONENTS>;

template<typename T>
[[nodiscard]] ComponentID GetComponentID() { return details::component_id_impl::value<T>; }

// Component Pool
class IComponentPool {};

template <ComponentConcept T>
class ComponentPool final : public IComponentPool
{
public:
    template<typename... Args>
    T &AddComponent(EntityID e, Args&&... args)
    {
        m_Indices.insert({ e, m_Components.size() });
        m_Components.emplace_back(std::forward<Args>(args)...);
        m_Entities.emplace_back(e);
        return m_Components.back();
    }

    void AddComponent(EntityID e, T&& component)
    {
        m_Indices.insert({ e, m_Components.size() });
        m_Components.emplace_back(std::move(component));
        m_Entities.emplace_back(e);
    }

    void RemoveComponent(EntityID e)
    {
        auto it = m_Indices.find(e);
        std::size_t componentIndex = it->second;

        if (componentIndex < m_Components.size() - 1)
        {
            m_Components[componentIndex] = std::move(m_Components.back());

            auto lastEntity = m_Entities.back();

            m_Entities[componentIndex] = lastEntity;
            m_Indices[lastEntity] = componentIndex;
        }

        m_Components.pop_back();
        m_Entities.pop_back();
        m_Indices.erase(it);
    }

    [[nodiscard]] bool HasComponent(EntityID e)
    {
        return m_Indices.find(e) != m_Indices.end();
    }

    [[nodiscard]] T &GetComponent(EntityID e)
    {
        auto it = m_Indices.find(e);
        return m_Components[it->second];
    }

    const auto &GetComponents() const { return m_Components; }
private:
    std::unordered_map<EntityID, std::size_t> m_Indices;
    std::vector<EntityID> m_Entities;
    std::vector<T> m_Components;
};
}