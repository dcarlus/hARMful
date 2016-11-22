#include <patterns/singleton/Singleton.hpp>

namespace Doom {
    Singleton::Singleton(Singleton&) {}

    Singleton::Singleton() noexcept {}

    Singleton::~Singleton() noexcept {}
}
