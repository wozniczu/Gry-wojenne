#include "Battle.h"

Battle::Battle() : finished(false), arenaSprite(arenaTexture) {
    if (!arenaTexture.loadFromFile("textures/arena.jpg")) {
        std::cerr << "Nie można załadować tekstury areny!" << std::endl;
    }
    arenaSprite.setTexture(arenaTexture, true);
    // Domyślna inicjalizacja - 10 jednostek każdego typu po obu stronach
    for (int i = 0; i < 10; i++) {
        teamA.push_back(new Infantry(100.f + (i % 5) * 30.f, 100.f + (i / 5) * 30.f, true));
        teamA.push_back(new Archer(100.f + (i % 5) * 30.f, 200.f + (i / 5) * 30.f, true));
        teamA.push_back(new Cavalry(100.f + (i % 5) * 30.f, 300.f + (i / 5) * 30.f, true));

        teamB.push_back(new Infantry(1200.f - (i % 5) * 30.f, 100.f + (i / 5) * 30.f, false));
        teamB.push_back(new Archer(1200.f - (i % 5) * 30.f, 200.f + (i / 5) * 30.f, false));
        teamB.push_back(new Cavalry(1200.f - (i % 5) * 30.f, 300.f + (i / 5) * 30.f, false));
    }
}

Battle::Battle(int infantryA, int archerA, int cavalryA, int infantryB, int archerB, int cavalryB) : finished(false), arenaSprite(arenaTexture) {
    // Generator losowych pozycji
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribA_x(50.f, 400.f);
    std::uniform_real_distribution<float> distribB_x(1000.f, 1350.f);
    std::uniform_real_distribution<float> distrib_y(100.f, 700.f);

    if (!arenaTexture.loadFromFile("textures/arena.jpg")) {
        std::cerr << "Błd: Nie udało się załadować tekstury!" << std::endl;
    }

    arenaSprite.setTexture(arenaTexture, true);
    arenaSprite.setScale({
        1400.f / arenaTexture.getSize().x,
        800.f / arenaTexture.getSize().y
        });


    // Tworzenie jednostek dla Drużyny A
    for (int i = 0; i < infantryA; i++) {
        teamA.push_back(new Infantry(distribA_x(gen), distrib_y(gen), true));
    }

    for (int i = 0; i < archerA; i++) {
        teamA.push_back(new Archer(distribA_x(gen), distrib_y(gen), true));
    }

    for (int i = 0; i < cavalryA; i++) {
        teamA.push_back(new Cavalry(distribA_x(gen), distrib_y(gen), true));
    }

    // Tworzenie jednostek dla Drużyny B
    for (int i = 0; i < infantryB; i++) {
        teamB.push_back(new Infantry(distribB_x(gen), distrib_y(gen), false));
    }

    for (int i = 0; i < archerB; i++) {
        teamB.push_back(new Archer(distribB_x(gen), distrib_y(gen), false));
    }

    for (int i = 0; i < cavalryB; i++) {
        teamB.push_back(new Cavalry(distribB_x(gen), distrib_y(gen), false));
    }
}

Battle::~Battle() {
    for (auto& unit : teamA) {
        delete unit;
    }
    teamA.clear();

    for (auto& unit : teamB) {
        delete unit;
    }
    teamB.clear();
}

void Battle::update() {
    // Przygotuj wektor wszystkich jednostek
    std::vector<Unit*> allUnits;
    allUnits.insert(allUnits.end(), teamA.begin(), teamA.end());
    allUnits.insert(allUnits.end(), teamB.begin(), teamB.end());

    // Aktualizacja jednostek drużyny A
    for (auto& unit : teamA) {
        if (unit->isAlive()) {
            unit->update(allUnits);
        }
    }

    // Aktualizacja jednostek drużyny B
    for (auto& unit : teamB) {
        if (unit->isAlive()) {
            unit->update(allUnits);
        }
    }

    // Sprawdzenie, czy bitwa się zakończyła
    bool teamAAlive = false;
    bool teamBAlive = false;

    for (const auto& unit : teamA) {
        if (unit->isAlive()) {
            teamAAlive = true;
            break;
        }
    }

    for (const auto& unit : teamB) {
        if (unit->isAlive()) {
            teamBAlive = true;
            break;
        }
    }

    if (!teamAAlive || !teamBAlive) {
        finished = true;
    }
}

void Battle::draw(sf::RenderWindow& window) {
    // Rysowanie areny
    window.draw(arenaSprite);

    // Rysowanie jednostek
    for (const auto& unit : teamA) {
        if (unit->isAlive()) {
            window.draw(unit->getShape());
            // Rysowanie strzał dla łuczników
            if (auto archer = dynamic_cast<Archer*>(unit)) {
                archer->drawArrows(window);
            }
        }
    }

    for (const auto& unit : teamB) {
        if (unit->isAlive()) {
            window.draw(unit->getShape());
            // Rysowanie strzał dla łuczników
            if (auto archer = dynamic_cast<Archer*>(unit)) {
                archer->drawArrows(window);
            }
        }
    }

    // Rysowanie wyniku po zakończeniu bitwy
    if (finished) {
        sf::Font font;
        if (font.openFromFile("fonts/alpha_echo.ttf")) {
            sf::Text resultText(font, "");
            bool teamAAlive = false;
            bool teamBAlive = false;

            for (const auto& unit : teamA) {
                if (unit->isAlive()) {
                    teamAAlive = true;
                    break;
                }
            }

            for (const auto& unit : teamB) {
                if (unit->isAlive()) {
                    teamBAlive = true;
                    break;
                }
            }

            if (!teamAAlive && !teamBAlive) {
                resultText.setString("Bitwa zakończona remisem!");
                resultText.setFillColor(sf::Color::Black);
            }
            else if (!teamAAlive) {
                resultText.setString("CZERWONI WYGRALI");
                resultText.setFillColor(sf::Color::Red);
            }
            else {
                resultText.setString("NIEBIESCY WYGRALI");
                resultText.setFillColor(sf::Color::Blue);
            }

            // Wyrodkowanie tekstu
            sf::FloatRect textRect = resultText.getLocalBounds();
            resultText.setOrigin(textRect.getCenter());
            resultText.setPosition({ 700.f, 400.f });

            window.draw(resultText);
        }
    }
}


bool Battle::isFinished() const {
    return finished;
}