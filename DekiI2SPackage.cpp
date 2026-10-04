// Entry point of the deki-i2s package.
#include "DekiI2SPackage.h"
#include <deki/interop/Plugin.h>
#include <deki/LogSystem.h>

extern void DekiI2SRegisterComponents();
extern int DekiI2SGetAutoComponentCount();
extern const Deki::ComponentMeta* DekiI2SGetAutoComponentMeta(int index);

namespace DekiI2s
{

#ifdef DEKI_EDITOR
#endif

static bool s_I2SRegistered = false;

}  // namespace DekiI2s
// The exports below are C symbols at global scope; the package's own
// registration helpers and statics live in its namespace.
using namespace DekiI2s;

extern "C"
{
    DEKI_I2S_API int DekiI2SEnsureRegistered(void)
    {
#ifdef DEKI_EDITOR
        if (s_I2SRegistered)
        {
            return ::DekiI2SGetAutoComponentCount();
        }
        s_I2SRegistered = true;
        ::DekiI2SRegisterComponents();
        return ::DekiI2SGetAutoComponentCount();
#else
        return 0;
#endif
    }

    DEKI_PLUGIN_API const char* DekiPluginGetName(void)
    {
        return "Deki I2S Package";
    }
    DEKI_PLUGIN_API const char* DekiPluginGetVersion(void)
    {
#ifdef DEKI_PACKAGE_VERSION
        return DEKI_PACKAGE_VERSION;
#else
        return "0.0.0-dev";
#endif
    }
    DEKI_PLUGIN_API int DekiPluginInit(void)
    {
        return 0;
    }
    DEKI_PLUGIN_API void DekiPluginShutdown(void)
    {
        s_I2SRegistered = false;
    }

#ifdef DEKI_EDITOR
    DEKI_PLUGIN_API int DekiPluginGetComponentCount(void)
    {
        return ::DekiI2SGetAutoComponentCount();
    }
    DEKI_PLUGIN_API const Deki::ComponentMeta* DekiPluginGetComponentMeta(int index)
    {
        return ::DekiI2SGetAutoComponentMeta(index);
    }
#else
    DEKI_PLUGIN_API int DekiPluginGetComponentCount(void)
    {
        return 0;
    }
    DEKI_PLUGIN_API const Deki::ComponentMeta* DekiPluginGetComponentMeta(int)
    {
        return nullptr;
    }
#endif

    DEKI_PLUGIN_API void DekiPluginRegisterComponents(void)
    {
#ifdef DEKI_EDITOR
        DekiI2SEnsureRegistered();
#endif
    }

    // A utility package that is only a facade: nothing else to register at load.

}  // extern "C"
