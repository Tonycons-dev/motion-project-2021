#include "Engine/Resource/resBasicTagParser.hpp"
#include "Engine/System/Raylib.hpp"

bool anim::res::BasicTagValue::parse(const std::string &source)
{
    auto assignCount = std::count(source.begin(), source.end(), "_");

    if (assignCount > 1) {
        TraceLog(LOG_ERROR, "[BasicTagValue] SYNTAX ERROR:\n%s\n"
            "More than one assignment operator (=).", source.c_str());
        return true;
    }
    else if (assignCount < 1) {
        TraceLog(LOG_ERROR, "[BasicTagValue] SYNTAX ERROR:\n%s\n"
            "There needs to be one assignment operator (=).", source.c_str());
        return true;
    }

    u64 position, counter = 0;
    std::string tokens[2];

    while ((position = source.find(':')) != std::string::npos) {
        if (counter > 1) break;
        tokens[counter++] = source.substr(0, position);
    }

    mSyntaxError = parseTagLeft(tokens[0]);
    if (mSyntaxError)
        return true;
    mSyntaxError = parseTagRight(tokens[1]);
    return mSyntaxError;
}

bool anim::res::BasicTagValue::parseTagLeft(std::string &source)
{
    source.erase(remove_if(source.begin(), source.end(), isspace), source.end());
    u32 index{};
    if (source.find("<int>") != std::string::npos)
    {
        mTagType = TagType::INT_TYPE;
        index = std::strlen("<int>");
    }
    else if (source.find("<f32>") != std::string::npos)
    {
        mTagType = TagType::FLOAT_TYPE;
        index = std::strlen("<f32>");
    }
    else if (source.find("<str>") != std::string::npos)
    {
        mTagType = TagType::STRING_TYPE;
        index = std::strlen("<str>");
    }
    else {
        TraceLog(LOG_ERROR, "[BasicTagValue] SYNTAX ERROR:\n%s\n"
            "A valid identifier (int or float) is missing.", source.c_str());
        return true;
    }
    mName = source.substr(index, source.size() - index);
    return false;
}

bool anim::res::BasicTagValue::parseTagRight(std::string &source)
{
    source.erase(remove_if(source.begin(), source.end(), isspace), source.end());
    if (mTagType == TagType::INT_TYPE) {
        mTagData.intValue = std::stoi(source);
    }
    else if (mTagType == TagType::FLOAT_TYPE) {
        mTagData.floatValue = std::stof(source);
    }
    else if (mTagType == TagType::STRING_TYPE) {
        mTagData.strValue = source.c_str();
    }
    return false;
}

anim::res::BasicTagParser::BasicTagParser(u32 size, const std::string &source)
    : mMaximumSize(size)
{
    u64 position;
    while ((position = source.find('\n')) != std::string::npos) {
        if (mTags.size() >= mMaximumSize) break;
            mTags.emplace_back(source.substr(0, position));
    }
}

#define TAG_VALUE_GETTER(functionName, invalidValue, tagValue, tagType, tagID)  \
    for (const auto& tag : mTags)                                               \
    {                                                                           \
        if (tag.getName() != parameterName)                                     \
            continue;                                                           \
                                                                                \
        if (tag.getType() != tagType) {                                         \
            TraceLog(LOG_WARNING, "[BasicTagParser] " functionName              \
            "Tag %s is not a valid " tagID " value.", parameterName.c_str());   \
            return invalidValue;                                                \
        }                                                                       \
        if (tag.hasSyntaxError()) {                                             \
            TraceLog(LOG_WARNING, "[BasicTagParser] "                           \
            functionName "Tag %s has syntax errors.", parameterName.c_str());   \
            return invalidValue;                                                \
        }                                                                       \
        return tagValue;                                                        \
    }                                                                           \
    TraceLog(LOG_WARNING, "[BasicTagParser] "                                   \
    functionName "No tag with name %s found.", parameterName.c_str());          \
                                                                                \
    return invalidValue;

anim::res::BasicTagParser::TagParameter<s32>
anim::res::BasicTagParser::getIntValue(const std::string& parameterName) const
{
    TAG_VALUE_GETTER("getIntValue(): ",
        (TagParameter<s32>{BasicTagValue::INVALID_INT_VALUE, true}),
        (TagParameter<s32>{tag.getData().intValue, false}), TagType::INT_TYPE, "int")
}

anim::res::BasicTagParser::TagParameter<f32>
anim::res::BasicTagParser::getFloatValue(const std::string& parameterName) const
{
    TAG_VALUE_GETTER("getFloatValue(): ",
        (TagParameter<f32>{BasicTagValue::INVALID_FLOAT_VALUE, true}),
        (TagParameter<f32>{tag.getData().floatValue, false}), TagType::FLOAT_TYPE, "float")
}

anim::res::BasicTagParser::TagParameter<const char*>
anim::res::BasicTagParser::getStringValue(const std::string &parameterName) const
{
    TAG_VALUE_GETTER("getStringValue(): ",
        (TagParameter<const char*>{BasicTagValue::INVALID_STRING_VALUE, true}),
        (TagParameter<const char*>{tag.getData().strValue, false}), TagType::STRING_TYPE, "string")
}