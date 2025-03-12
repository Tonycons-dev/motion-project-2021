/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -gfxWorldview.hpp-
 *   Functionality for the drawing of the world axis and grid.
 */

#ifndef _ANIM_GFX_WORLDVIEW_
#define _ANIM_GFX_WORLDVIEW_

#include <Core/Types/BasicTypes.hpp>
#include "Engine/System/Raylib.hpp"

namespace anim::gfx {

class WorldView final
{
public:
    #define WORLDVIEW_Z_AXIS_COL 0, 255, 0
    #define WORLDVIEW_Y_AXIS_COL 0, 0, 255
    #define WORLDVIEW_X_AXIS_COL 255, 0, 0

    static void drawWorldOrigin(f32 size, f32 alpha, f32 width = 0.1f);
    static void drawWorldGrid(f32 size, f32 spacing = 1.0f);
    static void drawDebugBoundingBoxes();

    static bool isWorldOriginShown;
    static bool isWorldGridShown;

    inline static void addDebugBoundingBox(const BoundingBox& box) {
        mDebugBoundingBoxes.emplace_back(box);
    }

    inline static const std::vector<BoundingBox>& getDebugBoundingBoxes() {
        return mDebugBoundingBoxes;
    }
private:
    WorldView() = default;
    static std::vector<BoundingBox> mDebugBoundingBoxes;
};
}
#endif