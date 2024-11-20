#include "../Header Files/VGE.WindowsPlatform.h"
#include "../../Core/Header Files/VGE.Platform.h"

namespace VGE {

std::unique_ptr<IPlatform> PlatformFactory::createPlatform() {
#ifdef _WIN32
    return std::make_unique<WindowsPlatform>();
#else
    #error "Platform not supported"
#endif
}

} // namespace VGE
