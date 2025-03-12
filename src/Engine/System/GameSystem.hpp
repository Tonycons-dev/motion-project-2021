/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -GameSystem.hpp-
 *   The top level functionality for handling states
 */

#pragma once
#include "Engine/System/Runtime.hpp"
#include "Engine/Actor/actRootActor.hpp"
#include "Engine/System/MouseMgr.hpp"

namespace anim {

class GameSystem final
{
public:
    struct InitArg
    {
        const char* title;

        u32 mWindowSizeX;
        u32 mWindowSizeY;
        u32 mFramerate;

        bool fullscreen;
    };

    struct State
    {
        f32 deltaTime;
        s64 processTime;
    };

    struct Flags
    {
        bool graphicsCtxActive : 1;
        bool drawBoundingBoxes : 1;
        bool drawWireframe : 1;
    };

    static GameSystem& instance();

    GameSystem(const GameSystem&) = delete;
    GameSystem(const GameSystem&&) = delete;

    bool load(const InitArg& arg);
    bool isUpdating();
    void unload();

    void setCameraPtr(Camera3D* cameraPtr);

    vec2i getWindowCenter() const;
    vec3f getCameraPosition();

    inline State& getState() {
        return mCurrentState;
    }

    [[nodiscard]] inline vec2u getWindowSize() const noexcept
    {    return vec2u(mInitArg.mWindowSizeX, mInitArg.mWindowSizeY); }

    [[nodiscard]] inline f32 getDeltaTime() const noexcept
        { return mCurrentState.deltaTime; }

    Flags mFlags{ false, false, false };
private:
    GameSystem() = default;
    Camera3D* mCamera3DPtr{};

    InitArg mInitArg{};
    State mCurrentState{};
    State mPreviousState{};

    bool constructWindow() const;
    void updateScene();
};
}