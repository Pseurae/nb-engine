#pragma once

#include "NB/ECS/internal.h"

#include <unordered_map>
#include <vector>

namespace NB::ECS
{
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