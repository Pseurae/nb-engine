#pragma once

#include "NB/ECS/internal.h"

namespace NB::ECS
{
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

template<typename T>
[[nodiscard]] ComponentID GetComponentID() { return details::component_id_impl::value<T>; }
}