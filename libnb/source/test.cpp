#include "NB/ECS/Component.h"
#include "NB/ECS/Entity.h"
#include "NB/ECS/Manager.h"
#include "NB/ECS/System.h"

#include <iostream>

struct Component1 : public NB::ECS::Component { int i = 1; };
struct Component2 : public NB::ECS::Component { };

class System1 final : public NB::ECS::System<Component1> 
{
    virtual void OnInitialize()
    {
        std::cout << "OnInitialize" << std::endl;
    }

    virtual void OnUpdate()
    {
        for (auto i : GetAffectedEntities())
        {
            auto &c = GetComponent<Component1>(i);
            std::cout << "Test " << c.i << std::endl;            
        }
    }

    virtual void OnShutdown()
    {
        std::cout << "OnShutdown" << std::endl;
    }
};

#include "NB/Traits.h"

void test()
{
    NB::ECS::Manager ecs;
    ecs.RegisterComponent<Component1>();
    ecs.RegisterComponent<Component2>();

    NB::ECS::EntityID player = ecs.CreateEntity();
    ecs.AddComponent<Component1>(player);
    ecs.AddComponent<Component2>(player);

    NB::ECS::EntityID enemy = ecs.CreateEntity();
    ecs.AddComponent<Component1>(enemy);

    ecs.AddSystem<System1>();
    ecs.UpdateAll();
    ecs.RemoveSystem<System1>();
    ecs.UpdateAll();
}
