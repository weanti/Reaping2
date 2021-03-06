#include "platform/i_platform.h"
#include "network/data_checksum_message.h"

namespace network {

DataChecksumMessageSenderSystem::DataChecksumMessageSenderSystem()
    : MessageSenderSystem()
{
}


void DataChecksumMessageSenderSystem::Init()
{
    MessageSenderSystem::Init();
}


void DataChecksumMessageSenderSystem::Update(double DeltaTime)
{
    MessageSenderSystem::Update(DeltaTime);
}

DataChecksumMessageHandlerSubSystem::DataChecksumMessageHandlerSubSystem()
    : MessageHandlerSubSystem()
{
}


void DataChecksumMessageHandlerSubSystem::Init()
{
}

void DataChecksumMessageHandlerSubSystem::Update(double DeltaTime)
{
    MessageHandlerSubSystem::Update(DeltaTime);
}

void DataChecksumMessageHandlerSubSystem::Execute(Message const& message)
{
    DataChecksumMessage const& msg=static_cast<DataChecksumMessage const&>(message);
    if ( msg.mClientId == mProgramState.mClientId )
    {
        std::string data;
        boost::uint32_t cs(0);
        if ( "data.pkg" == msg.mDatasource )
        {
            Package pkg( AutoFile( new OsFile("data.pkg") ) );
            cs = pkg.Checksum();
        }
        if ( cs != msg.mChecksum )
        {
            L1("checksum mismatch for %s: server(%d) != client(%d)\n", msg.mDatasource.c_str(), msg.mChecksum, cs );
            //exit(1);
        }
    }
}

} // namespace network
REAPING2_CLASS_EXPORT_IMPLEMENT( network__DataChecksumMessage, network::DataChecksumMessage )
