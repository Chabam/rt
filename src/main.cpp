#include "engine/engine.h"
#include "logger/logger.h"
#include "object/cube.h"
#include "object/vertice.h"

#include <array>
#include <stdexcept>
#include <vector>

int main(void)
{
    Engine engine(Shader("../../src/shaders/shader.vert", "../../src/shaders/shader.frag"));
    try
    {
        engine.init();

        std::vector<Mesh> objects = {Cube(), Cube(Material({0.f, 0.f, 1.f, 1.f}))};

        objects[0].applyTransformation(glm::translate(glm::mat4(1.f), glm::vec3(-2.f, 0.f, 0.f)));
        objects[1].applyTransformation(glm::translate(glm::mat4(1.f), glm::vec3(2.f, 0.f, 0.f)));

        engine.setMeshes(objects);
        engine.start();
    }
    catch (const std::runtime_error &e)
    {
        LOG_ERROR(e.what());
        return 1;
    }

    return 0;
}
