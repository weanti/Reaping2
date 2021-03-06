#ifndef INCLUDED_CORE_SCRIPTED_CONTROLLER_DISTANCE_TO_TARGET_CONDITION_H
#define INCLUDED_CORE_SCRIPTED_CONTROLLER_DISTANCE_TO_TARGET_CONDITION_H

#include "platform/frequency_timer.h"
#include "distance_condition.h"

namespace scriptedcontroller
{

class DistanceToTargetCondition : public DistanceCondition
{
public:
    DEFINE_DISTANCE_CONDITION_BASE( DistanceToTargetCondition )
    virtual void Update( Actor& actor, double Seconds );
    virtual void Reset( Actor& actor );
    virtual void Load( Json::Value const& setters );

    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize( Archive& ar, const unsigned int version );
protected:
    FrequencyTimer mTimer;
};

template<class Archive>
void DistanceToTargetCondition::serialize( Archive& ar, const unsigned int version )
{
    ar & boost::serialization::base_object<DistanceCondition>( *this );
}

} // namespace scriptedcontroller

#endif//INCLUDED_CORE_SCRIPTED_CONTROLLER_DISTANCE_TO_TARGET_CONDITION_H
