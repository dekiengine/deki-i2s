// deki-i2s: the factory audio chips get their I2S channel from, and the package's plugin entry points, which
// register its components with the editor once however often it asks and let
// a reloaded package register them again.
//
// The registration functions reflection codegen generates are stood in for
// here, so the entry file is tested as it is.

#include <gtest/gtest.h>

#include "DekiI2S.h"

#include <deki/PackageConfig.h>
#include <deki/interop/Plugin.h>

#include <cstring>

using namespace DekiI2s;

namespace
{
int g_Registered = 0;
}

// Stand-ins for the generated registration functions the entry file calls.
void DekiI2SRegisterComponents()
{
    ++g_Registered;
}
int DekiI2SGetAutoComponentCount()
{
    return 3;
}
const Deki::ComponentMeta* DekiI2SGetAutoComponentMeta(int)
{
    return nullptr;
}

// The entry points, from the package's entry file.
extern "C"
{
    int DekiI2SEnsureRegistered(void);
    const char* DekiPluginGetName(void);
    const char* DekiPluginGetVersion(void);
    void DekiPluginShutdown(void);
    int DekiPluginGetComponentCount(void);
    void DekiPluginRegisterComponents(void);
}

namespace
{

class PackageTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        DekiPluginShutdown();
        g_Registered = 0;
    }
};

class Fake : public IDekiI2S
{
public:
    const char* GetPackageId() const override { return "i2s"; }
    const char* GetPackageName() const override { return "Fake"; }
    void Configure(const Deki::PackageConfig&) override {}
    bool Initialize() override { return true; }
    void Shutdown() override {}
    void Update(float) override {}
    Deki::PackageState GetState() const override { return Deki::PackageState::Running; }
    const char* GetLastError() const override { return ""; }
    int GetPort() const override { return 0; }
    int Write(const void*, size_t bytes, uint32_t) override { return static_cast<int>(bytes); }
    bool Start() override { return true; }
    bool Stop() override { return true; }
};

IDekiI2S* CreateFake()
{
    return new Fake();
}

}  // namespace

TEST_F(PackageTest, CreateNeedsTheFactoryAPlatformRegisters)
{
    DekiI2S::SetFactory(nullptr);
    EXPECT_FALSE(DekiI2S::HasFactory());
    EXPECT_EQ(DekiI2S::Create(), nullptr);

    DekiI2S::SetFactory(&CreateFake);
    EXPECT_TRUE(DekiI2S::HasFactory());
    IDekiI2S* a = DekiI2S::Create();
    IDekiI2S* b = DekiI2S::Create();
    ASSERT_NE(a, nullptr);
    EXPECT_NE(a, b);  // one instance per chip driver: a I2S links exactly two devices
    delete a;
    delete b;
    DekiI2S::SetFactory(nullptr);
}

TEST_F(PackageTest, ComponentsAreRegisteredOnce)
{
    EXPECT_EQ(DekiI2SEnsureRegistered(), 3);
    EXPECT_EQ(DekiI2SEnsureRegistered(), 3);
    DekiPluginRegisterComponents();
    EXPECT_EQ(g_Registered, 1);
    EXPECT_EQ(DekiPluginGetComponentCount(), 3);
}

TEST_F(PackageTest, AReloadedPackageRegistersAgain)
{
    DekiI2SEnsureRegistered();
    DekiPluginShutdown();
    DekiI2SEnsureRegistered();
    EXPECT_EQ(g_Registered, 2);
}

TEST_F(PackageTest, ThePluginNamesItselfAndItsVersion)
{
    EXPECT_GT(std::strlen(DekiPluginGetName()), 0u);
    EXPECT_STREQ(DekiPluginGetVersion(), "tests");  // DEKI_PACKAGE_VERSION, as the build sets it
}
