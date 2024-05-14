#include <rt/3d/geometries/cube.hpp>
#include <rt/3d/geometries/quadMesh.hpp>
#include <rt/engine/engine.hpp>
#include <rt/graphics/gl/shader.hpp>
#include <rt/logger/logger.hpp>
#include <rt/resource_loader/resource_loader.hpp>

#include <exception>
#include <glm/ext/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

int main(void)
{
    try
    {
        Engine::init();

        Engine engine;
        std::shared_ptr<Shader> shader =
            std::make_shared<Shader>(ResourceLoader::read_file("./resources/shaders/blinn-phong.vert").c_str(),
                                     ResourceLoader::read_file("./resources/shaders/blinn-phong.frag").c_str());
        Scene scene;
        {
            auto cube = std::make_shared<Cube>(1, 1, 1, shader, Material({1.f, 0.f, 0.f}));
            cube->applyTransformation(glm::translate(glm::mat4(1.f), glm::vec3(-1.f, 0.f, 0.f)));
            scene.addObject(cube);
        }

        {
            auto cube = std::make_shared<Cube>(1, 1, 1, shader, Material({0.f, 0.f, 0.75f}, 1.f, 128));
            cube->applyTransformation(glm::translate(glm::mat4(1.f), glm::vec3(1.f, 0.f, 0.f)));
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
            lightIndicator->applyTransformation(glm::translate(glm::mat4(1.f), ligthPosition));
            lightIndicator->applyTransformation(glm::scale(glm::mat4(1.f), glm::vec3(0.1f, 0.1f, 0.1f)));
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
