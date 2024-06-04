#include <rt/utils/file_handler.hpp>
#include <rt/utils/logger.hpp>

#include <filesystem>
#include <fstream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

std::ifstream FileHandler::open_file_stream(const char* path, std::ios_base::openmode open_mode)
{
    std::filesystem::path path_object = std::filesystem::absolute(path);
    std::ifstream file = std::ifstream(path);

    if (!file.is_open())
    {
        std::string path_object_string = path_object.string();
        throw std::runtime_error(std::vformat("File not found: {}", std::make_format_args(path_object_string)));
    }

    return file;
}

std::string FileHandler::get_file_as_text(const char* path)
{
    std::ifstream file = open_file_stream(path);

    std::stringstream out;
    out << file.rdbuf();

    return out.str();
}

Image FileHandler::get_file_as_image(const char* path)
{
    std::ifstream file = open_file_stream(path, std::ios_base::binary);

    // Skipping the format indicator
    std::string str_read;

    std::getline(file, str_read);

    if (str_read[0] != 'P' || !std::isdigit(str_read[1]))
    {
        throw std::runtime_error("Only PPM file format is supported for the moment!");
    }

    // Only supporting PPM with full RGB
    const unsigned char version = str_read[1];

    Image out_img;
    std::string size_value;
    std::getline(file, size_value, ' ');
    out_img.m_width = std::stoi(size_value);

    std::getline(file, size_value);
    out_img.m_height = std::stoi(size_value);

    if (version > 4)
    {
        // skipping channel size, assuming 255
        std::getline(file, size_value);
    }

    const size_t total_pixels = out_img.m_width * out_img.m_height;
    out_img.m_pixels.reserve(total_pixels);

    for (size_t i = 0; i < total_pixels; ++i)
    {
        out_img.m_pixels.push_back(file.get());
        out_img.m_pixels.push_back(file.get());
        out_img.m_pixels.push_back(file.get());
    }

    file.get();
    if (!file.eof())
    {
        throw std::runtime_error("File should have been read!");
    }

    return out_img;
}