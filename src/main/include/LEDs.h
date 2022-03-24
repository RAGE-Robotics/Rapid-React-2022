#pragma once

#include "Rage2022.h"
//#include <vector>
//#include "Enemy.h"

class LEDs // His name is clide
{
public:
    LEDs();
    void setRange(int startIndex, int width, char iRed, char iGreen, char iBlue);
    void clear();
    void displayTeamColor();
    void displayRainbow();
    void displayFallingLights();
    void displayRedWhiteAndBlue();
    void updateLEDs();

    // LED Game Stuff
    // void runLEDGame();
    // void addEnemy(int p_pos, int p_dir, EnemyType p_type);
    // void nextGameStage();

private:
    static constexpr int kLength = 250;
    // // PWM port 9
    // // Must be a PWM header, not MXP or DIO
    frc::AddressableLED m_led{9};
    std::array<frc::AddressableLED::LEDData, kLength>
        m_ledBuffer; // Reuse the buffer

    frc::Timer m_LEDTimer;

#if 0
    const double baseSpawnRate = 1 / 100.0; // Chance of enemy spawning on given frame

    std::vector<Enemy> enemies;

    std::vector<GameStage> m_gameStages{
        GameStage(                 // Stage 1
            1.2,                   // Speed Multiplier
            1.0,                   // Spawn Rate Multiplier
            std::vector<EnemyType>{// Enemy Types
                EnemyType::RED_ENEMY},
            std::vector<int>{100}), // 100% chance of red enemy
        GameStage(                  // Stage 2
            1.2,
            1.0,
            std::vector<EnemyType>{
                EnemyType::RED_ENEMY,
                EnemyType::PURPLE_ENEMY},
            std::vector<int>{50, 50}), // 50/50 mix of red and purple
        GameStage(                     // Stage 3
            1.5,
            1.0,
            std::vector<EnemyType>{
                EnemyType::RED_ENEMY,
                EnemyType::PURPLE_ENEMY,
                EnemyType::GOLD_ENEMY},
            std::vector<int>{70, 20, 10}),
        GameStage(                     // Stage 4
            1.5,
            2.0,
            std::vector<EnemyType>{
                EnemyType::RED_ENEMY,
                EnemyType::PURPLE_ENEMY,
                EnemyType::GOLD_ENEMY},
            std::vector<int>{70, 20, 10})};

    unsigned int stageIndex = 3;
    int rand1 = rand() % 256;
    int rand2 = rand() % 256;
#endif
};
