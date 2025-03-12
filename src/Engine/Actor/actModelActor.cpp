/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actModelActor.hpp-
 *   Implementation of the ActorModel class.
 */

#include "Engine/Actor/actBaseActor.hpp"
#include "Engine/Actor/actModelProcess.hpp"
#include "Engine/System/Raymath.hpp"
#include "Engine/Resource/resModelResource.hpp"

void anim::act::ActorModel::onRender() {}


anim::act::ActorModel::ActorModel()
    :
    mFillColor((u8)0xff),
    mDirection(0.0f),
    mRotation(0.0f),
    mPosition(0.0f),
    mVelocity(0.0f),
    mBoundingBoxSize(1.0f),
    mScale(1.0f)
{}

anim::act::ActorModel::ActorModel(vec3f position)
    :
    mFillColor((u8)0xff),
    mDirection(0.0f),
    mRotation(0.0f),
    mPosition(position),
    mVelocity(0.0f),
    mBoundingBoxSize(1.0f),
    mScale(1.0f)
{
    translate(position);
}

anim::act::ActorModel::ActorModel(vec3f position, vec3f rotation)
    :
    mFillColor((u8)0xff),
    mDirection(0.0f),
    mRotation(rotation),
    mPosition(position),
    mVelocity(0.0f),
    mBoundingBoxSize(1.0f),
    mScale(1.0f)
{
    translate(position);
    rotateOnXYZ(rotation);
}

anim::act::ActorModel::ActorModel(vec3f position, vec3f rotation, f32 scale, bool wires)
    :
    mFillColor((u8)0xff),
    mDirection(0.0f),
    mRotation(rotation),
    mPosition(position),
    mVelocity(0.0f),
    mBoundingBoxSize(scale),
    mScale(scale)
{
    translate(position);
    rotateOnXYZ(rotation);
    setWireframeVisible(wires);
}

BoundingBox anim::act::ActorModel::getBoundingBox() const noexcept
{
    return BoundingBox {
        Vector3{
        mPosition.x - mBoundingBoxSize.x / 2.f,
        mPosition.y - mBoundingBoxSize.y / 2.f,
        mPosition.z - mBoundingBoxSize.z / 2.f},
        Vector3{
        mPosition.x + mBoundingBoxSize.x / 2.f,
        mPosition.y + mBoundingBoxSize.y / 2.f,
        mPosition.z + mBoundingBoxSize.z / 2.f}
    };
}

bool anim::act::ActorModel::createModelResource(u32 id, const char* filepath)
{
    checkModelResourceExists(id);
    auto handle = res::ModelResFactory.load(id, filepath);

    return checkModelResourceHandle(id, handle);
}

void anim::act::ActorModel::unloadModelResource(u32 id)
{
    if (!res::ModelResFactory.contains(id))
        return;

    res::ModelResFactory.unload(id);
}

bool anim::act::ActorModel::createModelResourceCylinder(u32 id, f32 radius, f32 height, s32 slices)
{
    checkModelResourceExists(id);
    auto model_ = LoadModelFromMesh(GenMeshCylinder(radius, height, slices));
    auto handle = res::ModelResFactory.load(id, model_);

    handle->mDimensions = vec3f(radius * 2.f);
    return checkModelResourceHandle(id, handle);
}

bool anim::act::ActorModel::createModelResourceTorus(u32 id, f32 radius, f32 size, s32 radSeg, s32 sides)
{
    checkModelResourceExists(id);
    auto model_ = LoadModelFromMesh(GenMeshTorus(radius, size, radSeg, sides));
    auto handle = res::ModelResFactory.load(id, model_);

    handle->mDimensions = vec3f(radius * 2.f);
    return checkModelResourceHandle(id, handle);
}

bool anim::act::ActorModel::createModelResourceRectPrism(u32 id, const vec3f &dimensions)
{
    checkModelResourceExists(id);
    auto model_ = LoadModelFromMesh(GenMeshCube(dimensions.x, dimensions.y, dimensions.z));
    auto handle = res::ModelResFactory.load(id, model_);

    handle->mDimensions = dimensions;
    return checkModelResourceHandle(id, handle);
}

