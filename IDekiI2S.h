#pragma once

#include <deki/providers/IPackage.h>
#include <cstdint>
#include <cstddef>

namespace DekiI2s
{

/// An I2S peripheral.
///
/// I2S is point-to-point: each audio chip owns its own I2S instance. The chip
/// driver gets one from DekiI2S::Create(), sets pins and format through
/// PackageConfig, then streams samples with Write().
///
/// Pin names in PackageConfig.pins: "BCLK", "LRCLK", "DOUT".
/// Settings in PackageConfig.settings:
///   "i2sPort"         -> int (default 0)
///   "sampleRate"      -> int (default 16000)
///   "bits_per_sample" -> int (default 16)
///   "channels"        -> int (1 = mono, 2 = stereo; default 1)
class IDekiI2S : public Deki::IPackage
{
public:
    const char* GetPackageCategory() const override { return "i2s"; }

    virtual int GetPort() const = 0;

    /// Writes `bytes` bytes of interleaved PCM samples to the I2S TX channel,
    /// blocking up to `timeoutMs` for DMA space. Returns the bytes written,
    /// which can be fewer than asked on a timeout.
    virtual int Write(const void* data, size_t bytes, uint32_t timeoutMs) = 0;

    virtual bool Start() = 0;
    virtual bool Stop() = 0;
};

}  // namespace DekiI2s
