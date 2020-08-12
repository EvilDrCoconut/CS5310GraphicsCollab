//
// Created by Evil Dr Coconut on 8/10/2020.
//

#include "particleSystem.h"
#include "Random.h"
#include <glm/glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm/gtx/compatibility.hpp>
#include <glm/glm/ext/scalar_constants.hpp>
#include <glm/glm/ext.hpp>

ParticleSystem::ParticleSystem(){

    particlePool.resize(1000);
}

void ParticleSystem::onUpdate(GLCore::Timestep ts){
    for(auto& part: particlePool){
        if(!part.active){
            continue;
        }
        if(part.lifeRemaining <= 0.0f){
            part.active = false;
            continue;
        }

        part.lifeRemaining -= ts;
        part.position += part.velocity * (float)ts;
        part.rotation += 0.01f * ts;

    }
};

void ParticleSystem::onRender(GLCore::Utils::OrthographicCamera& camera){

    if(!quadVA){
        float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f
        };

        glCreateVertexArrays(1, &quadVA);
        glBindVertexArray(quadVA);

        GLuint quadVB, quadVC;
        glCreateBuffers(1, &quadVB);
        glBindBuffer(GL_ARRAY_BUFFER, quadVB);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexArrayAttrib(quadVB, 0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

        uint32_t indices[] = {
                0,1,2,2,3,0
        };

        glCreateBuffers(1, &quadVC);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadVC);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        particleShader = std::unique_ptr<GLCore::Utils::Shader>(GLCore::Utils::Shader::FromGLSLTextFiles("assets/shader.glsl.vert", "assets/shader.glsl.frag"));
        particleShaderViewProj = glGetUniformLocation(particleShader->GetRendererID(), "u_ViewProj");
        particleShaderTransform = glGetUniformLocation(particleShader->GetRendererID(), "u_Transform");
        particleShaderColor = glGetUniformLocation(particleShader->GetRendererID(), "u_Color");


    }

    glUseProgram(particleShader->GetRendererID());
    glUniformMatrix4fv(particleShaderViewProj, 1, GL_FALSE, glm::value_ptr(camera.GetViewProjectionMatrix()));

    for (auto& part : particlePool)
    {
        if (!part.active)
            continue;

        float life = part.lifeRemaining / part.lifeSpan;
        glm::vec4 color = glm::lerp(part.colorEnd, part.colorBegin, life);
        color.a = color.a * life;

        float size = glm::lerp(part.sizeEnd, part.sizeBegin, life);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), { part.position.x, part.position.y, 0.0f })
                              * glm::rotate(glm::mat4(1.0f), part.rotation, { 0.0f, 0.0f, 1.0f })
                              * glm::scale(glm::mat4(1.0f), { size, size, 1.0f });

        glUniformMatrix4fv(particleShaderTransform, 1, GL_FALSE,
                           reinterpret_cast<const GLfloat *>(glm::value_ptr(transform)));
        glUniform4fv(particleShaderColor, 1, reinterpret_cast<const GLfloat *>(glm::value_ptr(color)));
        glBindVertexArray(quadVA);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

}

void ParticleSystem::emit(const ParticleHousing& particleHouse) {
    Particle &part = particlePool[poolIndex];
    part.active = true;
    part.position = particleHouse.position;
    part.rotation = Random::Float() * 2.0f * glm::pi<float>();

    part.velocity = particleHouse.velocity;
    part.velocity.x = particleHouse.velocityVariation.x * (Random::Float() - 0.5f);
    part.velocity.y = particleHouse.velocityVariation.y * (Random::Float() - 0.5f);

    part.colorBegin = particleHouse.colorBegin;
    part.colorEnd = particleHouse.colorEnd;

    part.lifeSpan = particleHouse.lifeSpan;
    part.lifeRemaining = particleHouse.lifeSpan;
    part.sizeBegin = particleHouse.sizeBegin + particleHouse.sizeVariation * (Random::Float() - 0.5f);
    part.sizeEnd = particleHouse.sizeEnd;

    poolIndex = poolIndex % particlePool.size();
}
