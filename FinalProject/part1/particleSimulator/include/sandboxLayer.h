//
// Created by Evil Dr Coconut on 8/10/2020.
//

#ifndef LUKE_S_PARTICLE_SIM_SANDBOXLAYER_H
#define LUKE_S_PARTICLE_SIM_SANDBOXLAYER_H

#include "GLCore.h"
#include "GLCoreUtils.h"
#include "particleSystem.h"

class SandboxLayer : public GLCore::Layer {
public:

    SandboxLayer();

    virtual ~SandboxLayer();
    virtual void onAttach();
    virtual void onDetach();
    virtual void onEvent(GLCore::Event& event);
    virtual void onUpdate(GLCore::Timestep ts);
    virtual void onImGuiRender();

private:
    GLCore::Utils::OrthographicCameraController cameraController;
    ParticleHousing particle;
    ParticleSystem particleSystem;

};

#endif //LUKE_S_PARTICLE_SIM_SANDBOXLAYER_H
