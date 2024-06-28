#include <rt/3d/geometries/model.hpp>
#include <rt/3d/geometries/triangle.hpp>

#include <numeric>
#include <sstream>

namespace rt
{

Model::Model(const std::string& obj_file_content)
    : m_vertices{}
    , m_indices{}
{
    std::istringstream obj_stream{obj_file_content};
    std::string line;
    std::vector<glm::vec3> raw_vertices;
    std::vector<Triangle> triangles;

    while (std::getline(obj_stream, line))
    {
        if (line.empty())
            continue;

        switch (std::string line_contents = line.substr(2); line[0])
        {
        case 'v': {
            const size_t first_space_loc = line_contents.find(' ');
            const size_t second_space_loc = line_contents.find(' ', first_space_loc + 1);

            float x = std::stof(line_contents.substr(0, first_space_loc));
            float y = std::stof(line_contents.substr(first_space_loc, second_space_loc));
            float z = std::stof(line_contents.substr(second_space_loc, line_contents.size()));

            raw_vertices.emplace_back(x, y, z);
            break;
        }
        case 'f': {

            const size_t first_space_loc = line_contents.find(' ');
            const size_t second_space_loc = line_contents.find(' ', first_space_loc + 1);

            const auto extract_first_value = [](const std::string& triplets) {
                if (size_t first_slash = triplets.find('/'); first_slash != std::string::npos)
                {
                    return std::stoi(triplets.substr(0, first_slash));
                }

                return std::stoi(triplets);
            };

            unsigned int p1_idx = extract_first_value(line_contents.substr(0, first_space_loc)) - 1;
            unsigned int p2_idx = extract_first_value(line_contents.substr(first_space_loc, second_space_loc)) - 1;
            unsigned int p3_idx = extract_first_value(line_contents.substr(second_space_loc, line_contents.size())) - 1;

            triangles.push_back(Triangle{{raw_vertices.at(p1_idx), raw_vertices.at(p2_idx), raw_vertices.at(p3_idx)}});
            break;
        }
        default:
            continue;
        }
    }

    for (const Triangle& triangle : triangles)
    {
        std::ranges::copy(triangle.get_vertices(), std::back_inserter(m_vertices));
    }

    m_indices.resize(m_vertices.size());
    std::iota(m_indices.begin(), m_indices.end(), 0);
}

std::span<const Vertex> Model::get_vertices() const
{
    return m_vertices;
}

std::span<const unsigned int> Model::get_indices() const
{
    return m_indices;
}

} // namespace rt