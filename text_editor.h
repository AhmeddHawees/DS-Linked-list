#pragma once
#include<string>
template <class T>
class Node
{
public:
	Node<T>* next;
	T value;

	Node();
	Node(T val);
};
template <class T>
class text_editor
{
    int count;
	Node<T>* head;
	Node<T>* tail;
public:
	text_editor();
	int size();
	void clear();
	T get_line(int);
	void Insertline(int, T);
	void Add(T);
	void Deleteline(int);
	void update(int, T);
	void find(T);
	void findandreplace(T, T);
	void  swaplines(T,int);
	void display();
	~text_editor(void);
};
