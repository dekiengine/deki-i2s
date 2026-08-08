#pragma once

#include "providers/IDekiModule.h"
#include <cstdint>
#include <cstddef>

/**
 * @brief Abstract I2S peripheral interface.
 *
 * I2S is point-to-point: each audio chip owns its own I2S instance.
 * The chip driver acquires one via DekiI2S::Create(), configures
 * pins/format via ModuleConfig, then streams samples with Write().
 *
 * Pin names in ModuleConfig.pins: "BCLK", "LRCLK", "DOUT".
 * Settings in ModuleConfig.settings:
 *   "i2s_port"        -> int    (default 0)
 *   "sample_rate"     -> int    (default 16000)
 *   "bits_per_sample" -> int    (default 16)
 *   "channels"        -> int    (1 = mono, 2 = stereo; default 1)
 */
class IDekiI2S : public IDekiModule
{
public:
    const char* GetModuleCategory() const override { return "i2s"; }

    virtual int  GetPort() const = 0;

    /**
     * @brief Write raw PCM samples to the I2S TX channel.
     * @param data       Pointer to interleaved sample bytes.
     * @param bytes      Number of bytes to write.
     * @param timeoutMs  Max time to block waiting for DMA space.
     * @return Bytes actually written (may be less than requested on timeout).
     */
    virtual int  Write(const void* data, size_t bytes, uint32_t timeoutMs) = 0;

    virtual bool Start() = 0;
    virtual bool Stop()  = 0;
};
