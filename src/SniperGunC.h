#pragma once

#include "Factory.h"
#include "GunC.h"

DECLARE_FACTORY(SniperGunC);
class SniperGunC final : public GunC {
  protected:
    void onShoot(TransformComponent* transform,
                 RigidbodyPC* rigidBody) override;
};
