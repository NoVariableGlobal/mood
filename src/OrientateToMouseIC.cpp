#include "OrientateToMouseIC.h"
#include "ComponentsManager.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "OgreSDLContext.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TridimensionalObjectRC.h"

#include "OgreRoot.h"

#include <SDL.h>
#include <cstdlib>
#include <math.h>
#include <stdlib.h>

#include <iostream>

void OrientateToMouseIC::handleInput(const SDL_Event& _event) {
    // Get mouse position
    int xMouse, yMouse;
    SDL_GetGlobalMouseState(&xMouse, &yMouse);

    // Get window position
    SDL_Window* win = OgreSDLContext::getInstance()->getSDLWindow();
    int xWindow, yWindow;
    SDL_GetWindowPosition(win, &xWindow, &yWindow);
    xMouse -= xWindow;
    yMouse -= yWindow;

    // Get window size
    int xWinSize, yWinSize;
    SDL_GetWindowSize(win, &xWinSize, &yWinSize);

    // Adjust limits
    if (xMouse < 0)
        xMouse = 0;
    if (yMouse < 0)
        yMouse = 0;
    if (xMouse > xWinSize)
        xMouse = xWinSize;
    if (yMouse > yWinSize)
        yMouse = yWinSize;

    // Calculate angle between mouse and father
    float angleInRad =
        atan2((yWinSize / 2.0f) + 28.0f - yMouse, xWinSize / 2.0f - xMouse);
    float angleInDeg = -angleInRad * 180 / M_PI;

    // Make the rotation
    TridimensionalObjectRC* fatherRender =
        dynamic_cast<TridimensionalObjectRC*>(
            father_->getComponent("TridimensionalObjectRC"));
    fatherRender->setRotation(Ogre::Vector3(0, angleInDeg - 90, 0));
}

// FACTORY INFRASTRUCTURE

OrientateToMouseICFactory::OrientateToMouseICFactory() = default;

Component* OrientateToMouseICFactory::create(Entity* _father,
                                             Json::Value& _data, Scene* scene) {
    // Create the component
    OrientateToMouseIC* orientationIC = new OrientateToMouseIC();
    scene->getComponentsManager()->addIC(orientationIC);

    // Set the component's father as the entity it was instanced for
    orientationIC->setFather(_father);
    orientationIC->setScene(scene);

    return orientationIC;
};

DEFINE_FACTORY(OrientateToMouseIC);
