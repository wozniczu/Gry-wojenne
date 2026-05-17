#include "Assets.h"

#ifdef _WIN32
#include <Windows.h>
#endif

namespace assets {
namespace {

bool openFontPath(sf::Font &font, const std::string &path) { return font.openFromFile(path); }

#ifdef _WIN32
bool openWindowsArial(sf::Font &font)
{
    char windir[MAX_PATH]{};
    if (GetWindowsDirectoryA(windir, MAX_PATH) == 0U) {
        return false;
    }
    std::string full = std::string(windir) + "\\Fonts\\arial.ttf";
    return openFontPath(font, full);
}
#endif

} // namespace

bool tryLoadUiFont(sf::Font &font)
{
    const char *candidates[] = {"fonts/arial.ttf", "fonts/Arial.ttf"};
    for (const char *p : candidates) {
        if (openFontPath(font, p)) {
            return true;
        }
    }

#ifdef _WIN32
    if (openWindowsArial(font)) {
        return true;
    }
#endif
    return false;
}

bool tryLoadBattleBannerFont(sf::Font &font)
{
    if (openFontPath(font, "fonts/alpha_echo.ttf")) {
        return true;
    }
    return tryLoadUiFont(font);
}

bool tryLoadMenuTexture(sf::Texture &texture)
{
    if (texture.loadFromFile("textures/menu.png")) {
        return true;
    }

    sf::Image image{};
    image.resize({1400u, 800u}, sf::Color(25, 55, 105));
    return texture.loadFromImage(image);
}

bool tryLoadArenaTexture(sf::Texture &texture)
{
    if (texture.loadFromFile("textures/arena.png")) {
        return true;
    }

    sf::Image image{};
    image.resize({1400u, 800u}, sf::Color(62, 45, 34));
    return texture.loadFromImage(image);
}

} // namespace assets
