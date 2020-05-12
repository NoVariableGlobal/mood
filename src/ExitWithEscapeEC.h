#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(ExitWithEscapeEC);

class GuiLabelComponent;

class ExitWithEscapeEC : public EventComponent {
  private:
    int timeToExit = 2;
    float startTime = 0;
    bool pressing = false;
    bool out = false;

    GuiLabelComponent* label;

  public:
    ExitWithEscapeEC();
    ~ExitWithEscapeEC();

    void setPress(bool press);
    void setAlpha();
    virtual void checkEvent() override;
};