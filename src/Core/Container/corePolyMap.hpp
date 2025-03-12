//#ifndef _CONTAINER_POLY_MAP_
//#define _CONTAINER_POLY_MAP_
//
//#include <Core/Container/coreLinkedList.hpp>
//
//namespace core {
//
//
//
//template<typename TKey, typename TValue>
//class DictionaryPair
//{
//public:
//	template<typename T, typename... Args>
//	void create(Args... args) {
//		value = new T(std::forward<Args>(args)...);
//	}
//
//	DictionaryPair(const TKey& key_) : key(key_) {}
//	~DictionaryPair() { if (value != nullptr) delete value; }
//
//	TKey key;
//	TValue* value = nullptr;
//};
//
//
//template<typename TKey, typename TValue>
//class Dictionary
//{
//	List<DictionaryPair<TKey, TValue>> mList;
//public:
//
//	class iterator
//	{
//	public:
//		iterator(List<DictionaryPair<TKey, TValue>>::iterator iter)
//			: mIterator(iter) {}
//
//		bool operator==(iterator other) const {
//			return mIterator == other.mIterator;
//		}
//		bool operator!=(iterator other) const {
//			return mIterator != other.mIterator;
//		}
//
//		iterator& operator++() {
//			++mIterator;
//			return *this;
//		}
//
//		iterator& operator++(int) {
//			PairIterator result(*this);
//			++(*this);
//			return result;
//		}
//
//		TValue& operator*() const { return *mIterator.value; }
//		TValue* operator->() const { return mIterator.value; }
//	private:
//		List<DictionaryPair<TKey, TValue>>::iterator mIterator;
//	};
//
//	iterator begin() { return iterator(mList.begin()); }
//	iterator end()   { return iterator(mList.end());   }
//
//	inline void clear() { mList.clear(); }
//
//	TValue* find(const TKey& key)
//	{
//		for (auto& iter : mList)
//		{
//			if (iter->key == key)
//				return &iter->value;
//		}
//		return nullptr;
//	}
//
//	TValue* get(TKey key)
//	{
//		auto* value = find(key);
//
//		if (value == nullptr)
//			throw std::invalid_argument("Dictionary: key value not found");
//
//		return value;
//	}
//
//	template<typename... Args>
//	void add(TKey key, Args... args)
//	{
//		mList.pushBack(DictionaryPair<TKey, TValue>(key, std::forward<Args>(args)...);
//	}
//
//	void remove(TKey key)
//	{
//		for (const auto& iter : mList)
//		{
//			if (iter->key == key)
//			{
//				mList.erase(iter);
//				return;
//			}
//		}
//	}
//};
//
//
//
//template<typename TKey, typename TValue>
//class PolyMap
//{
//public:
//	struct Pair
//	{
//		template<typename T, typename... Args>
//		void create(Args... args) {
//			value = new T(std::forward<Args>(args)...);
//		}
//
//		Pair(const TKey& key_) : key(key_) {}
//		~Pair() { if (value != nullptr) delete value; }
//
//		TKey key;
//		TValue* value = nullptr;
//	};
//
//	class iterator
//    {
//    private: using Node = typename LinkedList<Pair>::Node;
//    public:
//        explicit iterator(Node* listHead, Node* listTail, Node* pos)
//            : mIterator(listHead, listTail, pos) {}
//
//        bool operator==(const iterator& other) {
//            return this->mIterator == other.mIterator;
//        }
//        bool operator!=(const iterator& other) {
//            return this->mIterator != other.mIterator;
//        }
//
//        iterator& operator++() { ++mIterator; return *this; }
//        iterator& operator--() { --mIterator; return *this; }
//
//		iterator& operator++(int) {
//			iterator result(*this);
//			++(*this);
//			return result;
//		}
//		iterator* operator--(int) {
//			iterator result(*this);
//			++(*this);
//			return result;
//		}
//
//        TValue& operator*()  { 
//            return *mIterator.node()->value.value;  
//        }
//        TValue* operator->() { 
//            return mIterator.node()->value.value; 
//        }
//    private:
//        typename LinkedList<Pair>::iterator mIterator;
//    };
//
//	inline iterator begin() {
//		return iterator(mList.getListHead(), mList.getListTail(), mList.getListHead());
//	}
//	inline iterator end() {
//		return iterator(mList.getListHead(), mList.getListTail(), mList.getListTail());
//	}
//
//	PolyMap() = default;
//	~PolyMap() { mList.clear(); }
//
//	inline void clear()
//	{
//		mList.clear();
//	}
//
//	typename LinkedList<Pair>::Node* findNode(const TKey& key)
//	{
//		for (auto iter = mList.begin(); iter != mList.end(); ++iter)
//		{
//			if (iter->key == key)
//				return iter.node();
//		}
//
//		throw 10;
//		return nullptr;
//	}
//
//	template<typename T, typename... Args>
//	void add(TKey key, Args... args)
//	{
//		mList.insertEnd(Pair(key));
//		mList.end().node()->value.template create<T, Args...>(std::forward<Args>(args)...);
//	}
//
//	void remove(TKey key)
//	{
//		typename LinkedList<Pair>::Node* node = findNode(key);
//
//		if (node == nullptr)
//			return;
//
//		mList.remove(node);
//	}
//
//	TValue* get(TKey key)
//    {
//        typename LinkedList<Pair>::Node* node = findNode(key);
//
//        if (node == nullptr)
//            throw std::invalid_argument("PolyMap: Key value not found");
//        
//        return node->value.value;
//    }
//
//	Pair* getPair(TKey key)
//	{
//		typename LinkedList<Pair>::Node* node = findNode(key);
//	
//		if (node == nullptr)
//			throw std::invalid_argument("PolyMap: Key pair not found");
//
//		return &node->value;
//	}
//
//	TValue* last() { return mList.end().node()->value.value; }
//	TValue* first() { return mList.begin().node()->value.value; }
//	
//private: 
//	LinkedList<Pair> mList;
//};
//}
//
//#endif