#pragma once
#include "Core/Types/BasicTypes.hpp"

namespace anim::res {

enum class TagType : int
{
    INT_TYPE = 0,
    FLOAT_TYPE = 1,
    STRING_TYPE = 2
};

struct BasicTagValue
{
public:
    static constexpr s32 INVALID_INT_VALUE = INT32_MAX;
    static constexpr f32 INVALID_FLOAT_VALUE = MAXFLOAT;
    static constexpr auto INVALID_STRING_VALUE = "";

    union TagData {
        const char* strValue;
        s32 intValue;
        f32 floatValue;
    };
private:
    std::string mName{};
    TagType mTagType{};
    TagData mTagData{};
    bool mSyntaxError{};
public:
    BasicTagValue() = default;
    explicit BasicTagValue(const std::string& source) {
        mSyntaxError = parse(source);
    }

    [[nodiscard]] inline const TagType& getType() const noexcept
    { return mTagType; }

    [[nodiscard]] inline const TagData& getData() const noexcept
    { return mTagData; }

    [[nodiscard]] inline const std::string& getName() const noexcept
    { return mName; }

    [[nodiscard]] inline const bool& hasSyntaxError() const noexcept
    { return mSyntaxError; }
private:
    bool parse(const std::string& source);
    bool parseTagLeft(std::string& source);
    bool parseTagRight(std::string& source);
};

class BasicTagParser
{
public:
    template<typename T>
    struct TagParameter {
        T value;
        bool invalid;
    };
    BasicTagParser(u32 size, const std::string& source);

    [[nodiscard]] TagParameter<s32>
        getIntValue(const std::string& parameterName) const;

    [[nodiscard]] TagParameter<f32>
        getFloatValue(const std::string& parameterName) const;

    [[nodiscard]] TagParameter<const char*>
        getStringValue(const std::string& parameterName) const;
private:
    const u32 mMaximumSize;
    std::vector<BasicTagValue> mTags;
};
}