#include "Battle.h"

Battle::Battle() : finished(false), arenaSprite(arenaTexture) {
    if (!arenaTexture.loadFromFile("arena.jpg")) {
        std::cerr << "Nie mo¿na za³adowaæ tekstury areny!" << std::endl;
    }
    arenaSprite.setTexture(arenaTexture, true);
    // Domyœlna inicjalizacja - 10 jednostek ka¿dego typu po obu stronach
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

    if (!arenaTexture.loadFromFile("arena.jpg")) {
        std::cerr << "B³¹d: Nie uda³o siê za³adowaæ tekstury!" << std::endl;
    }

    arenaSprite.setTexture(arenaTexture, true);
    arenaSprite.setScale({
        1400.f / arenaTexture.getSize().x,
        800.f / arenaTexture.getSize().y
    });


    // Tworzenie jednostek dla Dru¿yny A
    for (int i = 0; i < infantryA; i++) {
        teamA.push_back(new Infantry(distribA_x(gen), distrib_y(gen), true));
    }

    for (int i = 0; i < archerA; i++) {
        teamA.push_back(new Archer(distribA_x(gen), distrib_y(gen), true));
    }

    for (int i = 0; i < cavalryA; i++) {
        teamA.push_back(new Cavalry(distribA_x(gen), distrib_y(gen), true));
    }

    // Tworzenie jednostek dla Dru¿yny B
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
    // Aktualizacja jednostek dru¿yny A
    for (auto& unit : teamA) {
        if (unit->isAlive()) {
            unit->update(teamB);
        }
    }

    // Aktualizacja jednostek dru¿yny B
    for (auto& unit : teamB) {
        if (unit->isAlive()) {
            unit->update(teamA);
        }
    }

    // Sprawdzenie, czy bitwa siê zakoñczy³a
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

        if (!teamAAlive && !teamBAlive) {
            std::cout << "Bitwa zakoñczona remisem!" << std::endl;
        }
        else if (!teamAAlive) {
            std::cout << "Dru¿yna B (Czerwona) wygra³a bitwê!" << std::endl;
        }
        else {
            std::cout << "Dru¿yna A (Niebieska) wygra³a bitwê!" << std::endl;
        }
    }
}

void Battle::draw(sf::RenderWindow& window) {
    // Rysowanie areny
    window.draw(arenaSprite);

    // Rysowanie jednostek
    for (const auto& unit : teamA) {
        if (unit->isAlive()) {
            window.draw(unit->getShape());
        }
    }

    for (const auto& unit : teamB) {
        if (unit->isAlive()) {
            window.draw(unit->getShape());
        }
    }

    // Rysowanie wyniku po zakoñczeniu bitwy
    if (finished) {
        sf::Font font;
        if (font.openFromFile("alpha_echo.ttf")) {
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
                resultText.setString("Bitwa zakoñczona remisem!");
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

            // Wyœrodkowanie tekstu
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

void Battle::displayUnitsHealth() const {
    int activeUnitsA = 0;
    int activeUnitsB = 0;

    for (const auto& unit : teamA) {
        if (unit->isAlive()) {
            activeUnitsA++;
        }
    }

    for (const auto& unit : teamB) {
        if (unit->isAlive()) {
            activeUnitsB++;
        }
    }

    std::cout << "Pozosta³o jednostek: Dru¿yna A: " << activeUnitsA << ", Dru¿yna B: " << activeUnitsB << std::endl;
}