#pragma once
#include <string>
#include <iostream>
#include <xmemory>

using namespace std;

template<typename ValueType>
class BidirectionalList {
protected:
	class Element {
	private:
		shared_ptr<Element> prev_element_;
	protected:
		ValueType id_;
		shared_ptr<Element> next_element_;
	public:

		void SetId(ValueType id);
		void SetNextElement(shared_ptr<Element> next);
		void SetPrevousElement(shared_ptr<Element> prevous);

		ValueType GetId() { return this->id_; }
		shared_ptr<Element> GetNextElement() { return this->next_element_; }
		shared_ptr<Element> GetPrevousElement() { return this->prev_element_; }
	};

	int size_;
	shared_ptr<Element> top_element_;
private:
	shared_ptr<Element> front_element_;
	void PopFront();
	void PopBack();
public:
	ValueType GetFrontElement() { return this->front_element_->GetId(); }
	BidirectionalList();


	void PushBack(ValueType id);
	void PushFront(ValueType id);
	void DeleteElement(ValueType id);
	bool Find(ValueType id);

	int GetSize() { return this->size_; }
	void PrintList();

};

template<typename ValueType>
class UnidirectionalList : public BidirectionalList<ValueType> {
private:
	using BidirectionalList<ValueType>::Element;
	using BidirectionalList<ValueType>::size_;
	using BidirectionalList<ValueType>::top_element_;
public:
	ValueType GetFrontElement();
	UnidirectionalList();
	void PushBack(ValueType id);
	void DeleteElement(ValueType id);
	bool Find(ValueType id);

	void PrintList();

	shared_ptr<Element> GetPrevousElement() = delete;
	void SetPrevousElement(shared_ptr<Element>) = delete;
	void PushFront(ValueType) = delete;
};


template<typename ValueType, template <class>typename List>
class Queue {
private:
	List<ValueType> list_;
public:
	void PushBack(ValueType id) {
		list_.PushBack(id);
	}
	ValueType Pop() {
		ValueType id_ = list_.GetFrontElement();
		list_.DeleteElement(list_.GetFrontElement());
		return id_;
	}
	bool IsEmpty() {
		if (!list_.GetSize())
			return true;
		else
			return false;
	}
	int GetSize() {
		return list_.GetSize();
	}
};



template<typename ValueType>
inline ValueType UnidirectionalList<ValueType>::GetFrontElement()
{
	auto current_element = top_element_;

	while (current_element->GetNextElement())
	{
		current_element = current_element->GetNextElement();
	}
	return current_element->GetId();
}

template<typename ValueType>
UnidirectionalList<ValueType>::UnidirectionalList() {
	this->size_ = 0;
}

template<typename ValueType>
void UnidirectionalList<ValueType>::PushBack(ValueType id) {
	if (!size_) {
		shared_ptr<Element> new_top(new Element);
		new_top->SetId(id);

		new_top->SetNextElement(nullptr);
		top_element_ = std::move(new_top);

		size_++;
		return;
	}
	shared_ptr<Element> new_top(new Element);
	new_top->SetId(id);

	new_top->SetNextElement(std::move(top_element_));
	top_element_ = std::move(new_top);

	size_++;
}

template<typename ValueType>
void UnidirectionalList<ValueType>::DeleteElement(ValueType id) {
	auto current_element = top_element_;

	if (current_element->GetId() == id) {
		top_element_ = move(current_element->GetNextElement());
		size_--;
		return;
	}

	while (current_element->GetNextElement()) {
		if (current_element->GetNextElement()->GetId() == id) {
			if (current_element->GetNextElement()) {
				current_element->SetNextElement(current_element->GetNextElement()->GetNextElement());
				size_--;
				return;
			}
		}
		current_element = current_element->GetNextElement();
	}


}

template<typename ValueType>
inline bool UnidirectionalList<ValueType>::Find(ValueType id) {
	auto current_element = top_element_;

	while (current_element->GetNextElement()) {
		if (current_element->GetId() == id) {
			return true;
		}
		current_element = current_element->GetNextElement();
	}
	if (current_element->GetId() == id)
		return true;
	return false;
}



template<typename ValueType>
inline void UnidirectionalList<ValueType>::PrintList() {
	if (size_ == 0) {
		throw "its empty\n";
	}
	auto current_element = top_element_;

	while (current_element->GetNextElement()) {
		std::cout << current_element->GetId() << " ";
		current_element = current_element->GetNextElement();
	}
	std::cout << current_element->GetId() << endl;
}

