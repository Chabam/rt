#include <engine/engine.h>
#include <logger/logger.h>
#include <object/cube.h>
#include <scene/scene.h>

#include <array>
#include <memory>
#include <stdexcept>
#include <vector>

int main(void)
{
    try
    {
        Engine::init();
        Engine engine{};
        std::shared_ptr<Shader> shader =
            std::make_shared<Shader>("../../src/shaders/shader.vert", "../../src/shaders/shader.frag");

        Scene scene;
        Cube cube = Cube(2, 2, 2, shader);
        cube.applyTransformation(glm::translate(glm::mat4(1.f), glm::vec3(-2.f, 0.f, 0.f)));
        scene.addObject(&cube);

        Cube cube2 = Cube(4, 2, 2, shader, Material({0.f, 0.f, 1.f, 1.f}));
        cube2.applyTransformation(glm::translate(glm::mat4(1.f), glm::vec3(2.f, 0.f, 0.f)));
        scene.addObject(&cube2);

        engine.setScene(scene);
        engine.start();
    }
    catch (const std::runtime_error& e)
    {
        Logger::error(e.what());
        return 1;
    }

    return 0;
}
