#pragma once
#include "Factory.h"
#include "GunC.h"
#include <string>

DECLARE_FACTORY(AutomaticRifleC);

class AutomaticRifleC final : public GunC {
  protected:
    void onShoot(BulletC* bullet, TransformComponent* transform,
                 RigidbodyPC* rigidBody) override;
};