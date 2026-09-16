# Deki I2S

Documentation: https://dekiengine.github.io/deki-i2s/ (components and properties, generated from the code)

I2S audio bus peripheral interface for the Deki Engine. Defines `IDekiI2S`: port selection, start, stop, and buffered writes with timeout.

Audio backends such as the MAX98357 driver in `deki-audio` push samples through this interface.

Part of the [Deki Engine](https://github.com/dekiengine/deki-engine) package ecosystem.

## Namespace

This package's types live in `DekiI2s`. Scene files store the qualified
name, so a component is `DekiI2s::SomeComponent` there, and code naming one
needs the namespace:

```cpp
using namespace DekiI2s;
obj->AddComponent<SomeComponent>();
```

Scenes saved before 0.16.0 used bare names and still load: every component
records what it used to be called, and a save writes the current name.

## Installation

Install via the Package Manager inside the Deki Editor.

## License

Licensed under the Apache License, Version 2.0. See [LICENSE](LICENSE) for details.
