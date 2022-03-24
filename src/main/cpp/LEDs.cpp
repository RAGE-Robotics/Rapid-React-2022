#include "LEDs.h"

LEDs::LEDs()
{
    m_LEDTimer.Reset();
    m_LEDTimer.Start();

    m_led.SetLength(kLength);
    m_led.SetData(m_ledBuffer);
    m_led.Start();
}

void LEDs::displayRainbow()
{
    int spacing = 3;

    for (int i = 0; i < kLength; i++)
    {
        // Alternate sin function movement
        // int shift = (int)(sin(m_timer.Get()) * kLength / 2 + kLength / 2);

        // Shift at a rate of 10 lights per seconds
        int shift = (int)(m_LEDTimer.Get() * 10);
        // Shift the lights, duplicate at each spacing interval, and wrap the value to the length of the LED array
        int offset = (shift % kLength) % spacing;
        // Final value to determine if an LED should be lit. Separated from the if statement for tidyness
        bool shouldLight = (i % spacing) == offset;
        if (shouldLight)
        {
            m_ledBuffer[i].SetHSV(
                (int)((i / (float)kLength) * 180 + ((int)m_LEDTimer.Get() * 180)) % 180, // Rotating hue, 180 degrees a second
                255,                                                                     // Max shade
                255);                                                                    // Max value
        }
        else
        {
            m_ledBuffer[i].SetRGB(0, 0, 0); // idk what
        }
    }
    m_led.SetData(m_ledBuffer); // This turns the lights on
}

void LEDs::displayTeamColor()
{
    auto alliance = frc::DriverStation::GetAlliance();
    for (int i = 0; i < kLength; i++)
    {
        if (alliance == frc::DriverStation::kRed)
        {
            m_ledBuffer[i].SetRGB(255, 0, 0); // Red
        }
        else
        {
            m_ledBuffer[i].SetRGB(0, 0, 255); // Blue
        }
    }
    m_led.SetData(m_ledBuffer); // This turns the lights on
}

void LEDs::displayFallingLights()
{
    int spacing = 3;

    for (int i = 0; i < kLength; i++)
    {
        // Alternate sin function movement
        // int shift = (int)(sin(m_LEDTimer.Get()) * kLength / 2 + kLength / 2);

        // Shift at a rate of 10 lights per seconds
        int shift = (int)(m_LEDTimer.Get() * 10);
        // Shift the lights, duplicate at each spacing interval, and wrap the value to the length of the LED array
        int offset = (shift % kLength) % spacing;
        // Final value to determine if an LED should be lit. Separated from the if statement for tidyness
        bool shouldLight = (i % spacing) == offset;
        if (shouldLight)
        {
            m_ledBuffer[i].SetRGB(255, 209, 5);
        }
        else
        {
            m_ledBuffer[i].SetRGB(0, 0, 0); // this is pretty obvious
        }
    }
    updateLEDs();
}

void LEDs::displayRedWhiteAndBlue()
{

    for (int i = 0; i < kLength; i++)
    {
        double t = (double)m_LEDTimer.Get() * 0.3;
        double normalizedPosition = (double)i / (double)kLength;

        // Modulo magic, keeps it in range 0 - 1, and makes it wrap indefinitely.
        double redStart = std::fmod(t, 1.0);
        double whiteStart = std::fmod(t + 1.0 / 3.0, 1.0); 
        double blueStart = std::fmod(t + 2.0 / 3.0, 1.0);

        // Honestly this is a mess.
        // I can try to explain it briefly, but both you AND me would lose brain cells.
        // There is definitely a simpler way, but this is what I went with.

         // So uhm... This first check is just for determining if the LED is within the range for the color in the normal case.
        if (normalizedPosition > redStart && normalizedPosition <= whiteStart) {
            m_ledBuffer[i].SetRGB(255, 0, 0);
        // This check handles the case where the start of the next color in the cycle has wrapped around.
        } else if (normalizedPosition > redStart && whiteStart < redStart) {
            m_ledBuffer[i].SetRGB(255, 0, 0);
        // Repeat for each color.
        } else if (normalizedPosition > whiteStart && normalizedPosition <= blueStart) {
            m_ledBuffer[i].SetRGB(255, 255, 255);
        } else if (normalizedPosition > whiteStart && blueStart < whiteStart) {
            m_ledBuffer[i].SetRGB(255, 255, 255);
        } else if (normalizedPosition > blueStart && normalizedPosition <= redStart) {
            m_ledBuffer[i].SetRGB(0, 0, 255);
        } else if (normalizedPosition > blueStart && blueStart < redStart) {
            m_ledBuffer[i].SetRGB(0, 0, 255);
        }

    }
    updateLEDs();
}

