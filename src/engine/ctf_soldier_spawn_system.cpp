#include "platform/i_platform.h"
#include "ctf_soldier_spawn_system.h"
#include "engine.h"
#include "soldier_spawn_system.h"
#include "core/map/ctf_soldier_spawn_point_map_element_system.h"
#include "core/ctf_program_state.h"

namespace engine {
namespace ctf {
CtfSoldierSpawnSystem::CtfSoldierSpawnSystem()
    : mScene( Scene::Get() )
    , mActorFactory( ActorFactory::Get() )
    , mPlayerAutoId(AutoId("player"))
{
}


void CtfSoldierSpawnSystem::Init()
{
    mOnRevive=EventServer<core::ReviveEvent>::Get().Subscribe( boost::bind( &CtfSoldierSpawnSystem::OnRevive, this, _1 ) );
}


void CtfSoldierSpawnSystem::Update(double DeltaTime)
{
}

void CtfSoldierSpawnSystem::OnRevive(core::ReviveEvent const& Evt)
{
    if (mEnabled)
    {
        Opt<::ctf::ClientData> ctfClientData(::ctf::ProgramState::Get().FindClientDataByClientId(Evt.mClientData->mClientId));
        if (ctfClientData.IsValid())
        {
            std::auto_ptr<Actor> player(Spawn(*Evt.mClientData, ctfClientData->mTeam));
            mScene.AddActor(player.release());
        }
    }
}

std::auto_ptr<Actor> CtfSoldierSpawnSystem::Spawn(::core::ClientData& clientData, ::ctf::Team::Type team)
{
    map::SpawnPoints_t spawnPoints(map::ctf::CtfSoldierSpawnPointMapElementSystem::Get()->GetActiveSpawnPoints(team));
    map::SpawnPoint spawnPoint(spawnPoints[rand()%spawnPoints.size()]);
    std::auto_ptr<Actor> player(mActorFactory(mPlayerAutoId));
    return SoldierSpawnSystem::Get()->Spawn(clientData,spawnPoint,player);
}

Opt<CtfSoldierSpawnSystem> CtfSoldierSpawnSystem::Get()
{
    return Engine::Get().GetSystem<CtfSoldierSpawnSystem>();
}

} // namespace ctf
} // namespace engine

