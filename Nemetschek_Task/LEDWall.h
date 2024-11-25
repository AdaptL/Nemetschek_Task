#pragma once
#include "Screen.h"
#include "GenerationStrategy.h"

class LEDWall : public Screen
{
public:
    LEDWall(const Dimension& panelSize,const Dimension& maxSizeOrRatio, 
            GenerationStrategy* strategy);

    void SetStrategy(GenerationStrategy* strategy);

    void SetDimensions(const Dimension& maxSizeOrRatio) override;

    virtual std::string ToString() const override;

    ~LEDWall() override;
private:
    Dimension*          m_panelSize;
    GenerationStrategy* m_strategy;
};


