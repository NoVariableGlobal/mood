#pragma once
#include "EventComponent.h"
#include "Factory.h"

DECLARE_FACTORY(ExitWithEscapeEC);


class ExitWithEscapeEC : public EventComponent {
  private:
    int timeToExit = 2;
    float startTime = 0;
    bool pressing = false;

  public:
    ExitWithEscapeEC();
    ~ExitWithEscapeEC();

    virtual void setPress(bool press);
    virtual void checkEvent() override;
};