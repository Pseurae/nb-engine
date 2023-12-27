#pragma once

#include "NB/ECS/internal.h"
#include "NB/ECS/ComponentPool.h"

#include <unordered_map>
#include <memory>

namespace NB::ECS
{
class Manager final
{
public:
    ~Manager();

    template<ComponentConcept T>
    bool RegisterComponent()
    {
        auto componentTypeID = GetComponentID<T>();
        return m_ComponentPools.emplace(componentTypeID, std::make_shared<ComponentPool<T>>()).second;
    }

    [[nodiscard]] EntityID CreateEntity();

    template<ComponentConcept T>
    [[nodiscard]] std::shared_ptr<ComponentPool<T>> GetComponentPool()
    {
        auto componentTypeID = GetComponentID<T>();
        auto it = m_ComponentPools.find(componentTypeID);
        return std::static_pointer_cast<ComponentPool<T>>(it->second);
    }

    [[nodiscard]] ComponentMask &GetEntityComponentMask(EntityID e);

    template<ComponentConcept T, typename... Args>
    T &AddComponent(EntityID e, Args ...args)
    {
        auto componentTypeID = GetComponentID<T>();
        auto pool = GetComponentPool<T>();
        auto &mask = GetEntityComponentMask(e);

        mask.set(componentTypeID);
        return pool->AddComponent(e, std::forward<Args>(args)...);
    }

    template<ComponentConcept T>
    void AddComponent(EntityID e, T&& component)
    {
        auto componentTypeID = GetComponentID<T>();
        auto pool = GetComponentPool<T>();
        auto &mask = GetEntityComponentMask(e);

        mask.set(componentTypeID);
        pool->AddComponent(e, component);
    }

    template<ComponentConcept T>
    void RemoveComponent(EntityID e)
    {
        auto componentTypeID = GetComponentID<T>();
        auto pool = GetComponentPool<T>();
        auto &mask = GetEntityComponentMask(e);

        mask.reset(componentTypeID);
        pool->RemoveComponent(e);
    }

    template<ComponentConcept T>
    [[nodiscard]] bool HasComponent(EntityID e)
    {
        auto componentTypeID = GetComponentID<T>();
        auto &mask = GetEntityComponentMask(e);
        return mask[componentTypeID];
    }

    template<ComponentConcept T>
    [[nodiscard]] T &GetComponent(EntityID e)
    {
        auto pool = GetComponentPool<T>();
        return pool->GetComponent(e);
    }

    template<SystemConcept T, typename... Args>
    std::shared_ptr<T> AddSystem(Args ...args)
    {
        auto systemId = GetSystemID<T>();
        auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
        m_SystemPool.emplace(systemId, ptr);
        ptr->m_ECS = this;

        m_SystemPool[systemId]->OnInitialize();

        return ptr;
    }

    template<SystemConcept T>
    void RemoveSystem()
    {
        auto systemId = GetSystemID<T>();
        auto it = m_SystemPool.find(systemId);
        it->second->OnShutdown();
        m_SystemPool.erase(it);
    }

    inline auto &GetEntities() { return m_Entities; }

    void UpdateAll();

    template<SystemConcept T>
    void Update()
    {
        auto systemId = GetSystemID<T>();
        auto it = m_SystemPool.find(systemId);
        it->second->OnUpdate();
    }

private:
    std::unordered_map<ComponentID, std::shared_ptr<IComponentPool>> m_ComponentPools;
    std::unordered_map<EntityID, ComponentMask> m_Entities;
    std::unordered_map<SystemID, std::shared_ptr<ISystem>> m_SystemPool;
};
}