#include "glm/gtc/constants.hpp"
#include "rt/3d/scene.hpp"
#include "rt/utils/image.hpp"

#include <rt/3d/camera/camera_controller.hpp>
#include <rt/3d/geometries/cube.hpp>
#include <rt/3d/geometries/model.hpp>
#include <rt/3d/geometries/plane.hpp>
#include <rt/3d/materials/blinn_phong.hpp>
#include <rt/engine/engine.hpp>
#include <rt/graphics/gl/texture.hpp>
#include <rt/utils/file_handler.hpp>
#include <rt/utils/logger.hpp>

#include <glm/ext/matrix_transform.hpp>
#include <memory>
#include <stdexcept>

int main(void)
{
    rt::Logger logger_main{"main"};

    rt::Engine engine;

    rt::Window::init();
    rt::Window main_window{1280, 720, "rt"};
    main_window.make_active();

    rt::BlinnPhong mat_red{{.m_color = {1.f, 0.f, 0.f}}};
    rt::BlinnPhong mat_shiny_blue{{.m_color = {0.f, 0.f, 1.f}, .m_specular = 1.f, .m_shininess = 128}};
    rt::BlinnPhong mat_ground{{.m_specular = 1.f, .m_shininess = 128}};
    rt::BlinnPhong mat_light{{.m_emitsLight = true}};

    auto tex = std::make_shared<rt::Texture>(
        std::make_shared<rt::Image>(rt::FileHandler::get_file_as_image("resources/textures/brickwall.jpg")),
        std::make_shared<rt::Image>(rt::FileHandler::get_file_as_image("resources/textures/brickwall_normal.jpg")));

    auto bunny_tex = std::make_shared<rt::Texture>(
        std::make_shared<rt::Image>(rt::FileHandler::get_file_as_image("resources/textures/bunny-atlas.jpg")));

    std::shared_ptr<rt::Cube> small_cube = std::make_shared<rt::Cube>(0.5f, 0.5f, 0.5f);
    std::shared_ptr<rt::Cube> default_cube = std::make_shared<rt::Cube>();
    std::shared_ptr<rt::Plane> default_plane = std::make_shared<rt::Plane>();
    std::shared_ptr<rt::Model> bunny =
        std::make_shared<rt::Model>(rt::FileHandler::get_file_as_text("resources/models/bunny.obj"));
    std::shared_ptr<rt::Model> teapot =
        std::make_shared<rt::Model>(rt::FileHandler::get_file_as_text("resources/models/teapot.obj"));

    rt::Scene scene;
    {
        rt::Mesh teapot_mesh{teapot, std::make_shared<rt::BlinnPhong>(mat_red)};
        teapot_mesh.set_model(glm::translate(teapot_mesh.get_model(), glm::vec3(-1.f, -1.f, 0.f)));
        teapot_mesh.set_model(glm::scale(teapot_mesh.get_model(), glm::vec3(0.25f)));
        teapot_mesh.set_model(glm::rotate(teapot_mesh.get_model(), glm::quarter_pi<float>(), glm::vec3(0.f, 1.f, 0.f)));
        scene.add_mesh(std::make_shared<rt::Mesh>(std::move(teapot_mesh)));
    }

    {
        auto bunny_mesh = std::make_shared<rt::Mesh>(bunny, std::make_shared<rt::BlinnPhong>(mat_shiny_blue), bunny_tex);
        bunny_mesh->set_model(glm::translate(bunny_mesh->get_model(), glm::vec3(1.5f, -1.f, 0.f)));
        bunny_mesh->set_model(glm::scale(bunny_mesh->get_model(), glm::vec3(0.005f)));
        bunny_mesh->set_model(glm::rotate(bunny_mesh->get_model(), glm::quarter_pi<float>(), glm::vec3(0.f, 1.f, 0.f)));
        scene.add_mesh(std::move(bunny_mesh));
    }

    {
        auto ground = std::make_shared<rt::Mesh>(default_plane, std::make_shared<rt::BlinnPhong>(mat_ground), tex);
        ground->set_model(glm::translate(ground->get_model(), glm::vec3(0.f, -1.01f, 0.f)));
        ground->set_model(glm::rotate(ground->get_model(), glm::half_pi<float>(), glm::vec3(1.f, 0.f, 0.f)));
        ground->set_model(glm::scale(ground->get_model(), glm::vec3(5.f, 5.f, 5.f)));
        scene.add_mesh(ground);
    }
    {
        glm::vec3 light_position(0.f, 0.2f, 0.5f);
        auto light_indicator = std::make_shared<rt::Mesh>(default_cube, std::make_shared<rt::BlinnPhong>(mat_light));
        light_indicator->set_model(glm::translate(light_indicator->get_model(), light_position));
        light_indicator->set_model(glm::scale(light_indicator->get_model(), glm::vec3(0.1f, 0.1f, 0.1f)));
        scene.add_mesh(light_indicator);

        scene.set_light({.m_ambient = 0.05f, .m_pos = light_position, .m_color = glm::vec3(1.f, 1.f, 1.f)});
    }

    rt::CameraController camera_controller{scene.get_camera(), main_window};
    engine.register_engine_component(std::make_shared<rt::CameraController>(camera_controller));

    try
    {
        engine.render(main_window, scene);
    }
    catch (const std::runtime_error& e)
    {
        logger_main.error(e.what());
        return 1;
    }

    return 0;
}
