#include "Engine/Resource/resTextResource.hpp"
#include "Engine/System/Raylib.hpp"

anim::res::TextResFactory_ anim::res::TextResFactory;

anim::res::TextResource::TextResource(const char *filepath)
{
    ASSERT_RESOURCE_FILE("TextResource: Text File", filepath)
    mResource = LoadFileText(filepath);
}