#pragma once

#include "Factory.h"
#include "GunC.h"

DECLARE_FACTORY(AutomaticRifleC)

class AutomaticRifleC final : public GunC {
  protected:
    void onShoot(TransformComponent* transform,
                 RigidbodyPC* rigidBody) override;
};