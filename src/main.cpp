#include <rt/3d/geometries/cube.hpp>
#include <rt/3d/geometries/plane.hpp>
#include <rt/3d/materials/blinn_phong.hpp>
#include <rt/engine/engine.hpp>
#include <rt/graphics/gl/shader.hpp>
#include <rt/utils/file_handler.hpp>
#include <rt/utils/logger.hpp>

#include <exception>
#include <glm/ext/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

int main(void)
{
    Logger logger_main{"main"};

    Engine engine;

    engine.create_window(1280, 720, "rt");

    BlinnPhong matRed{{.m_color = {1.f, 0.f, 0.f}}};
    BlinnPhong shinyBlue{{.m_color = {0.f, 0.f, 0.75f}, .m_specular = 1.f, .m_shininess = 128}};
    BlinnPhong groundGreen{{.m_color = {0.f, 0.75f, 0.f}, .m_specular = 1.f, .m_shininess = 128}};
    BlinnPhong light{{.m_emitsLight = true}};

    Scene scene;
    {
        Cube cube{0.5f, 0.5f, 0.5f, std::make_shared<BlinnPhong>(matRed)};
        cube.set_model(glm::translate(cube.get_model(), glm::vec3(-2.f, -1.f, 0.f)));
        scene.add_mesh(std::make_shared<Cube>(cube));
    }

    {
        auto cube = std::make_shared<Cube>(1, 1, 1, std::make_shared<BlinnPhong>(shinyBlue));
        cube->set_model(glm::translate(cube->get_model(), glm::vec3(2.f, 0.f, 0.f)));
        scene.add_mesh(cube);
    }

    {
        auto ground = std::make_shared<Plane>(1, 1, std::make_shared<BlinnPhong>(groundGreen));
        ground->set_model(glm::translate(ground->get_model(), glm::vec3(0.f, -1.01f, 0.f)));
        ground->set_model(glm::rotate(ground->get_model(), glm::half_pi<float>(), glm::vec3(1.f, 0.f, 0.f)));
        ground->set_model(glm::scale(ground->get_model(), glm::vec3(5.f, 5.f, 5.f)));
        scene.add_mesh(ground);
    }
    {
        glm::vec3 ligthPosition(0.f, 0.2f, 0.5f);
        auto lightIndicator = std::make_shared<Cube>(1, 1, 1, std::make_shared<BlinnPhong>(light));
        lightIndicator->set_model(glm::translate(lightIndicator->get_model(), ligthPosition));
        lightIndicator->set_model(glm::scale(lightIndicator->get_model(), glm::vec3(0.1f, 0.1f, 0.1f)));
        scene.add_mesh(lightIndicator);

        scene.set_light({.m_ambient = 0.1f, .m_pos = ligthPosition, .m_color = glm::vec3(1.f, 1.f, 1.f)});
    }

    engine.set_scene(scene);

    try
    {
        engine.start();
    }
    catch (const std::runtime_error& e)
    {
        logger_main.error(e.what());
        return 1;
    }

    return 0;
}
