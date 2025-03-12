#ifndef _CONTAINER_DICTIONARY_
#define _CONTAINER_DICTIONARY_

#include <Core/Container/coreLinkedList.hpp>

namespace core {

template<typename TKey, typename TValue>
class HashMap
{
private:
    struct Pair
    {
        TKey key;
        TValue value;
    };

    LinkedList<Pair> mList;
public:

    class iterator
    {
    private: using Node = typename LinkedList<Pair>::Node;
    public:
        explicit iterator(Node* listHead, Node* listTail, Node* pos)
            : mIterator(listHead, listTail, pos) {}

        bool operator==(const iterator& other) {
            return this->mIterator == other->mIterator;
        }
        bool operator!=(const iterator& other) {
            return this->mIterator != other->mIterator;
        }

        iterator& operator++() { ++mIterator; return *this; }
        iterator& operator--() { --mIterator; return *this; }

        TValue& operator*()  { 
            return mIterator.node()->value.value;  
        }
        TValue* operator->() { 
            return &mIterator.node()->value.value; 
        }
    private:
        typename LinkedList<Pair>::iterator mIterator;
    };

    inline iterator begin() { 
        return iterator(mList.getListHead(), mList.getListTail(), mList.getListHead()); 
    }
    inline iterator end() { 
        return iterator(mList.getListHead(), mList.getListTail(), mList.getListTail());
    }

	HashMap() = default;
    ~HashMap() { mList.clear(); }


    typename LinkedList<Pair>::Node* findNode(const TKey& key)
    {
        for (auto iter = mList.begin(); iter != mList.end(); ++iter)
        {
            if (iter->key == key)
                return iter.node();            
        }
        return nullptr;
    }

    inline void clear()
    {
        mList.clear();
    }

    void add(TKey key, TValue value)
    {
        mList.insertEnd(Pair{key, value});
    }

    void remove(TKey key)
    {
        typename LinkedList<Pair>::Node* node = findNode(key);

        if (node == nullptr)
            return;

        mList.remove(node);
    }

    TValue* get(TKey key)
    {
        typename LinkedList<Pair>::Node* node = findNode(key);

        if (node == nullptr)
            return nullptr;
        
        return &node->value.value;
    }
    
    TValue* last()  { return mList.end().node()->value.value;   }
    TValue* first() { return mList.begin().node()->value.value; }
};
}
#endif