#pragma once

#include "Factory.h"
#include "GunC.h"

DECLARE_FACTORY(MachineGunC);

class MachineGunC final : public GunC {
  protected:
    void onShoot(TransformComponent* transform,
                 RigidbodyPC* rigidBody) override;
};