//
// Created by Evil Dr Coconut on 8/10/2020.
//

#include "sandboxLayer.h"
#include <imgui/imgui.h>
#include <glm/glm/ext.hpp>

using namespace GLCore;

SandboxLayer::SandboxLayer() : cameraController(16.0f / 9.0f){

}

SandboxLayer::~SandboxLayer() {

}

void SandboxLayer::onAttach() {

    GLCore::Utils::EnableGLDebugging();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    particle.colorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
    particle.colorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
    particle.sizeBegin = 0.5f, particle.sizeVariation = 0.3f, particle.sizeEnd = 0.0f;
    particle.lifeSpan = 1.0f;
    particle.velocity = { 0.0f, 0.0f };
    particle.velocityVariation = { 3.0f, 1.0f };
    particle.position = { 0.0f, 0.0f };
}

void SandboxLayer::onDetach() {

}

void SandboxLayer::onEvent(Event& event) {
    cameraController.OnEvent(event);

    if (event.GetEventType() == EventType::WindowResize)
    {
        WindowResizeEvent& e = (WindowResizeEvent&)event;
        glViewport(0, 0, e.GetWidth(), e.GetHeight());
    }
}

void SandboxLayer::onUpdate(Timestep ts) {

    cameraController.OnUpdate(ts);

    //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClearColor(0,0,0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float x; 
    float y;

    if (GLCore::Input::IsMouseButtonPressed(HZ_MOUSE_BUTTON_LEFT))
    {
        auto [x, y] = Input{}::GetMousePosition();
        auto width = GLCore::Application::Get().GetWindow().GetWidth();
        auto height = GLCore::Application::Get().GetWindow().GetHeight();

        auto bounds = cameraController.GetBounds();
        auto pos = cameraController.GetCamera().GetPosition();
        x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
        y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
        particle.position = { x + pos.x, y + pos.y };
        for (int i = 0; i < 5; i++)
            particleSystem.emit(particle);
    }

    particleSystem.onUpdate(ts);
    particleSystem.onRender(cameraController.GetCamera());
}

void SandboxLayer::onImGuiRender() {

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Birth Color", glm::value_ptr(particle.colorBegin));
    ImGui::ColorEdit4("Death Color", glm::value_ptr(particle.colorEnd));
    ImGui::DragFloat("Life Time", &particle.lifeSpan, 0.1f, 0.0f, 1000.0f);
    ImGui::End();
}