void anim::act::ActorModel::checkModelResourceExists(u32 id)
{
    if (res::ModelResFactory.contains(id))
        res::ModelResFactory.unload(id);
}

bool anim::act::ActorModel::checkModelResourceHandle(u32 id, const ModelResourceHandle &handle)
{
    if (!handle->isResourceValid()) {
        res::ModelResFactory.unload(id);
        return false;
    }
    return true;
}

bool anim::act::ActorModel::setModelResource(u32 id)
{
    if (!res::ModelResFactory.contains(id))
        return false;

    auto handle = res::ModelResFactory.handle(id);

    if (!handle->isResourceValid())
        return false;

    this->removeModel();

    mRenderFlags.isModelActive = true;
    mRenderFlags.isModelGlobalResource = true;

    mModel = handle->const_resource();
    return true;
}

void anim::act::ActorModel::removeModel()
{
    if (mRenderFlags.isModelActive)
    {
        if (!mRenderFlags.isModelGlobalResource)
            UnloadModel(mModel);

        mRenderFlags.isModelActive = false;
    }
}

void anim::act::ActorModel::generateModelCylinder(f32 radius, f32 height, s32 slices)
{
    setBoundingBoxSize(vec3f(radius * 2.f));
    mModel = LoadModelFromMesh(GenMeshCylinder(radius, height, slices));
    mRenderFlags.isModelActive = true;
    mRenderFlags.isModelGlobalResource = false;
}

void anim::act::ActorModel::generateModelTorus(f32 radius, f32 size, s32 radSeg, s32 sides)
{
    setBoundingBoxSize(vec3f(radius * 2.f));
    mModel = LoadModelFromMesh(GenMeshTorus(radius, size, radSeg, sides));
    mRenderFlags.isModelActive = true;
    mRenderFlags.isModelGlobalResource = false;
}

void anim::act::ActorModel::generateModelRectPrism(const vec3f &dimensions)
{
    setBoundingBoxSize(dimensions);
    mModel = LoadModelFromMesh(GenMeshCube(dimensions.x, dimensions.y, dimensions.z));
    mRenderFlags.isModelActive = true;
    mRenderFlags.isModelGlobalResource = false;
}

void anim::act::ActorModel::translate(const vec3f& position)
{
    mPosition = position;
    mModel.transform = MatrixTranslate(position.x, position.y, position.z);
}

void anim::act::ActorModel::rotateOnXYZ(const vec3f& angles)
{
    mRotation = angles;
    mModel.transform = MatrixRotateXYZ(*(Vector3*)(&mRotation));
}

void anim::act::ActorModel::rotateXAxis(f32 angle)
{
    mRotation.x = angle;
    this->rotateOnXYZ(mRotation);
}

void anim::act::ActorModel::rotateYAxis(f32 angle)
{
    mRotation.y = angle;
    this->rotateOnXYZ(mRotation);
}

void anim::act::ActorModel::rotateZAxis(f32 angle)
{
    mRotation.z = angle;
    this->rotateOnXYZ(mRotation);
}

void anim::act::ActorModel::setWireframeVisible(bool wireframe) noexcept {
    mRenderFlags.wireframeVisible = wireframe;
}

void anim::act::ActorModel::setBoundingBoxVisible(bool visible) noexcept {
    mRenderFlags.boundingBoxVisible = visible;
}

void anim::act::ActorModel::setBoundingBoxSize(const vec3f& dimensions) noexcept {
    mBoundingBoxSize = dimensions;
}

void anim::act::ActorModel::setModelScale(f32 scale) noexcept {
    mScale = scale;
}

void anim::act::ActorModel::setFillColor(const vec4b& fillColor) noexcept {
    mFillColor = fillColor;
}

void anim::act::ActorModel::setModelAndBoundingBoxSize(f32 modelSize, const vec3f& size) noexcept
{
    mScale = modelSize;
    mBoundingBoxSize = size;
}