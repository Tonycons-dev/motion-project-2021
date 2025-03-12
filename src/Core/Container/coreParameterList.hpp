#pragma once

#include <Core/Types/BasicTypes.hpp>
#include <Core/Utils/Vector2.hpp>
#include <Core/Utils/Vector3.hpp>
#include <Core/Utils/Vector4.hpp>

namespace core {

enum ParameterType : s8
{
    PARAM_CHAR   = 0x0, PARAM_BYTE   = 0x1, 
    PARAM_SHORT  = 0x2, PARAM_USHORT = 0x3, 
    PARAM_INT    = 0x4, PARAM_UINT   = 0x5,
    PARAM_LONG   = 0x6, PARAM_ULONG  = 0x7, 
    PARAM_FLOAT  = 0x8, PARAM_DOUBLE = 0x9, 
    PARAM_STRING = 0xa, PARAM_VEC2F  = 0xb,
    PARAM_VEC3F  = 0xc, PARAM_VEC4F  = 0xd,
};

class ParameterData
{
private: 
    using v2f = vec2f;
    using v3f = vec3f;
    using v4f = vec4f;
    using str = const char*;

    ParameterType mType;    
public:
    ParameterData(void ) : mType(PARAM_INT   ), ms32(0){};
    ParameterData(s8  n) : mType(PARAM_CHAR  ), ms8 (n) {}
    ParameterData(u8  n) : mType(PARAM_BYTE  ), mu8 (n) {}
    ParameterData(s16 n) : mType(PARAM_SHORT ), ms16(n) {} 
    ParameterData(u16 n) : mType(PARAM_USHORT), mu16(n) {}
    ParameterData(s32 n) : mType(PARAM_INT   ), ms32(n) {} 
    ParameterData(u32 n) : mType(PARAM_UINT  ), mu32(n) {}
    ParameterData(s64 n) : mType(PARAM_LONG  ), ms64(n) {} 
    ParameterData(u64 n) : mType(PARAM_ULONG ), mu64(n) {}
    ParameterData(f32 n) : mType(PARAM_FLOAT ), mf32(n) {}
    ParameterData(f64 n) : mType(PARAM_DOUBLE), mf64(n) {}
    ParameterData(v2f n) : mType(PARAM_VEC2F ), mv2f(n) {} 
    ParameterData(v3f n) : mType(PARAM_VEC3F ), mv3f(n) {}
    ParameterData(v4f n) : mType(PARAM_VEC4F ), mv4f(n) {}
    ParameterData(str n) : mType(PARAM_STRING), mstr(n) {}

    union 
    {
        s8  ms8;  u8  mu8;
        s16 ms16; u16 mu16;
        s32 ms32; u32 mu32;
        s64 ms64; u64 mu64;
        f32 mf32; f64 mf64;
        v2f mv2f; v3f mv3f;
        v4f mv4f; str mstr;
    };
};

template<typename... Args>
class ParameterList
{
private:
    using v2f = vec2f;
    using v3f = vec3f;
    using v4f = vec4f;
    using str = const char*;
public:
    va_list mArgs;
    ParameterList(Args... args)
    {

        mData = {std::forward<Args>(args)...};
    }

    constexpr auto size() const noexcept {
        return sizeof...(Args);
    }

    inline s8  getChar  (u32 i) const { return mData[i].ms8;  }
    inline u8  getByte  (u32 i) const { return mData[i].mu8;  }
    inline s16 getShort (u32 i) const { return mData[i].ms16; }
    inline u16 getUshort(u32 i) const { return mData[i].mu16; }
    inline s32 getInt   (u32 i) const { return mData[i].ms32; }
    inline u32 getUint  (u32 i) const { return mData[i].mu32; }
    inline f32 getFloat (u32 i) const { return mData[i].mf32; }
    inline f64 getDouble(u32 i) const { return mData[i].mf64; }
    inline v2f getVec2f (u32 i) const { return mData[i].mv2f; }
    inline v3f getVec3f (u32 i) const { return mData[i].mv3f; }
    inline v4f getVec4f (u32 i) const { return mData[i].mv4f; }
    inline str getString(u32 i) const { return mData[i].mstr; }
private:
    std::array<ParameterData, sizeof...(Args)> mData;
};

}