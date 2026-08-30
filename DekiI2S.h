#pragma once

#include "IDekiI2S.h"
#include "DekiI2SPackage.h"

/**
 * @brief Factory for I2S instances. Each chip driver owns its own I2S
 * (I2S is point-to-point, so there's no shared-bus registry).
 *
 * Platform integration packages (e.g. deki-esp32-integration) call SetFactory
 * at boot; chip drivers call Create() when they need an instance.
 */
class DEKI_I2S_API DekiI2S
{
public:
    using Factory = IDekiI2S* (*)();

    static void      SetFactory(Factory factory);
    static IDekiI2S* Create();
    static bool      HasFactory();

private:
    static Factory s_Factory;
};
