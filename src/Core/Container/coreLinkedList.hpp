//#ifndef _CONTAINER_DOUBLE_LIST_
//#define _CONTAINER_DOUBLE_LIST_
//
//namespace core {
//
//template<typename T>
//class LinkedList
//{
//public:
//    struct Node
//    {
//        Node(const T& e = T(), Node* n = nullptr, Node* p = nullptr)
//            : value(e), next(n), prev(p) {}
//
//        T value;
//        Node* next, * prev;
//    };
//
//    class iterator
//    {
//    public:
//        explicit iterator(Node* listHead, Node* listTail, Node* pos = nullptr)
//            : mListHead(listHead), mListTail(listTail), mListIter(pos)
//        {
//            if (mListIter == nullptr)
//                mListIter = mListHead;
//        }
//
//        bool operator==(const iterator& other) {
//            return mListIter == other.mListIter;
//        }
//        bool operator!=(const iterator& other) {
//            return mListIter != other.mListIter;
//        }
//
//        iterator& operator++() {
//            mListIter = mListIter->next;
//            return *this;
//        }
//        iterator& operator--() {
//            mListIter = mListIter->prev;
//            return *this;
//        }
//
//		iterator& operator++(int) {
//			iterator result(*this);
//			++(*this);
//			return result;
//		}
//		iterator& operator--(int) {
//			iterator result(*this);
//			--(*this);
//			return result;
//		}
//
//        T& operator* () const { return  mListIter->value; }
//        T* operator->() const { return &mListIter->value; }
//
//        Node* node() const { return mListIter; }
//        
//    private:
//        Node* mListHead, *mListTail, *mListIter;
//    };
//
//    iterator begin() { 
//        return iterator(mListHead, mListTail, mListHead); 
//    }
//    iterator at(Node* node) { 
//        return iterator(mListHead, mListTail, node);
//    }
//    iterator end() { 
//        return iterator(mListHead, mListTail, mListTail->next->next->next->next); 
//    }
//
//	LinkedList() : isEmpty(true) {
//		mListHead = mListTail = new Node;
//	}
//
//    ~LinkedList() { this->clear(); }
//
//
//    Node* allocNode(const T& e = T(), Node* n = nullptr, Node* p = nullptr)
//    {
//		return new Node(e, n, p);
//    }
//
//    void freeNode(Node* node)
//    {
//        delete node;
//    }
//
//    void insertBegin(const T&& value)
//    {
//        if (isEmpty)
//            mListHead = mListTail = allocNode(value);
//        else
//        {
//            Node* node = allocNode(std::move(value), mListHead, nullptr);
//            mListHead->prev = node;
//            mListHead = node;
//        }
//    }
//
//    void insertBegin(const T& value)
//    {
//        if (isEmpty)
//            mListHead = mListTail = allocNode(value);
//        else
//        {
//            Node* node = allocNode(value, mListHead, nullptr);
//            mListHead->prev = node;
//            mListHead = node;
//        }
//    }
//
//    void insertEnd(const T&& value)
//    {
//        if (isEmpty)
//            mListHead = mListTail = allocNode(value);
//        else
//        {
//            Node* node = allocNode(std::move(value), nullptr, mListTail);
//            mListTail->next = node;
//            mListTail = node;            
//        }
//    }
//
//    void insertEnd(const T& value)
//    {
//        if (isEmpty)
//            mListHead = mListTail = allocNode(value);
//        else
//        {
//            Node* node = allocNode(value, nullptr, mListTail);
//            mListTail->next = node;
//            mListTail = node;            
//        }
//    }
//
//    bool remove(Node* node)
//    {
//        Node* rNode = mListHead;
//
//        while (rNode != nullptr)
//        {
//            if (rNode == node)
//                break;
//            rNode = rNode->next;
//        }
//
//        if (rNode == node)
//        {
//            if (rNode == mListHead) mListHead = rNode->next;
//            if (rNode == mListTail) mListTail = rNode->prev;
//
//            if (rNode->prev != nullptr)
//                rNode->prev->next = rNode->next;
//            
//            if (rNode->next != nullptr)
//                rNode->next->prev = rNode->prev;
//
//            freeNode(rNode);
//            return true;
//        }
//        return false;
//    }
//
//    void clear()
//    {
//        Node* iter = mListHead;
//
//        while (iter != nullptr)
//        {
//            Node* node = iter;
//            iter = iter->next;
//
//            freeNode(node);
//        }
//        mListHead = mListTail = nullptr;
//    }
//
//    Node* find(T&& value) const
//    {
//        Node* iter = mListHead;
//
//        while (iter != nullptr)
//        {
//            if (iter->value == value)
//                return iter;
//
//            iter = iter->next;
//        }
//        return nullptr;     
//    }
//
//    Node* find(const T& value) const
//    {
//        Node* iter = mListHead;
//
//        while (iter != nullptr)
//        {
//            if (iter->value == value)
//                return iter;
//
//            iter = iter->next;
//        }
//        return nullptr;         
//    }
//
//    inline Node* getListHead() const noexcept {
//        return mListHead;
//    }
//
//    inline Node* getListTail() const noexcept {
//        return mListTail;
//    }
//
//  //  inline bool isEmpty() const noexcept { 
//  //      return mListHead == nullptr; 
//		////return mListHead->next == nullptr;
//  //  }
//
//private:
//    Node* mListHead = nullptr;
//    Node* mListTail = nullptr;
//	bool isEmpty = true;
//};
//
//template<typename T>
//class List;
//class ListIterator;
//
//
//class ListNode
//{
//	friend class ListIterator;
//	template<class T> friend class List;
//protected:
//	
//	ListNode* next, * prev;
//
//	void pushBack(ListNode* node)
//	{
//		node->next = this;
//		node->prev = prev;
//		prev->next = node;
//		prev = node;
//	}
//
//	void unlink()
//	{
//		auto* next_ = next, * prev_ = prev;
//		next_->prev = prev_;
//		prev_->next = next_;
//		next = this;
//		prev = this;
//	}
//public:
//	ListNode() : next(this), prev(this) {}
//	~ListNode() { unlink(); }
//};
//
//class ListIterator
//{
//protected:
//	ListNode* node;
//public:
//	ListIterator(ListNode* node_) : node(node_) {}
//
//	ListIterator& operator++() {
//		node = node->next;
//		return *this;
//	}
//
//	bool operator!=(ListIterator iter) const { return node != iter.node; }
//	bool operator==(ListIterator iter) const { return node == iter.node; }
//};
//
//template<class T>
//class List 
//{
//public:
//	class ValueNode : public ListNode 
//	{
//		friend class List<T>;
//		T value;
//		ValueNode(T t) : value(t) {}
//	};
//
//	template<class U>
//	class IteratorT : public ListIterator 
//	{
//		friend class List<T>;
//		ValueNode* getNode() const { return static_cast<ValueNode*>(node); }
//	public:
//
//		IteratorT(ListNode* node_) : ListIterator{ node_ } {}
//
//		U& operator* () const { return  getNode()->value; }
//		U* operator->() const { return &getNode()->value; }
//
//		operator IteratorT<U const>() const { return node; }
//	};
//
//private:
//	ListNode list;
//public:
//	using iterator = IteratorT<T>;
//	using const_iterator = IteratorT<T const>;
//
//	~List() { clear(); }
//
//	bool empty() const { return list.next == &list; }
//
//	iterator begin() { return list.next; }
//	iterator end() { return &list; }
//
//	void pushBack(T t) { list.pushBack(new ValueNode(t)); }
//	void erase(iterator i) { delete i.node(); }
//	void erase(const_iterator i) { delete i.node(); }
//
//	void clear() {
//		while (!empty())
//			erase(begin());
//	}
//
//	// Implement the rest of the functionality.
//};
//
//struct f { int c; };
//void bar()
//{
//	List<f> i;
//
//
//	for (auto& a : i)
//	{
//		a.c = 0;
//	}
//}
//}
//#endif