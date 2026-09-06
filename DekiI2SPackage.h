#pragma once

#ifdef _WIN32
    #ifdef DEKI_I2S_EXPORTS
        #define DEKI_I2S_API __declspec(dllexport)
    #else
        #define DEKI_I2S_API __declspec(dllimport)
    #endif
#else
    #define DEKI_I2S_API __attribute__((visibility("default")))
#endif
