#pragma once
#include "Core/Types/BasicTypes.hpp"

struct Shader;
namespace anim::gfx {

class PostProcessor
{
    PostProcessor() = default;
public:
    static PostProcessor& instance();

    struct EffectFlags
    {
        bool antialiasingEnabled : 1;
        bool distanceFogEnabled : 1;
        bool heatDistortEnabled : 1;
    };

    enum class EffectType : int
    {
        ANTIALIASING,
        DISTANCE_FOG,
        HEAT_DISTORT
    };

    void enableEffect(bool enable, EffectType effectType);
    void initialize(const EffectFlags& effectFlags);
    void update();
    void unload();

    const Shader* getShaderConst() const;
    Shader* getShader() const;
private:
    EffectFlags mFlags{};
};

}