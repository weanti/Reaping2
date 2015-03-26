#ifndef INCLUDED_CORE_SHOT_COLLISION_COMPONENT_H
#define INCLUDED_CORE_SHOT_COLLISION_COMPONENT_H

#include "core/collision_component.h"
#include "core/property_loader.h"

class ShotCollisionComponent : public CollisionComponent
{
public:
    virtual void SetDamage( int32_t Damage );
    virtual int32_t GetDamage() const;
    virtual void SetParentGUID( int32_t parentGUID );
    virtual int32_t GetParentGuid() const;
protected:
    ShotCollisionComponent();
    friend class ComponentFactory;
    int32_t mDamage;
    int32_t mParentGUID;
};

class ShotCollisionComponentLoader: public ComponentLoader<ShotCollisionComponent>
{
    virtual void BindValues();
protected:
    ShotCollisionComponentLoader();
    friend class ComponentLoaderFactory;
};

#endif//INCLUDED_CORE_SHOT_COLLISION_COMPONENT_H
