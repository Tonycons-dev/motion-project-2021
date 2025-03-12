#pragma once

#include "Engine/Resource/resResourceBase.hpp"

namespace anim::res {

class TextResource
{
private:
    RESOURCE_IMPL(std::string)
public:
    explicit TextResource(const char* filepath);
};

class TextResFactory_ : public ResourceFactory
    <TextResource, ResourceLoader<TextResource>>{};

extern TextResFactory_ TextResFactory;
}