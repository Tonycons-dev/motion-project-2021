//#include <Engine/System/globalHeaps.hpp>
//
//anim::HeapData anim::globalHeaps[GLOBAL_HEAP_COUNT] = {
//
//{core::Heap(), kbyte(0x04), "anim__remoteConnectionHeap"},
//{core::Heap(), kbyte(0x04), "anim__remoteConnectionInqHeap"},
//{core::Heap(), kbyte(0x04), "anim__remoteSerialPortHeap"},
//{core::Heap(), kbyte(0x04), "anim__remoteBtBindingHeap"},
//{core::Heap(), mbyte(0x80), "anim__ActorBaseHeap"}
//
//};
//
//bool anim::initHeaps()
//{
//    for (u64 n = 0; n < GLOBAL_HEAP_COUNT; n++) 
//    {
//        if (!globalHeaps[n].heap.init(globalHeaps[n].size, globalHeaps[n].name))
//        {
//            LOG_FAILURE(globalHeaps[n].heap.getMessage());
//            return false;
//        }
//    }
//    return true;
//}
//
//void anim::freeHeaps()
//{
//    for (u64 n = 0; n < GLOBAL_HEAP_COUNT; n++)
//    {
//        if (!globalHeaps[n].heap.free())
//            LOG_FAILURE(globalHeaps[n].heap.getMessage());
//    }
//}