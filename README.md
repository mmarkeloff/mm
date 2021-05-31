<h1 align="center">
mm
</h1>

C++ module manager.

Header-only library implements manager to dynamic loading a shared objects at runtime.

### Build

See [BUILD.md](BUILD.md) for details.

## Usage

### some_mod_int.hpp

```cpp
#include <memory>

#include "mod_int.hpp"
#include "some_mod_impl.hpp"

class SomeModInterface: public mm::BaseModInterface {
private:
    std::shared_ptr<SomeModImpl> m_ModImpl;
public:
    SomeModInterface();

    void* getImpl() const noexcept override;
};

__MM_INSTANCE_TMPL(SomeModInterface)
```

### some_mod_impl.hpp

```cpp
class SomeModImpl {
public:
    virtual void impl() const noexcept;
};
```

### some_mod.cpp

```cpp
#include "some_mod_int.hpp"
#include "some_mod_impl.hpp"

SomeModInterface::SomeModInterface() : m_ModImpl{new SomeModImpl} {}
void* SomeModInterface::getImpl() const noexcept { return m_ModImpl.get(); }

void SomeModImpl::impl() const noexcept { }
```

### main.cpp

```cpp
#include "mod_factory.hpp"
#include "some_mod_impl.hpp"

#define SOME_MODID 0x1

int main(int argc, char* argv[]) {
    mm::ModMgr::instance().add({SOME_MODID, "some-mod"});

    mm::ModFactory factory{SOME_MODID};
    if (factory.isInitialised()) {
        auto modInterface = factory.instance();

        auto modImpl = static_cast<SomeModImpl*>(modInterface->getImpl());
        modImpl->impl();
    }

    return 0;
}
```

## Supported OS's

Only Linux/macOS.

## Examples

See [sample project](sample) for more complete usage examples.

## Documentation

See automatic generated [docs](https://mmarkeloff.github.io/mm/) for more information.
