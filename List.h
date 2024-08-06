#ifndef CUSTOM_LIST_H
#define CUSTOM_LIST_H
#include <iostream>

template<typename K, typename V>
class Entry{
private:
	K _key;
	V _value;
public:
	Entry(const K& k = K(), const V& v = V()): _key(k), _value(v) {}
 	const K& key() const {return _key;}
 	const V& value() const {return _value;}
	void setKey(const K& k) {_key = k;}
	void setValue(const V& v) {_value=v;}
};

template <typename T>
class List{

private:
  struct Node
  {
    T data;
    Node* next;
    Node* prev;
  };

public:
  class Iterator{
  public:
    T& operator*();
    bool operator==(const Iterator& p) const;
    bool operator!=(const Iterator& p) const;
    Iterator& operator++();
    Iterator& operator--();
    friend class List;

  private:
    Node* v;
    Iterator(Node* u);
  };

public:
  List();
  int size() const;
  bool empty() const;
  Iterator begin() const;
  Iterator end() const;
  void insertFront(const T& e);
  void insertBack(const T& e);
  void insert(const Iterator& p, const T& e);
  void eraseFront();
  void eraseBack();
  void erase(const Iterator& p);

private:
  int n;
  Node* head;
  Node* tail;
};

//Iterator methods
template<typename T>List<T>::Iterator::Iterator(typename List<T>::Node* u){v = u;}
template<typename T>T& List<T>::Iterator::operator*(){return v->data;}
template<typename T>bool List<T>::Iterator::operator==(const Iterator& p)const{return v == p.v;}
template<typename T>bool List<T>::Iterator::operator!=(const Iterator& p)const{return v != p.v;}
template<typename T>typename List<T>::Iterator& List<T>::Iterator::operator++(){v = v->next; return *this;}
template<typename T>typename List<T>::Iterator& List<T>::Iterator::operator--(){v = v->prev; return *this;}

//List methods
template<typename T>List<T>::List(){
  n = 0;
  head = new Node;
  tail = new Node;
  head->next = tail;
  tail->prev = head;
}
template<typename T>int List<T>::size()const{return n;}
template<typename T>bool List<T>::empty()const{return n==0;}
template<typename T>typename List<T>::Iterator List<T>::begin()const{return Iterator(head->next);}
template<typename T>typename List<T>::Iterator List<T>::end()const{return Iterator(tail);}
template<typename T>void List<T>::insert(const Iterator& p, const T& e){
  Node* w = p.v;
  Node* u = w->prev;
  Node* v = new Node;
  v->data = e;
  v->next = w; w->prev = v;
  v->prev = u; u->next = v;
  n++;
}
template<typename T>void List<T>::insertFront(const T& e){insert(begin(),e);}
template<typename T>void List<T>::insertBack(const T& e){insert(end(),e);}
template<typename T>void List<T>::erase(const Iterator& p){
  Node* v = p.v;
  Node* w = v->next;
  Node* u = v->prev;
  u->next = w; w->prev = u;
  delete v;
  n--;
}
template<typename T>void List<T>::eraseFront(){erase(begin());}
template<typename T>void List<T>::eraseBack(){erase(--end());}

#endif
