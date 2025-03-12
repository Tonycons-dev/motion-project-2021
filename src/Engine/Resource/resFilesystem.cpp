//
// Created by anthony on 6/6/21.
//

#include "Engine/Resource/resFilesystem.hpp"
#include <filesystem>

bool anim::res::Filesystem::pathExists(const char *filepath)
{
    std::filesystem::path file{filepath};
    return std::filesystem::exists(file);
}