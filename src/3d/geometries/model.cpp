#include <rt/3d/geometries/model.hpp>
#include <rt/3d/geometries/triangle.hpp>

#include <numeric>
#include <regex>
#include <sstream>

namespace rt
{

Model::Model(const std::string& obj_file_content)
    : m_vertices{}
    , m_indices{}
{
    std::istringstream obj_stream{obj_file_content};
    const std::regex obj_line_regex{R"((v|f)(?: ([0-9-\.]+))(?: ([0-9-\.]+))(?: ([0-9-\.]+))(?: ([0-9-\.]+))?)"};
    std::string line;
    std::vector<glm::vec3> raw_vertices;
    std::vector<Triangle> triangles;

    while (std::getline(obj_stream, line))
    {
        std::smatch matches;
        if (!std::regex_match(line, matches, obj_line_regex))
            continue;

        const std::string& line_type = matches[1];

        if (line_type == "v")
        {
            raw_vertices.emplace_back(std::stof(matches[2]), std::stof(matches[3]), std::stof(matches[4]));
        }
        else if (line_type == "f")
        {
            triangles.emplace_back(std::array<glm::vec3, Triangle::POINT_COUNT>{
                raw_vertices.at(std::stoi(matches[2]) - 1), raw_vertices.at(std::stoi(matches[3]) - 1),
                raw_vertices.at(std::stoi(matches[4]) - 1)});
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

std::span<const unsigned short> Model::get_indices() const
{
    return m_indices;
}

} // namespace rt