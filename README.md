# Deki I2S

Docs: https://dekiengine.github.io/deki-i2s/ (components and properties, generated from the code)

I2S audio bus peripheral interface for the Deki Engine. Defines `IDekiI2S`: port selection, start, stop, and buffered writes with timeout.

Audio backends such as the MAX98357 driver in `deki-audio` push samples through this interface.

Part of [Deki Engine](https://github.com/dekiengine/deki-engine).

## Namespace

Types live in `DekiI2s`. Scene files store the qualified name, and so does code:

```cpp
using namespace DekiI2s;
obj->AddComponent<SomeComponent>();
```

Scenes saved before 0.16.0 used bare names and still load; saving writes the current one.

## Install

Package Manager in the Deki Editor, or `DekiEditor --packages-add deki-i2s <project>`.

## License

Apache 2.0. See [LICENSE](LICENSE).
