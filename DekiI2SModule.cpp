#include "DekiI2SPackage.h"
#include "interop/DekiPlugin.h"
#include "DekiLogSystem.h"

#ifdef DEKI_EDITOR
extern void DekiI2S_RegisterComponents();
extern int  DekiI2S_GetAutoComponentCount();
extern const DekiComponentMeta* DekiI2S_GetAutoComponentMeta(int index);
#endif

static bool s_I2SRegistered = false;

extern "C" {

DEKI_I2S_API int DekiI2S_EnsureRegistered(void)
{
#ifdef DEKI_EDITOR
    if (s_I2SRegistered) return DekiI2S_GetAutoComponentCount();
    s_I2SRegistered = true;
    DekiI2S_RegisterComponents();
    return DekiI2S_GetAutoComponentCount();
#else
    return 0;
#endif
}

DEKI_PLUGIN_API const char* DekiPlugin_GetName(void)    { return "Deki I2S Package"; }
DEKI_PLUGIN_API const char* DekiPlugin_GetVersion(void)
{
#ifdef DEKI_PACKAGE_VERSION
    return DEKI_PACKAGE_VERSION;
#else
    return "0.0.0-dev";
#endif
}
DEKI_PLUGIN_API int  DekiPlugin_Init(void)     { DEKI_LOG_INFO("[deki-i2s] DekiPlugin_Init"); return 0; }
DEKI_PLUGIN_API void DekiPlugin_Shutdown(void) { s_I2SRegistered = false; }

#ifdef DEKI_EDITOR
DEKI_PLUGIN_API int  DekiPlugin_GetComponentCount(void) { return DekiI2S_GetAutoComponentCount(); }
DEKI_PLUGIN_API const DekiComponentMeta* DekiPlugin_GetComponentMeta(int index)
{
    return DekiI2S_GetAutoComponentMeta(index);
}
#else
DEKI_PLUGIN_API int  DekiPlugin_GetComponentCount(void) { return 0; }
DEKI_PLUGIN_API const DekiComponentMeta* DekiPlugin_GetComponentMeta(int) { return nullptr; }
#endif

DEKI_PLUGIN_API void DekiPlugin_RegisterComponents(void)
{
#ifdef DEKI_EDITOR
    int n = DekiI2S_EnsureRegistered();
    DEKI_LOG_INFO("[deki-i2s] DekiPlugin_RegisterComponents -> %d component(s)", n);
#endif
}


// Pure utility package — facade-only. Nothing to register at package load.

}  // extern "C"
