#include <rt/utils/file_handler.hpp>
#include <rt/utils/logger.hpp>

#include <array>
#include <filesystem>
#include <fstream>

std::ifstream FileHandler::open_file_stream(const char* path, std::ios_base::openmode open_mode)
{
    std::filesystem::path path_object = std::filesystem::absolute(path);
    std::ifstream file{path, std::ios_base::in | open_mode};

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
    stbi_set_flip_vertically_on_load(true);
    return Image(path);
}