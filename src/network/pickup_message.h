#ifndef INCLUDED_NETWORK_PICKUP_MESSAGE_H
#define INCLUDED_NETWORK_PICKUP_MESSAGE_H

#include "network/message.h"
#include "network/message_handler_sub_system.h"
#include "network/message_sender_system.h"
#include "core/item.h"
#include "engine/collisions/pickup_collision_sub_system.h"
#include "core/actor_event.h"
namespace network {

    class PickupMessage: public Message
    {
        friend class ::boost::serialization::access;
    public:
        DEFINE_MESSAGE_BASE(PickupMessage)
        int32_t mActorGUID;
        Item::ItemType mItemType;
        int32_t mItemId;
        PickupMessage()
            : mActorGUID(0)
            , mItemType(Item::Normal)
            , mItemId(0)
        {
        }
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version);
    };

    template<class Archive>
    void PickupMessage::serialize(Archive& ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Message>(*this);
        ar & mActorGUID;
        ar & mItemType;
        ar & mItemId;
    }

    class SetPickupContentMessage: public Message
    {
        friend class ::boost::serialization::access;
    public:
        DEFINE_MESSAGE_BASE(SetPickupContentMessage)
        int32_t mActorGUID;
        Item::ItemType mItemType;
        int32_t mContentId;
        SetPickupContentMessage()
            : mActorGUID(0)
            , mItemType(Item::Normal)
            , mContentId(0)
        {
        }
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version);
    };

    template<class Archive>
    void SetPickupContentMessage::serialize(Archive& ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Message>(*this);
        ar & mActorGUID;
        ar & mItemType;
        ar & mContentId;
    }

    class PickupMessageHandlerSubSystem: public MessageHandlerSubSystem
    {
    public:
        DEFINE_SUB_SYSTEM_BASE(PickupMessageHandlerSubSystem)
        PickupMessageHandlerSubSystem();
        virtual void Init();
        virtual void Execute(Message const& message );
    };

    class SetPickupContentMessageHandlerSubSystem: public MessageHandlerSubSystem
    {
    public:
        DEFINE_SUB_SYSTEM_BASE(SetPickupContentMessageHandlerSubSystem)
        SetPickupContentMessageHandlerSubSystem();
        virtual void Init();
        virtual void Execute(Message const& message );
    };

    class PickupMessageSenderSystem: public MessageSenderSystem
    {
        AutoReg mOnPickup;
        void OnPickup( engine::PickupEvent const& Evt );
        AutoReg mOnActorEvent;
        void OnActorEvent( ActorEvent const& Evt );
    public:
        DEFINE_SYSTEM_BASE(PickupMessageSenderSystem)
        PickupMessageSenderSystem();
        virtual void Init();
        virtual void Update( double DeltaTime );
    };

} // namespace network
#endif//INCLUDED_NETWORK_PICKUP_MESSAGE_H