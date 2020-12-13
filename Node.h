#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>

template <typename T>
class Node
{
private:
	template <typename Iter>
	class BinaryTreeIterator
	{
		// It's needed to call private constructor outside of the class (in begin, end etc.)
		friend class Node<T>;

	public:
		typedef Iter iterator_type;
		typedef iterator_type* pointer;

		pointer value;

	private:
		// Create iterator via begin, end, ++, -- etc
		BinaryTreeIterator(pointer p) : value(p) { }

	public:
		// Public constructor copy (standards oblige to make it)
		BinaryTreeIterator(BinaryTreeIterator const& it) : value(it.value) { }

		// Manimulations by sign with iterator
		bool operator !=(BinaryTreeIterator const& other) const { return value != other.value; }
		bool operator ==(BinaryTreeIterator const& other) const { return value == other.value; }
		Iter operator *() const { return *this->value; }
		BinaryTreeIterator& operator ++()
		{
			pointer p;
			if (value->rightLeaf != nullptr)
			{
				value = value->rightLeaf;
				while (value->leftLeaf != nullptr) value = value->leftLeaf;
			}
			else
			{
				p = value->parent;
				while (p != nullptr && value == p->rightLeaf)
				{
					value = p;
					p = p->parent;
				}
				value = p;
			}

			return *this;
		}
		BinaryTreeIterator operator ++(int)
		{
			pointer toReturn = value;
			pointer p;
			if (value->rightLeaf != nullptr)
			{
				value = value->rightLeaf;
				while (value->leftLeaf != nullptr) value = value->leftLeaf;
			}
			else
			{
				p = value->parent;
				while (p != nullptr && value == p->rightLeaf)
				{
					value = p;
					p = p->parent;
				}
				value = p;
			}

			return toReturn;
		}
		BinaryTreeIterator& operator +=(const size_t& iterations)
		{
			for (size_t i = 0; i < iterations; ++i)
			{
				pointer p;
				if (value->rightLeaf != nullptr)
				{
					value = value->rightLeaf;
					while (value->leftLeaf != nullptr) value = value->leftLeaf;
				}
				else
				{
					p = value->parent;
					while (p != nullptr && value == p->rightLeaf)
					{
						value = p;
						p = p->parent;
					}
					value = p;
				}
			}

			return *this;
		}
		BinaryTreeIterator& operator --()
		{
			pointer p;
			if (value->leftLeaf != nullptr)
			{
				value = value->leftLeaf;
				while (value->rightLeaf != nullptr) value = value->rightLeaf;
			}
			else
			{
				p = value->parent;
				while (p != nullptr && value == p->leftLeaf)
				{
					value = p;
					p = p->parent;
				}
				value = p;
			}

			return *this;
		}
		BinaryTreeIterator operator --(int)
		{
			pointer toReturn = value;
			pointer p;
			if (value->leftLeaf != nullptr)
			{
				value = value->leftLeaf;
				while (value->rightLeaf != nullptr) value = value->rightLeaf;
			}
			else
			{
				p = value->parent;
				while (p != nullptr && value == p->leftLeaf)
				{
					value = p;
					p = p->parent;
				}
				value = p;
			}

			return toReturn;
		}
		BinaryTreeIterator& operator -=(const size_t& iterations)
		{
			for (size_t i = 0; i < iterations; ++i)
			{
				pointer p;
				if (value->leftLeaf != nullptr)
				{
					value = value->leftLeaf;
					while (value->rightLeaf != nullptr) value = value->rightLeaf;
				}
				else
				{
					p = value->parent;
					while (p != nullptr && value == p->leftLeaf)
					{
						value = p;
						p = p->parent;
					}
					value = p;
				}
			}

			return *this;
		}
	};
	friend class BinaryTreeIterator<T>;

public:
	Node(T data = T(), Node<T>* parent = nullptr, Node<T>* leftLeaf = nullptr, Node<T>* rightLeaf = nullptr) :data(data), parent(parent), leftLeaf(leftLeaf), rightLeaf(rightLeaf) { }
	~Node() { }

	typedef BinaryTreeIterator<Node<T>> iterator;
	typedef BinaryTreeIterator<const Node<T>> const_iterator;


	void insert(T data);							// Insert a value
	void clear() { recursiveClearMethod(this); }	// Clear all elements except root
	void print() { recursivePrintMethod(this); }	// Print all elements

	void erase(Node<T>::iterator& iterator);		// Delete a value and rebalance the tree (doesn't work with node, cuz idk how I can this pointer, that always points to original one)
	Node<T>* find(const Node<T>::iterator iterator)	// Same thing as above, but it searches by iterator
	{ return iterator.value; }	
	Node<T>* find(T data);							// Find an element by given data

	// Iterator range based methods
	iterator begin()
	{
		Node<T>* currentNode = this;
		while (currentNode->leftLeaf != nullptr)
			currentNode = currentNode->leftLeaf;

		return iterator(currentNode);
	}
private: iterator root() { return this; }			// Private cuz it must be used only by methods
public:
	iterator end() { return nullptr; }
	iterator rbegin()
	{
		Node<T>* currentNode = this;
		while (currentNode->rightLeaf != nullptr)
			currentNode = currentNode->rightLeaf;

		return iterator(currentNode);
	}
	iterator rend() { return nullptr; }
	const_iterator cbegin() const
	{
		const Node<T>* currentNode = this;
		while (currentNode->leftLeaf != nullptr)
			currentNode = currentNode->leftLeaf;

		return const_iterator(currentNode);
	}
	const_iterator cend() { return nullptr; }
	const_iterator crbegin()
	{
		const Node<T>* currentNode = this;
		while (currentNode->rightLeaf != nullptr)
			currentNode = currentNode->rightLeaf;

		return const_iterator(currentNode);
	}
	const_iterator crend() { return nullptr; }

