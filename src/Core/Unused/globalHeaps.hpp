//#ifndef _ANIM_GLOBAL_HEAPS_
//#define _ANIM_GLOBAL_HEAPS_
//
//#include <Core/Memory/coreHeap.hpp>
//#include <Core/Types/BasicTypes.hpp>
//
//namespace anim {
//
//#define GLOBAL_HEAP_COUNT 8
//
//
//constexpr auto mbyte(u64 value) {
//    return value * 1000000;
//}
//
//constexpr auto kbyte(u64 value) {
//    return value * 1000;
//}
//
//struct HeapData
//{
//    core::Heap  heap;
//    std::size_t size;
//    const char* name;
//};
//
//extern HeapData globalHeaps[GLOBAL_HEAP_COUNT];
//
//bool initHeaps();
//void freeHeaps();
//}
//#endif