template<typename ValueType>
BidirectionalList<ValueType>::BidirectionalList() {
	this->size_ = 0;
}

template<typename ValueType>
void BidirectionalList<ValueType>::PushBack(ValueType id) {
	if (size_ == 0) {
		shared_ptr<Element> new_top(new Element);
		new_top->SetId(id);

		top_element_ = new_top;
		top_element_->SetNextElement(nullptr);
		front_element_ = new_top;
		front_element_->SetPrevousElement(nullptr);
		size_++;
		return;
	}

	shared_ptr<Element> new_top(new Element);
	new_top->SetId(id);

	new_top->SetPrevousElement(top_element_);
	new_top->SetNextElement(nullptr);
	top_element_->SetNextElement(new_top);

	top_element_ = new_top;

	size_++;
}

template<typename ValueType>
void BidirectionalList<ValueType>::PushFront(ValueType id) {
	if (size_ == 0) {
		shared_ptr<Element> new_top(new Element);
		new_top->SetId(id);

		top_element_ = new_top;
		top_element_->SetNextElement(nullptr);
		front_element_ = new_top;
		front_element_->SetPrevousElement(nullptr);
		size_++;
		return;
	}

	shared_ptr<Element> new_top(new Element);
	new_top->SetId(id);

	new_top->SetNextElement(front_element_);
	new_top->SetPrevousElement(nullptr);
	front_element_->SetPrevousElement(new_top);

	front_element_ = new_top;

	size_++;
}

// Removes first found copy of element from front!
template<typename ValueType>
void BidirectionalList<ValueType>::DeleteElement(ValueType id) {
	auto current_element = front_element_;

	//if its first element, we should change front_element
	if (current_element->GetId() == id) {
		PopFront();
		return;
	}

	while (current_element->GetNextElement()) {
		if (current_element->GetId() == id) {

			if (current_element->GetPrevousElement()) {
				current_element->GetPrevousElement()->SetNextElement(current_element->GetNextElement());
			}
			if (current_element->GetNextElement()) {
				current_element->GetNextElement()->SetPrevousElement(current_element->GetPrevousElement());
			}
			size_--;
			return;
		}
		current_element = current_element->GetNextElement();
	}

	//if its last element, we should change top_element

	if (top_element_->GetId() == id) {

		PopBack();
		return;
	}
}



template<typename ValueType>
inline void BidirectionalList<ValueType>::PopFront() {
	auto current_element = front_element_;
	if (current_element->GetNextElement()) {
		current_element->GetNextElement()->SetPrevousElement(current_element->GetPrevousElement());
	}
	front_element_ = move(current_element->GetNextElement());
	size_--;
	return;

}

template<typename ValueType>
inline void BidirectionalList<ValueType>::PopBack() {
	auto current_element = top_element_;
	if (current_element->GetPrevousElement()) {
		current_element->GetPrevousElement()->SetNextElement(current_element->GetNextElement());
	}
	top_element_ = move(top_element_->GetPrevousElement());
	size_--;
	return;
}

template<typename ValueType>
bool BidirectionalList<ValueType>::Find(ValueType id) {
	auto current_element = front_element_;

	while (current_element != top_element_) {
		if (current_element->GetId() == id) {
			return true;
		}
		current_element = current_element->GetNextElement();
	}
	if (current_element->GetId() == id)
		return true;
	return false;
}

template<typename ValueType>
inline void BidirectionalList<ValueType>::PrintList() {
	shared_ptr<Element> current_element = front_element_;
	while (current_element->GetNextElement()) {
		std::cout << current_element->GetId() << " ";
		current_element = current_element->GetNextElement();
	}
	std::cout << top_element_->GetId() << endl;
}


template<typename ValueType>
inline void BidirectionalList<ValueType>::Element::SetId(ValueType id) {
	this->id_ = id;
}

template<typename ValueType>
inline void BidirectionalList<ValueType>::Element::SetNextElement(shared_ptr<Element> next) {
	this->next_element_ = std::move(next);
}

template<typename ValueType>
inline void BidirectionalList<ValueType>::Element::SetPrevousElement(shared_ptr<Element> prevous) {
	this->prev_element_ = std::move(prevous);
}
