#include <rt/3d/geometries/model.hpp>
#include <rt/3d/geometries/triangle.hpp>

#include <algorithm>
#include <numeric>
#include <sstream>
#include <string>

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
    std::vector<glm::vec2> uvs;

    while (std::getline(obj_stream, line))
    {
        if (line.empty())
            continue;

        switch (std::string line_contents = line.substr(line.find(' ') + 1); line[0])
        {
        case 'v': {
            const size_t first_space_loc = line_contents.find(' ');
            switch (line[1])
            {
            case ' ': {
                const size_t second_space_loc = line_contents.find(' ', first_space_loc + 1);

                float x = std::stof(line_contents.substr(0, first_space_loc));
                float y = std::stof(line_contents.substr(first_space_loc, second_space_loc - first_space_loc));
                float z = std::stof(line_contents.substr(second_space_loc));

                raw_vertices.emplace_back(x, y, z);
                break;
            }
            case 't': {
                float u = std::stof(line_contents.substr(0, first_space_loc));
                float v = std::stof(line_contents.substr(first_space_loc));

                uvs.emplace_back(u, v);
            }
            default:
                continue;
            }
            break;
        }
        case 'f': {
            const size_t first_space_loc = line_contents.find(' ');
            const size_t second_space_loc = line_contents.find(' ', first_space_loc + 1);

            const size_t slash_count = std::count(line_contents.begin(), line_contents.end(), '/') / 3;

            if (slash_count != 0)
            {
                const auto extract_values =
                    [slash_count](const std::string& triplets) -> std::tuple<unsigned int, unsigned int> {
                    size_t first_slash = triplets.find('/');
                    size_t last_slash = triplets.rfind('/');

                    if (slash_count == 2)
                    {
                        return std::make_tuple(std::stoi(triplets.substr(0, first_slash)) - 1,
                                               std::stoi(triplets.substr(first_slash + 1, last_slash)) - 1);
                    }

                    return std::make_tuple(std::stoi(triplets.substr(0, first_slash)) - 1,
                                           std::stoi(triplets.substr(last_slash - 1)) - 1);
                };

                const auto [p1_idx, p1_uv] = extract_values(line_contents.substr(0, first_space_loc));
                const auto [p2_idx, p2_uv] =
                    extract_values(line_contents.substr(first_space_loc, second_space_loc - first_space_loc));
                const auto [p3_idx, p3_uv] = extract_values(line_contents.substr(second_space_loc));

                triangles.push_back(
                    Triangle{{raw_vertices.at(p1_idx), raw_vertices.at(p2_idx), raw_vertices.at(p3_idx)},
                             {uvs.at(p1_uv), uvs.at(p2_uv), uvs.at(p3_uv)}});
            }
            else
            {

                const unsigned int p1_idx = std::stoi(line_contents.substr(0, first_space_loc)) - 1;
                const unsigned int p2_idx =
                    std::stoi(line_contents.substr(first_space_loc, second_space_loc - first_space_loc)) - 1;
                const unsigned int p3_idx = std::stoi(line_contents.substr(second_space_loc)) - 1;

                triangles.push_back(
                    Triangle{{raw_vertices.at(p1_idx), raw_vertices.at(p2_idx), raw_vertices.at(p3_idx)}});
            }

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
