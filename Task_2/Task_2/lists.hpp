#pragma once
#include <string>
#include <iostream>
#include <xmemory>

using namespace std;

template<typename ValueType, template <class>typename List>
class Queue;

template<typename ValueType>
class UnidirectionalList {
protected:
	class Element {
	public:
		shared_ptr<Element> next_element_;
		ValueType id_;
	};
protected:
	shared_ptr<Element> top_element_;
	ValueType GetFrontElement();
public:
	friend class Queue<ValueType, UnidirectionalList>;

	UnidirectionalList();
	void PushBack(ValueType id);
	void PopElement(ValueType id);
	bool Find(ValueType id);

	void PrintList();

};


template<typename ValueType>
class BidirectionalList :public UnidirectionalList<ValueType> {
private:
	class Element :public UnidirectionalList<ValueType>::Element {
	public:
		using UnidirectionalList<ValueType>::Element::id_;
		shared_ptr<Element> next_element_;
		shared_ptr<Element> prev_element_;
	};
	shared_ptr<Element> top_element_;
	shared_ptr<Element> front_element_;

	ValueType GetFrontElement() { return this->front_element_->id_; }
	void PopFront();
	void PopBack();

public:
	friend class Queue<ValueType, BidirectionalList>;

	BidirectionalList();

	void PushBack(ValueType id);
	void PushFront(ValueType id);
	void PopElement(ValueType id);
	bool Find(ValueType id);

	void PrintList();

};

template<typename ValueType, template <class>typename List>
class Queue {
private:
	List<ValueType>* list_;
public:
	Queue(List<ValueType>& list) {list_ = &list; }
	void PushBack(ValueType id) {
		list_->PushBack(id);
	}
	ValueType Pop() {
		ValueType id_ = list_->GetFrontElement();
		list_->PopElement(list_->GetFrontElement());
		return id_;
	}
	bool Find(ValueType id) {
		return list_->Find(id);
	}
};


template<typename ValueType>
inline UnidirectionalList<ValueType>::UnidirectionalList()
{
	top_element_ = nullptr;
}

template<typename ValueType>
inline ValueType UnidirectionalList<ValueType>::GetFrontElement()
{
	auto current_element = top_element_;

	while (current_element->next_element_)
	{
		current_element = current_element->next_element_;
	}
	return current_element->id_;
}

template<typename ValueType>
inline void UnidirectionalList<ValueType>::PushBack(ValueType id)
{
	if (!top_element_) {
		shared_ptr<Element> new_top(new Element);
		new_top->id_ = (id);

		new_top->next_element_ = nullptr;
		top_element_ = std::move(new_top);

		return;
	}
	shared_ptr<Element> new_top(new Element);
	new_top->id_ = (id);

	new_top->next_element_ = std::move(top_element_);
	top_element_ = std::move(new_top);

}

template<typename ValueType>
inline void UnidirectionalList<ValueType>::PopElement(ValueType id)
{
	auto current_element = top_element_;

	if (current_element->id_ == id) {
		top_element_ = move(current_element->next_element_);
		return;
	}

	while (current_element->next_element_) {
		if (current_element->next_element_->id_ == id) {
			if (current_element->next_element_) {
				current_element->next_element_ = current_element->next_element_->next_element_;
				return;
			}
		}
		current_element = current_element->next_element_;
	}
}

template<typename ValueType>
inline bool UnidirectionalList<ValueType>::Find(ValueType id)
{
	auto current_element = top_element_;

	while (current_element->next_element_) {
		if (current_element->id_ == id) {
			return true;
		}
		current_element = current_element->next_element_;
	}
	if (current_element->id_ == id)
		return true;
	return false;
}

template<typename ValueType>
inline void UnidirectionalList<ValueType>::PrintList()
{
	if (!top_element_) {
		string message = "Its empty\n";
		throw message;
	}
	auto current_element = top_element_;

	while (current_element) {
		std::cout << current_element->id_ << " ";
		current_element = current_element->next_element_;
	}
	std::cout << endl;
}

template<typename ValueType>
inline void BidirectionalList<ValueType>::PopFront()
{
	auto current_element = front_element_;
	if (current_element->next_element_) {
		current_element->next_element_->prev_element_ = current_element->next_element_;
	}
	front_element_ = move(current_element->next_element_);
}

template<typename ValueType>
inline void BidirectionalList<ValueType>::PopBack()
{
	auto current_element = top_element_;
	if (current_element->prev_element_) {
		current_element->prev_element_->next_element_ = current_element->next_element_;
	}
	top_element_ = move(top_element_->prev_element_);
}

template<typename ValueType>
inline BidirectionalList<ValueType>::BidirectionalList()
{
	this->front_element_ = nullptr;
	this->top_element_ = nullptr;
}

template<typename ValueType>
inline void BidirectionalList<ValueType>::PushBack(ValueType id)
{
	if (!front_element_) {
		shared_ptr<Element> new_top(new Element);
		new_top->id_ = id;

		top_element_ = new_top;
		top_element_->next_element_ = nullptr;
		front_element_ = new_top;
		front_element_->prev_element_ = nullptr;
		return;
	}

	shared_ptr<Element> new_top(new Element);
	new_top->id_ = id;

	new_top->prev_element_ = top_element_;
	new_top->next_element_ = nullptr;
	top_element_->next_element_ = new_top;

	top_element_ = new_top;
}

template<typename ValueType>
inline void BidirectionalList<ValueType>::PushFront(ValueType id)
{
	if (!top_element_) {
		shared_ptr<Element> new_top(new Element);
		new_top->id_ = id;

		top_element_ = new_top;
		top_element_->next_element_ = nullptr;
		front_element_ = new_top;
		front_element_->prev_element_ = nullptr;
		return;
	}

	shared_ptr<Element> new_top(new Element);
	new_top->id_ = id;

	new_top->next_element_ = front_element_;
	new_top->prev_element_ = nullptr;
	front_element_->prev_element_ = new_top;

	front_element_ = new_top;

}

template<typename ValueType>
inline void BidirectionalList<ValueType>::PopElement(ValueType id)
{
	auto current_element = front_element_;

	//if its first element, we should change front_element
	if (current_element->id_ == id) {
		PopFront();
		return;
	}

	while (current_element->next_element_) {
		if (current_element->id_ == id) {

			if (current_element->prev_element_) {
				current_element->prev_element_->next_element_ = current_element->next_element_;
			}
			if (current_element->next_element_) {
				current_element->next_element_->prev_element_ = current_element->prev_element_;
			}
			return;
		}
		current_element = current_element->next_element_;
	}

	//if its last element, we should change top_element

	if (top_element_->id_ == id) {

		PopBack();
		return;
	}
}

template<typename ValueType>
inline bool BidirectionalList<ValueType>::Find(ValueType id)
{
	auto current_element = front_element_;

	while (current_element != top_element_) {
		if (current_element->id_ == id) {
			return true;
		}
		current_element = current_element->next_element_;
	}
	if (current_element->id_ == id)
		return true;
	return false;
}

template<typename ValueType>
inline void BidirectionalList<ValueType>::PrintList()
{
	shared_ptr<Element> current_element = front_element_;
	while (current_element) {
		std::cout << current_element->id_ << " ";
		current_element = current_element->next_element_;
	}
	std::cout << endl;
}
