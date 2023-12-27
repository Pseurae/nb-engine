#pragma once

#include <concepts>
#include <ranges>

#include "NB/ECS/internal.h"
#include "NB/ECS/Component.h"

namespace NB::ECS
{
class Manager;

class ISystem 
{
protected:
    virtual void OnInitialize() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnShutdown() = 0;

    friend class Manager;
};

template<int N, typename... Ts> using NthTypeOf =
        typename std::tuple_element<N, std::tuple<Ts...>>::type;

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

    template<std::size_t I, ComponentConcept T = NthTypeOf<I, Args...>>
    T &GetComponent(EntityID e)
    {
        return GetECS().template GetComponent<T>(e);
    }

    template<ComponentConcept T>
    requires((std::same_as<T, Args> || ...))
    T &GetComponent(EntityID e)
    {
        return GetECS().template GetComponent<T>(e);
    }
};

template<typename T>
concept SystemConcept = requires(T t){ []<typename... Args>(System<Args...>&){}(t); };

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

void test();