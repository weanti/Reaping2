#include "platform/i_platform.h"
#include "network/create_actor_message_handler_sub_system.h"
#include "create_actor_message.h"
#include "core/shot_collision_component.h"
namespace network {

    CreateActorMessageHandlerSubSystem::CreateActorMessageHandlerSubSystem()
        : MessageHandlerSubSystem()
        , mActorFactory(ActorFactory::Get())
    {

    }

    void CreateActorMessageHandlerSubSystem::Init()
    {

    }

    void CreateActorMessageHandlerSubSystem::Execute(Message const& message)
    {
        CreateActorMessage const& msg=static_cast<CreateActorMessage const&>(message);
        if (msg.mState==ActorEvent::Added)
        {
            //L1("executing createactor: %d \n",msg.mSenderId );
            std::auto_ptr<Actor> actor(mActorFactory(msg.mActorId));
            if(msg.mActorId==AutoId("pickup"))
            {
                L1("executing createactor: pickup! %d \n",msg.mSenderId );
            }
            actor->SetGUID(msg.mActorGUID);
            //TODO: handle parent from lower engine level (not only for shots)
            if (msg.mParentGUID!=-1)
            {
                Opt<ShotCollisionComponent> collisionC=actor->Get<ShotCollisionComponent>();
                if (collisionC.IsValid())
                {
                    Opt<Actor> parent=mScene.GetActor(msg.mParentGUID);
                    if(parent.IsValid())
                    {
                        collisionC->SetParentGUID(parent->GetGUID());
                    }
                }
            }
            L2("createactormessage executed with (GUID:%d)\n",actor->GetGUID());

            mScene.AddActor(actor.release());
        }
        else 
        {
            L2("createactormessage remove with (GUID:%d)\n",msg.mActorGUID);
            mScene.RemoveActor(msg.mActorGUID);
        }
    }

} // namespace engine

