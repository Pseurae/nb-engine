#pragma once

#include <ranges>

#include "NB/ECS/internal.h"
#include "NB/Traits.h"

namespace NB::ECS
{
namespace details
{
template<ComponentConcept... Args>
[[nodiscard]] constexpr ComponentMask GetComponentMask()
{
    ComponentMask mask;
    (mask.set(GetComponentID<Args>()), ...);
    return mask;
}
}

template<ComponentConcept... Args>
class System : public ISystem
{
public:
    inline const ComponentMask GetComponentMask() const { return details::GetComponentMask<Args...>(); }
private:
    Manager *m_ECS = nullptr;
    friend class Manager;

    [[nodiscard]] Manager &GetECS() { return *m_ECS; }
protected:
    auto GetAffectedEntities()
    {
        return GetECS().GetEntities() | 
            std::views::filter([this](auto kv) { return (kv.second & GetComponentMask()) == GetComponentMask(); }) | 
            std::views::transform([](auto kv) { return kv.first; });
    }

    template<std::size_t I, ComponentConcept T = typename NB::Traits::Parameters<Args...>::template Get<I>>
    T &GetComponent(EntityID e)
    {
        return GetECS().template GetComponent<T>(e);
    }

    template<ComponentConcept T>
    requires (NB::Traits::Parameters<Args...>::template Has<T>)
    T &GetComponent(EntityID e)
    {
        return GetECS().template GetComponent<T>(e);
    }
};

namespace details
{
struct system_id_impl
{
private:
    [[nodiscard]] static SystemID Next() 
    {
        static SystemID counter = INVALID_SYSTEM_ID;

        if (counter >= MAX_SYSTEMS)
            return INVALID_SYSTEM_ID;

        return ++counter;
    }
public:
    template<SystemConcept T>
    static inline SystemID value = Next();
};
}

template<typename T>
[[nodiscard]] static inline SystemID GetSystemID() { return details::system_id_impl::value<T>; }
}
