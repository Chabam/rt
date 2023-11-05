#include <engine/engine.h>
#include <object/cube.h>
#include <glContext/shader.h>
#include <utils/fileHelper.h>
#include <utils/logger.h>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <exception>

int main(void)
{
    try
    {
        Engine::init();

        Engine engine;
        std::shared_ptr<Shader> shader =
            std::make_shared<Shader>(FileHelper::readFromFile("../../src/shaders/shader.vert").c_str(),
                                     FileHelper::readFromFile("../../src/shaders/shader.frag").c_str());

        Scene scene;
        {
            auto cube = std::make_shared<Cube>(2, 2, 2, shader);
            cube->applyTransformation(glm::translate(glm::mat4(1.f), glm::vec3(-2.f, 0.f, 0.f)));
            scene.addObject(cube);
        }

        {
            auto cube = std::make_shared<Cube>(4, 2, 2, shader, Material({0.f, 0.f, 1.f, 1.f}));
            cube->applyTransformation(glm::translate(glm::mat4(1.f), glm::vec3(2.f, 0.f, 0.f)));
            scene.addObject(cube);
        }

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
