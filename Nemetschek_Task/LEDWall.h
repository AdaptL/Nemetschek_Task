#pragma once
#include "Screen.h"
#include "GenerationStrategy.h"

class LEDWall : public Screen
{
public:
    LEDWall(const Dimension& panelSize, GenerationStrategy strategy);

    void SetStrategy(GenerationStrategy* strategy);

    void GenerateWall(const Dimension& maxSizeOrRatio);

    void SetDimensions(const Dimension& other);


    ~LEDWall() override = default;
private:
    Dimension m_panelSize;
    GenerationStrategy* m_strategy;
};


