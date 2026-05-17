#pragma once
#include <SFML/Graphics.hpp>

namespace assets {

bool tryLoadUiFont(sf::Font &font);

bool tryLoadBattleBannerFont(sf::Font &font);

bool tryLoadMenuTexture(sf::Texture &texture);

bool tryLoadArenaTexture(sf::Texture &texture);

} // namespace assets
