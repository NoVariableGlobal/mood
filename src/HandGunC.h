#pragma once
#include "Factory.h"
#include "GunC.h"
#include <string>

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(HandGunC);

class HandGunC final : public GunC {
  protected:
    void onShoot(BulletC* bullet, TransformComponent* transform,
                 RigidbodyPC* rigidBody) override;
};
