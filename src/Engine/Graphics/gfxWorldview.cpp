/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -gfxWorldview.cpp-
 *   Functionality for the drawing of the world axis and grid.
 */

#include "Engine/Graphics/gfxWorldview.hpp"
#include "Engine/System/GameSystem.hpp"

std::vector<BoundingBox> anim::gfx::WorldView::mDebugBoundingBoxes;
bool anim::gfx::WorldView::isWorldGridShown{false};
bool anim::gfx::WorldView::isWorldOriginShown{false};

void anim::gfx::WorldView::drawWorldOrigin(f32 size, f32 alpha, f32 width)
{
    auto axisBodyAlpha = static_cast<u8>(0xFF * alpha);
    auto axisHeadAlpha = static_cast<u8>(0x80 * alpha);

    DrawCube({0.f, 0.f, 0.f}, width, width, size, RlColor{WORLDVIEW_Z_AXIS_COL, axisBodyAlpha});
    DrawCube({0.f, 0.f, 0.f}, size, width, width, RlColor{WORLDVIEW_X_AXIS_COL, axisBodyAlpha});
    DrawCube({0.f, 0.f, 0.f}, width, size, width, RlColor{WORLDVIEW_Y_AXIS_COL, axisBodyAlpha});

    f32 head = width * 2.0f;

    DrawCube({0.f, 0.f, size}, head, head, head, RlColor{WORLDVIEW_Z_AXIS_COL, axisHeadAlpha});
    DrawCube({size, 0.f, 0.f}, head, head, head, RlColor{WORLDVIEW_X_AXIS_COL, axisHeadAlpha});
    DrawCube({0.f, size, 0.f}, head, head, head, RlColor{WORLDVIEW_Y_AXIS_COL, axisHeadAlpha});
}

void anim::gfx::WorldView::drawWorldGrid(f32 size, f32 spacing)
{
    DrawGrid(s32(size), spacing);
}

void anim::gfx::WorldView::drawDebugBoundingBoxes()
{
    if (!anim::GameSystem::instance().drawBoundingBoxes)
        return;

    for (const auto& boundingBox : mDebugBoundingBoxes)
    {
        const vec3f size(
            boundingBox.max.x - boundingBox.min.x,
            boundingBox.max.y - boundingBox.min.y,
            boundingBox.max.z - boundingBox.min.z);

        DrawCubeWires(boundingBox.max, size.x, size.y, size.z, RED);
    }
}