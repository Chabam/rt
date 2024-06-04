#include <rt/utils/file_handler.hpp>
#include <rt/utils/logger.hpp>

#include <filesystem>
#include <fstream>

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

    while (file.peek() == '#')
        std::getline(file, str_read);

    // Only supporting PPM with full RGB
    const unsigned char version = str_read[1];

    Image out_img;
    std::getline(file, str_read, ' ');
    out_img.m_width = std::stoull(str_read);

    std::getline(file, str_read);
    out_img.m_height = std::stoull(str_read);

    unsigned char max_value = 1;

    if (version > 4)
    {
        std::getline(file, str_read);
        max_value = std::stoi(str_read);
    }

    const size_t total_pixels = out_img.m_width * out_img.m_height;
    out_img.m_pixels.reserve(total_pixels);

    char c;
    while (file >> c)
    {
        char r = c;
        file >> c;
        char g = c;
        file >> c;
        char b = c;
        out_img.m_pixels.emplace_back(r, g, b);
    }

    return out_img;
}