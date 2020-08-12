//
// Created by Evil Dr Coconut on 8/10/2020.
//

#pragma once

#ifndef LUKE_S_PARTICLE_SIM_PARTICLESYSTEM_H
#define LUKE_S_PARTICLE_SIM_PARTICLESYSTEM_H

#include "GLCore.h"
#include "GLCoreUtils.h"
#include "glm/glm/glm.hpp"
#include "Glad/include/glad/glad.h"
#include <bits/unique_ptr.h>
#include <vector>

struct ParticleHousing{

    glm::vec2 position;
    glm::vec2 velocity, velocityVariation;
    glm::vec4 colorBegin, colorEnd;
    float sizeBegin, sizeEnd, sizeVariation;
    float lifeSpan = 1.0f;
};


class ParticleSystem{

public:
    ParticleSystem();

    void onUpdate(GLCore::Timestep ts);
    void onRender(GLCore::Utils::OrthographicCamera& camera);
    void emit(const ParticleHousing& particleHousing);

private:
    struct Particle{

        glm::vec2 position;
        glm::vec2 velocity;
        glm::vec4 colorBegin, colorEnd;
        float rotation = 0.0f;
        float sizeBegin, sizeEnd;
        float lifeSpan = 1.0f;
        float lifeRemaining = 0.0f;
        bool active = false;
    };

    std::vector<Particle> particlePool;
    uint32_t poolIndex = 999;

    GLuint quadVA = 0;
    std::unique_ptr<GLCore::Utils::Shader> particleShader;
    GLuint particleShaderViewProj{}, particleShaderTransform{}, particleShaderColor{};

};




#endif //LUKE_S_PARTICLE_SIM_PARTICLESYSTEM_H
