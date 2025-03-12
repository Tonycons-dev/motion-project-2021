#pragma once
#include "Engine/Resource/resResourceBase.hpp"

namespace anim::res
{

struct ImageResource
{
private:
    struct ResourceData
    {
        void *data;
        int width, height;
        int mipmaps, format;
    };
    RESOURCE_IMPL(ResourceData)
public:
    explicit ImageResource(const char* filepath);
    explicit ImageResource(const char* filetype, const u8* rawData, u32 size);

    ~ImageResource();

    void flipVertical();
    void flipHorizontal();

    void resize(bool cubicInterpolation, const vec2i& newSize);
    void format(s32 newFormat);

    void rotate(bool clockwise);
    void setTint(vec4b& tint);

    void invertColors();
    void setGrayscale();

    void setContrast(f32 contrast);
    void setBrightness(u8 brightness);

    void replaceColor(vec4b& originalColor, vec4b& replaceColor);
};

class TextureResource
{
private:
    struct ResourceData
    {
        unsigned int id;
        int width, height;
        int mipmaps, format;
    };
    RESOURCE_IMPL(ResourceData)
public:
    explicit TextureResource(const char* filepath);
    explicit TextureResource(ImageResource& resource);

    ~TextureResource();
};

class ImageResFactory_ : public ResourceFactory
     <ImageResource, ResourceLoader<ImageResource>>{};

class TextureResFactory_ : public ResourceFactory
     <TextureResource, ResourceLoader<TextureResource>>{};

extern ImageResFactory_ ImageResFactory;
extern TextureResFactory_ TextureResFactory;
}