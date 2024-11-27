#pragma once
#include "Screen.h"
#include "GenerationStrategy.h"

class LEDWall : public Screen
{
public:
    LEDWall(const Dimension& panelSize,const Dimension& maxSizeOrRatio, 
            GenerationStrategy* strategy);

    LEDWall(const LEDWall& other);
    LEDWall(LEDWall&& other) noexcept;
    LEDWall& operator=(const LEDWall& other);
    LEDWall& operator=(LEDWall&& other) noexcept;

    void SetStrategy(GenerationStrategy* strategy);

    void SetDimensions(const Dimension& maxSizeOrRatio) override;

    virtual std::string ToString() const override;

    ~LEDWall() override;
private:
    Dimension*          m_panelSize;
    GenerationStrategy* m_strategy;
    unsigned rows;
    unsigned columns;
};


