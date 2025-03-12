#include "Engine/Resource/resGraphicsResource.hpp"
#include "Engine/System/Raylib.hpp"

anim::res::ImageResFactory_ anim::res::ImageResFactory;
anim::res::TextureResFactory_ anim::res::TextureResFactory;

anim::res::ImageResource::ImageResource(const char* filepath)
{
    ASSERT_RESOURCE_FILE("ImageResource", filepath)

    auto resource = LoadImage(filepath);
    mResource = *reinterpret_cast<ResourceData*>(&resource);
}

anim::res::ImageResource::ImageResource(const char* filetype, const u8* rawData, u32 size)
{
    auto resource = LoadImageFromMemory(filetype, rawData, int(size));
    mResource = *reinterpret_cast<ResourceData*>(&resource);    
}

anim::res::ImageResource::~ImageResource()
{
    if (isResourceValid())
    UnloadImage(*reinterpret_cast<Image*>(&mResource));
}

void anim::res::ImageResource::flipVertical()
{
    if (isResourceValid())
    ImageFlipVertical(reinterpret_cast<Image*>(&mResource));
}

void anim::res::ImageResource::flipHorizontal()
{
    if (isResourceValid())
    ImageFlipHorizontal(reinterpret_cast<Image*>(&mResource));
}

void anim::res::ImageResource::resize(bool cubicInterpolation, const vec2i& newSize)
{
    if (!isResourceValid())
        return;
    if (cubicInterpolation)
        ImageResize(reinterpret_cast<Image*>(&mResource), newSize.x, newSize.y);
    else
        ImageResizeNN(reinterpret_cast<Image*>(&mResource), newSize.x, newSize.y);
}

void anim::res::ImageResource::format(s32 newFormat)
{
    if (isResourceValid())
        ImageFormat(reinterpret_cast<Image*>(&mResource), newFormat);
}

void anim::res::ImageResource::rotate(bool clockwise)
{
    if (!isResourceValid())
        return;
    if (clockwise)
        ImageRotateCW(reinterpret_cast<Image*>(&mResource));
    else
        ImageRotateCCW(reinterpret_cast<Image*>(&mResource));
}

void anim::res::ImageResource::setTint(vec4b& tint)
{
    if (isResourceValid())
    ImageColorTint(reinterpret_cast<Image*>(&mResource), *reinterpret_cast<Color*>(&tint));
}

void anim::res::ImageResource::invertColors()
{
    if (isResourceValid())
    ImageColorInvert(reinterpret_cast<Image*>(&mResource));
}

void anim::res::ImageResource::setGrayscale()
{
    if (isResourceValid())
    ImageColorGrayscale(reinterpret_cast<Image*>(&mResource));
}

void anim::res::ImageResource::setContrast(f32 contrast)
{
    if (isResourceValid())
    ImageColorContrast(reinterpret_cast<Image*>(&mResource), contrast);
}

void anim::res::ImageResource::setBrightness(u8 brightness)
{
    if (isResourceValid())
    ImageColorBrightness(reinterpret_cast<Image*>(&mResource), brightness);
}

void anim::res::ImageResource::replaceColor(vec4b& originalColor, vec4b& replaceColor)
{
    if (isResourceValid())
    ImageColorReplace(reinterpret_cast<Image*>(&mResource), 
    *reinterpret_cast<Color*>(&originalColor), *reinterpret_cast<Color*>(&replaceColor));
}

anim::res::TextureResource::TextureResource(const char* filepath)
{
    ASSERT_RESOURCE_FILE("ImageResource", filepath)

    auto resource_ = LoadImage(filepath);
    mResource = *reinterpret_cast<ResourceData*>(&resource_);
}

anim::res::TextureResource::TextureResource(ImageResource &resource)
{
    auto resource_ = LoadTextureFromImage(
        *reinterpret_cast<Image*>(&resource.resource()));

    mResource = *reinterpret_cast<ResourceData*>(&resource_);
}

anim::res::TextureResource::~TextureResource()
{
    if (isResourceValid())
        UnloadTexture(*reinterpret_cast<Texture*>(&mResource));
}