void LEDs::setRange(int startIndex, int width, char iRed, char iGreen, char iBlue)
{
    if (startIndex < 0 || startIndex > kLength)
        return;
    if (startIndex + width >= kLength)
        width = kLength - startIndex;

    for (int i = startIndex; i < startIndex + width; i++)
    {
        m_ledBuffer[i].SetRGB(iRed, iGreen, iBlue);
    }
}

void LEDs::clear()
{
    for (int i = 0; i < kLength; i++)
    {
        m_ledBuffer[i].SetRGB(0, 0, 0);
    }
}
void LEDs::updateLEDs()
{
    m_led.SetData(m_ledBuffer); // Move the color data from the array to the LED string
}

#if 0
void LEDs::runLEDGame()
{
    clear();
    //std::cout << enemies.size() << std::endl;
    GameStage currentStage = m_gameStages[stageIndex];

    // runs every time a new enemy needs vb bn to spawn, based on the base spawn rate and stage multiplier
    if (rand() % int(1 / (baseSpawnRate * currentStage.spawnMult)) == 0)
    {
        int randomSide = rand() % 2; // 0 for beginning of LED array, 1 for end

        // for every spawn chance defined by the current stage
        for (int i = 0; i < currentStage.spawnChances.size(); i++)
        {
            int randValue = rand() % 100; // used to determine which enemytype spawns
            if (currentStage.spawnChances[i] > randValue) { // Sorted in decending order, so this should work
                addEnemy(kLength * randomSide, -1 * (randomSide * 2 - 1), currentStage.enemyTypes[i]);
                goto LOOPEXIT; // scuffed but breaks out of multiple layers
            }
        }
        LOOPEXIT: ;
    }

    // put every enemy into the led buffer for "rendering" purposes
    for (unsigned int i = 0; i < (unsigned int)enemies.size(); i++)
    {
        enemies[i].updateEnemy(currentStage.speedMult);
        int enemyRed, enemyGreen, enemyBlue;
        switch (enemies[i].type)
        {
        case EnemyType::GOLD_ENEMY:
            enemyRed = 255;
            enemyGreen = 215;
            enemyBlue = 0;
            break;
        case EnemyType::RED_ENEMY:
            enemyRed = 255;
            enemyGreen = 0;
            enemyBlue = 0;
            break;
        case EnemyType::PURPLE_ENEMY:
            enemyRed = 255;
            enemyGreen = 0;
            enemyBlue = 255;
            break;
        default:
            enemyRed = 0;
            enemyGreen = 0;
            enemyBlue = 0;
        }
        LEDs::setRange((int)(enemies[i].currentPos + 0.5f), enemies[i].size, enemyRed, enemyGreen, enemyBlue);
    }

    // delete enemies out of bounds
    for (int i = enemies.size(); i > 0; i--)
    {
        if ((enemies[i].currentPos > kLength) || (enemies[i].currentPos < -(int)enemies[i].size))
        {
            enemies.erase(enemies.begin() + i, enemies.begin() + i);
        }
    }

    updateLEDs();
}

void LEDs::addEnemy(int p_pos, int p_dir, EnemyType p_type)
{
    auto newEnemy = Enemy(p_type, p_pos);
    newEnemy.setDirection(p_dir);
    enemies.push_back(newEnemy);
}

void LEDs::nextGameStage()
{
    if (stageIndex < m_gameStages.size())
    {
        stageIndex++;
    }
}
#endif
