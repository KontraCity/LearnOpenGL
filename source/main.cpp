// Library {fmt}
#include <fmt/format.h>

// Custom modules
#include "graphics/window.hpp"
using namespace kc;

int main()
{
    try
    {
        Graphics::Window window(800, 600, "../../resources");
        window.run();
    }
    catch (const std::runtime_error& error)
    {
        fmt::print(stderr, "Runtime error: {}\n", error.what());
        return -1;
    }
}
