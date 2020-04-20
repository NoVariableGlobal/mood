#pragma once

#include "Factory.h"
#include "GunC.h"

DECLARE_FACTORY(ShotgunC);
class ShotgunC final : public GunC {
  private:
    // Number of pellets each shot fires
    int nPellets;

    // Distance in angles between each pellet
    int dispAngle;

  protected:
    void onPreShoot() override;
    void onShoot(TransformComponent* transform,
                 RigidbodyPC* rigidBody) override;

  public:
    void setNPellets(int n);
    void setDispersion(int n);
};