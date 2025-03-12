/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actActorBase.hpp-
 *   Defines base actor classes.
 */

#ifndef _ANIM_ACTOR_BASE_
#define _ANIM_ACTOR_BASE_

#include "Core/Types/BasicTypes.hpp"
#include "Core/Utils/Vector2.hpp"
#include "Core/Utils/Vector3.hpp"
#include "Core/Utils/Vector4.hpp"
#include "Core/Container/corePolyMap.hpp"
#include "Engine/Actor/actProcess.hpp"
#include "Engine/Actor/actBaseProcess.hpp"
#include "Engine/Actor/actModelProcess.hpp"
#include "Engine/System/Raylib.hpp"
#include "Engine/Resource/resModelResource.hpp"

namespace anim::act {

//An entity, which like an actor, performs a dedicated role continuously.
class ActorBase
{
public:
    ActorBase() = default;
    virtual ~ActorBase() = default;

    //Called immediately after the constructor. Preferably use onEnter() instead.
    virtual void onCreate();

    //Called when the actor enters the scene and is fully initialized.
    virtual void onEnter();

    //Called continuously while the actor is active.
    virtual void onUpdate();

    //Called when the actor is removed from the scene.
    virtual void onLeave();

    //Called when the actor is removed from the scene due to an error.
    virtual void onAbort();

    void removeChild(const char* name, bool abort = false);

    void finishIf_(bool condition);
    void abortIf_(bool condition, const char* message = nullptr);

    //Immediately terminate execution and log a message if the condition is true.
    #define abortIf(args, message)   \
        if (args)                    \
        {                            \
            abortIf_(true, message); \
            return;                  \
        }

    //Finish execution if the condition is true.
    #define finishIf(args)           \
        if (args)                    \
        {                            \
            finishIf_(true);         \
            return;                  \
        }

    void endSubRoutines();
    void endSubProcesses();

    void abortSubRoutines();
    void abortSubProcesses();

    void endExecution();

    //Add an actor by name, with arguments to be passed into its constructor.
	template<typename ActorType, typename... Args>
	void addChild(const char* name, Args... args)
	{
		mChildren.insert(std::make_pair(name, new ActorType(std::forward<Args>(args)...)));

		mChildren[name]->mRoot = this;
		mChildren[name]->mName = name;
		mChildren[name]->onCreate();
        
        if constexpr (std::is_base_of<ActorModel, ActorType>::value)
            ActorModelScheduler::addProcess(mChildren[name]);
        else
		    ActorBaseScheduler::addProcess(mChildren[name]);
	}

    //Get an actor by name. Returns null if an actor by that name does not exist.
	template<typename ActorType>
	ActorType* getChild(const char* name)
	{
		return (ActorType*)(mChildren[name].get());
	}

	std::unordered_map<const char*, std::unique_ptr<ActorBase>> mChildren;

	ActorProcess* mProcess{};
    ActorBase* mRoot{};

    const char* mName{};
    u32 mNumProcesses = 0;
protected:
    friend class ActorProcess;
};

//An actor with extended functionality to represent a 3D object.
class ActorModel : public ActorBase
{
public:
    ActorModel();
    explicit ActorModel(vec3f position);

    ActorModel(vec3f position, vec3f rotation);
    ActorModel(vec3f position, vec3f rotation, f32 scale, bool wires);

    virtual void onRender();
    virtual void onPreRender();
    virtual void onPostRender();
    
    //Move the actor to the specified position.
    void translate   (const vec3f& position);

    //Set the X, Y, and Z rotation to the specified angle.
    void rotateOnXYZ (const vec3f& angles);

    //Set the X axis rotation to the specified angle.
    void rotateXAxis (f32 angle);

    //Set the Y axis rotation to the specified angle.
    void rotateYAxis (f32 angle);

    //Set the Z axis rotation to the specified angle.
    void rotateZAxis (f32 angle);

    //set the wireframe of the model to be visible.
    void setWireframeVisible(bool wireframe) noexcept;

    //Set the bounding box of the model to be visible.
    void setBoundingBoxVisible(bool visible) noexcept;

    //Set the size of the bounding box. This does not affect the size of the model.
    void setBoundingBoxSize(const vec3f& dimensions) noexcept;

    //Set the scale of the model. This does not affect the size of the bounding box.
    void setModelScale(f32 scale) noexcept;

    //Sets the size of both the model and bounding box.
    void setModelAndBoundingBoxSize(f32 modelSize, const vec3f& boundingBoxDimensions) noexcept;

    //Set the tint of the model in RGBA color. It is white by default.
    void setFillColor(const vec4b& fillColor) noexcept;

    static bool createModelResource(u32 id, const char* filepath);
    static bool createModelResourceCylinder(u32 id, f32 radius, f32 height, s32 slices);
    static bool createModelResourceTorus(u32 id, f32 radius, f32 size, s32 radSeg, s32 sides);
    static bool createModelResourceRectPrism(u32 id, const vec3f& dimensions);

    static void unloadModelResource(u32 id);
    bool setModelResource(u32 id);
    void removeModel();

    void generateModelCylinder(f32 radius, f32 height, s32 slices);
    void generateModelTorus(f32 radius, f32 size, s32 radSeg, s32 sides);
    void generateModelRectPrism(const vec3f& dimensions);

    //Get the bounding box of the model.
    [[nodiscard]] BoundingBox getBoundingBox() const noexcept;

    inline Material& getModelMaterial(u32 index) const {
        return mModel.materials[index];
    }

    vec4b mFillColor;
    vec4f mDirection;
    vec3f mRotation;
    vec3f mPosition; 
    vec3f mVelocity; 

    //Size of the actor's collision box
    vec3f mBoundingBoxSize;

    //Scale of the actor's model
    f32 mScale;

    struct RenderFlags
    {
        bool wireframeVisible : 1;
        bool wireframeInvisibleDebug : 1;
        bool boundingBoxVisible : 1;
        bool boundingBoxInvisibleDebug : 1;
        bool isModelActive : 1;
        bool isModelGlobalResource : 1;
    };

    RenderFlags mRenderFlags {
        false, false, false,
        false, false, false };
private:
    friend class ActorModelProcess;
    using ModelResourceHandle = entt::resource_handle<res::ModelResource>;

    RlModel mModel{};

    static void checkModelResourceExists(u32 id);
    static bool checkModelResourceHandle(u32 id, const ModelResourceHandle& handle);
};
}
#endif