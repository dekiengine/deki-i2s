#include "DekiI2S.h"
#include "DekiLogSystem.h"

DekiI2S::Factory DekiI2S::s_Factory = nullptr;

void DekiI2S::SetFactory(Factory factory)
{
    s_Factory = factory;
    DEKI_LOG_INTERNAL("DekiI2S: Factory registered");
}

IDekiI2S* DekiI2S::Create()
{
    if (!s_Factory)
    {
        DEKI_LOG_ERROR("DekiI2S: No factory registered - platform package must call SetFactory()");
        return nullptr;
    }
    return s_Factory();
}

bool DekiI2S::HasFactory()
{
    return s_Factory != nullptr;
}