	friend std::ostream& operator <<(std::ostream& os, const Node<T>& value) { return os << value.data; }

private:
	// Node pointers and data
	T data;
	Node<T>* parent;
	Node<T>* leftLeaf;
	Node<T>* rightLeaf;

	// Methods to do other methods, which require recursion
	void recursivePrintMethod(Node<T>* pointer);
	void recursiveClearMethod(Node<T>* pointer);
	void recursiveEraseMethod(Node<T>* pointer);
	
};

#endif // !NODE_H



template<typename T>
inline void Node<T>::insert(T data)
{
	// If default value is equal to default value (so it is not assigned)
	if (this->data == T())
	{
		this->data = data;
	}
	else
	{
		// If you want to create a multi map - remove 3rd while condition and if after it
		Node<T>* currentElement = this;
		while (currentElement->leftLeaf != nullptr || currentElement->rightLeaf != nullptr)
		{
			// Left side
			if (currentElement->data > data)
			{
				if (currentElement->leftLeaf == nullptr) break;
				currentElement = currentElement->leftLeaf;
				continue;
			}

			// Right side
			if (currentElement->data < data)
			{
				if (currentElement->rightLeaf == nullptr) break;
				currentElement = currentElement->rightLeaf;
				continue;
			}

			if (currentElement->data == data) return;
		}
		currentElement->data > data ? currentElement->leftLeaf = new Node<T>(data, currentElement) : currentElement->rightLeaf = new Node<T>(data, currentElement);
	}
}

template<typename T>
inline void Node<T>::recursiveEraseMethod(Node<T>* pointer)
{
	if (pointer == nullptr) return;
	// If leaf doesn't have any child
	if (pointer->leftLeaf == nullptr && pointer->rightLeaf == nullptr) {
		if (pointer->parent->leftLeaf == pointer) pointer->parent->leftLeaf = nullptr;
		else pointer->parent->rightLeaf = nullptr;
		return;
	}
	
	Node<T>* toSet = pointer;
	// Right side. Find minimal element
	if (toSet->data > root().value->data)
	{
		while (toSet->leftLeaf == nullptr) 
			if (toSet->rightLeaf != nullptr) toSet = toSet->rightLeaf;
		while (toSet->leftLeaf != nullptr)
			toSet = toSet->leftLeaf;
	}
	// Left side. Take right elements, if available, else - left one
	else
	{
		if (toSet->rightLeaf != nullptr) toSet = toSet->rightLeaf;
		else toSet = toSet->leftLeaf;
	}
	

	recursiveEraseMethod(toSet);
	// Change parent left/right element to element to toSet instead of 'pointer'
	if (pointer->parent != nullptr)
	{
		if (pointer->parent->rightLeaf == pointer) pointer->parent->rightLeaf = toSet;
		else pointer->parent->leftLeaf = toSet;
	}

	// Change leafs parent element to element to toSet instead of 'pointer'
	if (pointer->leftLeaf != nullptr) pointer->leftLeaf->parent = toSet;
	if (pointer->rightLeaf != nullptr) pointer->rightLeaf->parent = toSet;

	// Set parent and leafs of pointer to toSet
	toSet->parent = pointer->parent;
	toSet->leftLeaf = pointer->leftLeaf;
	toSet->rightLeaf = pointer->rightLeaf;
}

template<typename T>
inline void Node<T>::erase(Node<T>::iterator& iterator)
{
	if (iterator == nullptr) return;
	recursiveEraseMethod(iterator.value);

	//////////////////////////
	// SPACE TO CHANGE ROOT //
	//////////////////////////
}

template<typename T>
inline Node<T>* Node<T>::find(T data)
{
	Node<T>* currentElement = this;
	if (this == nullptr) return end();
	while (currentElement->rightLeaf != nullptr || currentElement->leftLeaf != nullptr)
	{
		if (currentElement->data == data) return currentElement;

		// Left side
		if (currentElement->data > data)
			if (currentElement->leftLeaf != nullptr) currentElement = currentElement->leftLeaf;
		// Right side
			else if (currentElement->rightLeaf != nullptr) currentElement = currentElement->rightLeaf;
	}
	if (currentElement->data != data) return end();

	return currentElement;
}

template<typename T>
inline void Node<T>::recursivePrintMethod(Node<T>* pointer)
{
	if (pointer == nullptr) return;
	recursivePrintMethod(pointer->leftLeaf);
	std::cout << pointer->data << std::endl;
	recursivePrintMethod(pointer->rightLeaf);
}

template<typename T>
inline void Node<T>::recursiveClearMethod(Node<T>* pointer)
{
	// If a node doesn't have a leaf
	if (pointer == nullptr) return;

	// Node calls by recurtion 2 methods for his 2 leafs
	recursiveClearMethod(pointer->leftLeaf);
	recursiveClearMethod(pointer->rightLeaf);

	// If it is root. Object will be deleted automaticaly when function with tree will terminate
	if (pointer->parent == nullptr) return;

	pointer == pointer->parent->rightLeaf ? pointer->parent->rightLeaf = nullptr : pointer->parent->leftLeaf = nullptr;

	delete pointer;
}