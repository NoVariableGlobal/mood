#pragma once
#include "Factory.h"
#include "GunC.h"
#include <string>

DECLARE_FACTORY(ShotgunC);
class ShotgunC : public GunC {
  private:
    // Number of pellets each shot fires
    int nPellets;

    // Distance in angles between each pellet
    int dispAngle;

  public:
    ShotgunC();
    ~ShotgunC();

    virtual void destroy();
    virtual bool shoot();

    void setNPellets(int n);
    void setDispersion(int n);
};