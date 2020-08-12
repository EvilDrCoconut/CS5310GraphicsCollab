//
// Created by Evil Dr Coconut on 8/10/2020.
//


#include <GLCore.h>
#include "sandboxLayer.h"

using namespace GLCore;

class Sandbox : public Application {

public:
    Sandbox() {
        PushLayer(new SandboxLayer());
    }

};

int main() {

    std::unique_ptr<Sandbox> app = std::make_unique<Sandbox>();
    app->Run();

}
