/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -GameSystem.cpp-
 *   The top level functionality for handling states
 */

#include "GameSystem.hpp"
#include "Engine/Graphics/gfxWorldview.hpp"


anim::GameSystem& anim::GameSystem::instance()
{
    static GameSystem engine;
    return engine;
}

bool anim::GameSystem::load(const GameSystem::InitArg& arg)
{
    mInitArg = arg;
    SetTraceLogLevel(LOG_ERROR);

    if (!constructWindow())
    {
        LOG_FAILURE("Failed to create window.");
        return false;
    }

    mCurrentState.deltaTime = 1.0f;
    mPreviousState = mCurrentState;

    MouseMgr::initialize();

    LOG_MESSAGE("Initialized engine successfully.");
    mFlags.graphicsCtxActive = true;
    return true;
}

bool anim::GameSystem::isUpdating()
{
    if (WindowShouldClose())
        return false;

    mCurrentState.deltaTime = f32(mInitArg.mFramerate) / f32(GetFPS());

    if (std::isinf(mCurrentState.deltaTime) || std::isnan(mCurrentState.deltaTime))
        mCurrentState.deltaTime = 1.0f;

    MouseMgr::update();
    BeginDrawing();

    if (mCamera3DPtr != nullptr)
        this->updateScene();
    else
        ClearBackground(BLACK);

    mCurrentState.processTime = std::clock();
    act::ActorBaseScheduler::updateProcesses(mCurrentState.processTime);

    DrawFPS(10, 10);
    EndDrawing();

    mPreviousState = mCurrentState;
    return true;
}

void anim::GameSystem::updateScene()
{
    ClearBackground(SKYBLUE);
    BeginMode3D(*mCamera3DPtr);

    mCurrentState.processTime = std::clock();
    act::ActorModelScheduler::updateProcesses(mCurrentState.processTime);

    if (gfx::WorldView::isWorldOriginShown)
        gfx::WorldView::drawWorldOrigin(5.0f, 0.5f);

    if (gfx::WorldView::isWorldGridShown)
        gfx::WorldView::drawWorldGrid(200.0f);

    if (!gfx::WorldView::getDebugBoundingBoxes().empty())
        gfx::WorldView::drawDebugBoundingBoxes();

    EndMode3D();
}

void anim::GameSystem::unload()
{
    SetCameraMode(*mCamera3DPtr, CAMERA_CUSTOM);
    act::ActorRoot::instance().endExecution();
    act::ActorRoot::instance().mChildren.clear();

    CloseWindow();
    mFlags.graphicsCtxActive = false;

    LOG_MESSAGE("Terminated engine.");
}

bool anim::GameSystem::constructWindow() const
{
    if (mInitArg.fullscreen)
    {
        auto windowWidth  = GetScreenWidth();
        auto windowHeight = GetScreenHeight();

        InitWindow(windowWidth, windowHeight, mInitArg.title);
        ToggleFullscreen();
    }
    else
    {
        auto windowWidth = int(mInitArg.mWindowSizeX);
        auto windowHeight = int(mInitArg.mWindowSizeY);

        InitWindow(windowWidth, windowHeight, mInitArg.title);
    }

    if (!IsWindowReady())
        return false;

    u32 refreshRate = GetMonitorRefreshRate(GetCurrentMonitor());

    if (mInitArg.mFramerate > refreshRate)
        SetTargetFPS(int(refreshRate));
    else
        SetTargetFPS(int(mInitArg.mFramerate));

    return true;
}

vec2i anim::GameSystem::getWindowCenter() const
{
    auto windowPosition = GetWindowPosition();

    return {s32(windowPosition.x) + s32(mInitArg.mWindowSizeX / 2),
            s32(windowPosition.y) + s32(mInitArg.mWindowSizeY / 2)};
}

void anim::GameSystem::setCameraPtr(Camera3D *cameraPtr)
{
    if (cameraPtr == nullptr)
        return;

    mCamera3DPtr = cameraPtr;
    SetCameraMode(*mCamera3DPtr, CAMERA_CUSTOM);
}

vec3f anim::GameSystem::getCameraPosition()
{
    if (mCamera3DPtr != nullptr)
        return *reinterpret_cast<vec3f*>(&mCamera3DPtr->position);

    return vec3f();
}

bool anim::Runtime::isDevWorkstation1()
{
    if (Runtime::getNumThreads() >= 16)
        return true;

    return false;
}

bool anim::Runtime::isDevWorkstation2()
{
    if (Runtime::getNumThreads() <= 8)
        return true;

    return false;
}

u32 anim::Runtime::getNumThreads()
{
    return std::thread::hardware_concurrency();
}