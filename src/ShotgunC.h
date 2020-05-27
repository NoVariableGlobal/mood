#pragma once
#include "Factory.h"
#include "GunC.h"

DECLARE_FACTORY(ShotgunC)

class ShotgunC final : public GunC {
    // Number of pellets each shot fires
    int nPellets_ = 0;

    // Distance in angles between each pellet
    int dispersionAngle_ = 0;

  protected:
    void onPreShoot() override;
    void onShoot(TransformComponent* transform,
                 RigidbodyPC* rigidBody) override;

  public:
    void setNPellets(int n);
    void setDispersion(int n);
};
