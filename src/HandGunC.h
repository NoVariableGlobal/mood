#pragma once

#include "Factory.h"
#include "GunC.h"

// FACTORY INFRASTRUCTURE DECLARATION
DECLARE_FACTORY(HandGunC)

class HandGunC final : public GunC {
  protected:
    void onShoot(TransformComponent* transform,
                 RigidbodyPC* rigidBody) override;
};
