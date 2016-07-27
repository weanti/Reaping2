#ifndef INCLUDED_MAP_GROUP_SELECTED_EVENT_H
#define INCLUDED_MAP_GROUP_SELECTED_EVENT_H

#include "platform/event.h"

namespace map {

struct GroupSelectedEvent : public platform::Event
{
    std::string mGroupName;
    GroupSelectedEvent(std::string groupName)
        :mGroupName(groupName){}
};

} // namespace map

#endif//INCLUDED_MAP_GROUP_SELECTED_EVENT_H

//command:  "classgenerator.exe" -g "event" -n "map" -c "group_selected_event" -m "std::string-groupName"
