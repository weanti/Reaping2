#include "platform/i_platform.h"
#include "engine/collisions/shot_collision_sub_system.h"
#include "engine/engine.h"
#include "platform/auto_id.h"
#include "core/i_health_component.h"
#include "core/shot_collision_component.h"
#include "core/i_position_component.h"
#include "core/i_notify_parent_on_death_component.h"

namespace engine {

ShotCollisionSubSystem::ShotCollisionSubSystem()
    : CollisionSubSystem()
{

}

void ShotCollisionSubSystem::Init()
{
}

void ShotCollisionSubSystem::Update(Actor& actor, double DeltaTime)
{
    if (!mOther)
    {
        return;
    }
    Opt<ShotCollisionComponent> shotCC=actor.Get<ShotCollisionComponent>();
    Opt<IHealthComponent> otherHealthC=mOther->Get<IHealthComponent>();
    Opt<IHealthComponent> healthC = actor.Get<IHealthComponent>();
    Opt<IPositionComponent> positionC = actor.Get<IPositionComponent>();    

    if( mOther->GetGUID() == shotCC->GetParentGuid() )
    {
        return;
    }

    if(otherHealthC.IsValid()&&otherHealthC->IsAlive())
    {
        otherHealthC->TakeDamage(shotCC->GetDamage());
    }
    if (healthC.IsValid())
    {
        healthC->SetHP(0);
    }
    Opt<INotifyParentOnDeathComponent> notifyParentC=actor.Get<INotifyParentOnDeathComponent>();
    if(notifyParentC.IsValid())
    {
        notifyParentC->SetKillerGUID(mOther->GetGUID());
    }


}

void ShotCollisionSubSystem::ClipScene(Actor& actor)
{
    Opt<ShotCollisionComponent> shotCC=actor.Get<ShotCollisionComponent>();
    Opt<IPositionComponent> positionC = actor.Get<IPositionComponent>();
    Opt<IHealthComponent> healthC = actor.Get<IHealthComponent>();

    double radius=shotCC->GetRadius();
    glm::vec4 const& AllowedDimensions = mScene.GetDimensions();
    if( positionC->GetX() + radius < AllowedDimensions.x * 2 ||
        positionC->GetX() - radius > AllowedDimensions.z * 2 ||
        positionC->GetY() + radius < AllowedDimensions.y * 2 ||
        positionC->GetY() - radius > AllowedDimensions.w * 2 )
    {
        healthC->SetHP(0);  
    }
}

} // namespace engine

