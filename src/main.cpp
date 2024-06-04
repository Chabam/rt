#include <rt/3d/geometries/cube.hpp>
#include <rt/3d/geometries/plane.hpp>
#include <rt/3d/materials/blinn_phong.hpp>
#include <rt/engine/engine.hpp>
#include <rt/graphics/gl/shader.hpp>
#include <rt/graphics/gl/texture.hpp>
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

    BlinnPhong mat_red{{.m_color = {1.f, 0.f, 0.f}}};
    BlinnPhong shiny_blue{{.m_color = {0.f, 0.f, 0.75f}, .m_specular = 1.f, .m_shininess = 128}};
    BlinnPhong ground_green{{.m_color = {0.f, 0.75f, 0.f}, .m_specular = 1.f, .m_shininess = 128}};
    BlinnPhong light{{.m_emitsLight = true}};

    auto tex = std::make_shared<Texture>(FileHandler::get_file_as_image("resources/textures/smiley.ppm"));

    Scene scene;
    {
        Cube cube{0.5f, 0.5f, 0.5f, std::make_shared<BlinnPhong>(mat_red)};
        cube.set_model(glm::translate(cube.get_model(), glm::vec3(-2.f, -1.f, 0.f)));
        scene.add_mesh(std::make_shared<Cube>(cube));
    }

    {
        auto cube = std::make_shared<Cube>(1, 1, 1, std::make_shared<BlinnPhong>(shiny_blue));
        cube->set_model(glm::translate(cube->get_model(), glm::vec3(2.f, 0.f, 0.f)));
        scene.add_mesh(cube);
    }

    {
        auto ground = std::make_shared<Plane>(1, 1, std::make_shared<BlinnPhong>(ground_green), tex);
        ground->set_model(glm::translate(ground->get_model(), glm::vec3(0.f, -1.01f, 0.f)));
        ground->set_model(glm::rotate(ground->get_model(), glm::half_pi<float>(), glm::vec3(1.f, 0.f, 0.f)));
        ground->set_model(glm::scale(ground->get_model(), glm::vec3(5.f, 5.f, 5.f)));
        scene.add_mesh(ground);
    }
    {
        glm::vec3 light_position(0.f, 0.2f, 0.5f);
        auto light_indicator = std::make_shared<Cube>(1, 1, 1, std::make_shared<BlinnPhong>(light));
        light_indicator->set_model(glm::translate(light_indicator->get_model(), light_position));
        light_indicator->set_model(glm::scale(light_indicator->get_model(), glm::vec3(0.1f, 0.1f, 0.1f)));
        scene.add_mesh(light_indicator);

        scene.set_light({.m_ambient = 0.1f, .m_pos = light_position, .m_color = glm::vec3(1.f, 1.f, 1.f)});
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
