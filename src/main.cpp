#include <rt/3d/geometries/cube.hpp>
#include <rt/3d/geometries/plane.hpp>
#include <rt/3d/materials/blinnPhong.hpp>
#include <rt/engine/engine.hpp>
#include <rt/graphics/gl/shader.hpp>
#include <rt/logger/logger.hpp>
#include <rt/resourceLoader/resourceLoader.hpp>

#include <exception>
#include <glm/ext/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

int main(void)
{
    try
    {
        Engine::init();

        Engine engine;
        BlinnPhong matRed{{.m_color = {1.f, 0.f, 0.f}}};
        BlinnPhong shinyBlue{{.m_color = {0.f, 0.f, 0.75f}, .m_specular = 1.f, .m_shininess = 128}};
        BlinnPhong groundGreen{{.m_color = {0.f, 0.75f, 0.f}, .m_specular = 1.f, .m_shininess = 128}};
        BlinnPhong light{{.m_emitsLight = true}};

        Scene scene;
        {
            auto cube = std::make_shared<Cube>(0.5f, 0.5f, 0.5f, matRed);
            cube->setModel(glm::translate(cube->getModel(), glm::vec3(-2.f, -1.f, 0.f)));
            scene.addMesh(cube);
        }

        {
            auto cube = std::make_shared<Cube>(1, 1, 1, shinyBlue);
            cube->setModel(glm::translate(cube->getModel(), glm::vec3(2.f, 0.f, 0.f)));
            scene.addMesh(cube);
        }

        {
            auto ground = std::make_shared<Plane>(1, 1, groundGreen);
            ground->setModel(glm::translate(ground->getModel(), glm::vec3(0.f, -1.01f, 0.f)));
            ground->setModel(glm::rotate(ground->getModel(), glm::half_pi<float>(), glm::vec3(1.f, 0.f, 0.f)));
            ground->setModel(glm::scale(ground->getModel(), glm::vec3(5.f, 5.f, 5.f)));
            scene.addMesh(ground);
        }
        {
            glm::vec3 ligthPosition(0.f, 0.2f, 0.5f);
            auto lightIndicator = std::make_shared<Cube>(1, 1, 1, light);
            lightIndicator->setModel(glm::translate(lightIndicator->getModel(), ligthPosition));
            lightIndicator->setModel(glm::scale(lightIndicator->getModel(), glm::vec3(0.1f, 0.1f, 0.1f)));
            scene.addMesh(lightIndicator);

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
