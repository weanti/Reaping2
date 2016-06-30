#include "hdouble_room1.h"
#include "core/i_position_component.h"
#include "random.h"

namespace map {

HDoubleRoom1::HDoubleRoom1( int32_t Id )
    : IRoom( Id )
    , mActorFactory( ActorFactory::Get() )
{
    mRoomDesc.SetCellCount( 2 );
    mRoomDesc.SetCellSize( 1000 );
    mRoomDesc.GetCell( 0, 0 ).mPossibleEntrances = { Cell::Top, Cell::Bottom, Cell::Left };
    mRoomDesc.GetCell( 0, 0 ).mFilled = true;
    mRoomDesc.GetCell( 1, 0 ).mPossibleEntrances = { Cell::Top, Cell::Right, Cell::Bottom };
    mRoomDesc.GetCell( 1, 0 ).mFilled = true;
    mRoomDesc.GetProperties() = { RoomDesc::Start,RoomDesc::End };
    mRoomDesc.SetRoom( this );
}

void HDoubleRoom1::Generate( RoomDesc& roomDesc, int32_t x, int32_t y )
{
    std::auto_ptr<Actor> wall;// = mActorFactory( AutoId( "wall" ) );

    int cellCount = mRoomDesc.GetCellSize() / 100;
    for (int i = 0; i < cellCount*cellCount*2; ++i)
    {
        auto& entrances00 = roomDesc.GetCell( 0, 0 ).mPossibleEntrances;
        auto& entrances10 = roomDesc.GetCell( 1, 0 ).mPossibleEntrances;
        if (i < cellCount * 2 
                && (i<cellCount&&entrances00.find( Cell::Top ) == entrances00.end()
                    || i>=cellCount&&entrances10.find( Cell::Top ) == entrances10.end())
            || i >= (cellCount - 1)*cellCount * 2
                && (i < (cellCount - 1)*cellCount * 2+cellCount &&entrances00.find( Cell::Bottom ) == entrances00.end()
                    || i >= (cellCount - 1)*cellCount * 2 + cellCount&&entrances10.find( Cell::Bottom ) == entrances10.end())
            || i%(cellCount*2) == 0 && entrances00.find( Cell::Left ) == entrances00.end()
            || i%(cellCount*2) == cellCount*2 - 1 && entrances10.find( Cell::Right ) == entrances10.end())
        {
            wall = mActorFactory( AutoId( "wall_small" ) );
            Opt<IPositionComponent> positionC = wall->Get<IPositionComponent>();
            positionC->SetX( i%(cellCount*2)*100.0 + x );
            positionC->SetY( i / (cellCount*2)*100.0 + y );
            roomDesc.mPlacedActorGUIDs.push_back( wall->GetGUID() );
            mScene.AddActor( wall.release() );
        }
    }
    for (int i = 0; i < 10; ++i)
    {
        wall = mActorFactory( AutoId( "wall_small" ) );
        Opt<IPositionComponent> positionC = wall->Get<IPositionComponent>();
        positionC->SetX( (mRand() % (cellCount*2 - 2) + 1)*100.0 + x );
        positionC->SetY( (mRand() % (cellCount - 2) + 1)*100.0 + y );
        roomDesc.mPlacedActorGUIDs.push_back( wall->GetGUID() );
        mScene.AddActor( wall.release() );
    }
    if (roomDesc.GetProperties().find( RoomDesc::Start ) != roomDesc.GetProperties().end())
    {
        PlaceSoldierSpawnPoint( roomDesc, x + 200, y + 200 );
    }
    if (roomDesc.GetProperties().find( RoomDesc::End ) != roomDesc.GetProperties().end())
    {
        PlaceLevelEndPoint( roomDesc, x + 400, y + 300 );
    }
}

} // namespace map

