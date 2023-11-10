#include <engine/engine.h>
#include <exception>
#include <glContext/shader.h>
#include <glm/gtx/transform.hpp>
#include <glm/mat4x4.hpp>
#include <object/geometries/cube.h>
#include <object/geometries/quadMesh.h>
#include <utils/fileHelper.h>
#include <utils/logger.h>

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
            auto cube = std::make_shared<Cube>(1, 1, 1, shader, Material({1.f, 0.f, 0.f}));
            cube->applyTransformation(glm::translate(glm::vec3(-1.f, 0.f, 0.f)));
            scene.addObject(cube);
        }

        {
            auto cube = std::make_shared<Cube>(1, 1, 1, shader, Material({0.f, 0.f, 0.75f}, 1.f, 128));
            cube->applyTransformation(glm::translate(glm::vec3(1.f, 0.f, 0.f)));
            scene.addObject(cube);
        }

        {
            // clang-format off
            auto quad = std::make_shared<QuadMesh>(
                glm::vec3{ -5.f, -.51f, -5.f },
                glm::vec3{ -5.f, -.51f,  5.f },
                glm::vec3{  5.f, -.51f,  5.f },
                glm::vec3{  5.f, -.51f, -5.f },
                shader, Material({0.1f, 0.1f, 0.1f}, 1.f, 32)
            );
            // clang-format on
            scene.addObject(quad);
        }
        {
            glm::vec3 ligthPosition(0.f, 1.f, 0.75f);
            auto lightIndicator = std::make_shared<Cube>(1, 1, 1, shader, Material({1.f, 1.f, 1.f}));
            lightIndicator->applyTransformation(glm::translate(ligthPosition));
            lightIndicator->applyTransformation(glm::scale(glm::vec3(0.1f, 0.1f, 0.1f)));
            scene.addObject(lightIndicator);

            scene.setLight({.m_ambient = 0.1f, .m_pos = ligthPosition, .m_color = glm::vec3(1.f, 1.f, 1.f)});
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
