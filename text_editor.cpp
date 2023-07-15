#include"text_editor.h"
#include <assert.h>
#include<string>
#include <sstream>
using namespace std;
template <class T>
Node<T>::Node()
{
	value = 0;
	next = 0;
}

template <class T>
Node<T>::Node(T val)
{
	value = val;
	next = 0;
}
template <class T>
text_editor<T>::text_editor(void)
{
	head = tail = 0;
	count = 0;
}
template <class T>
int text_editor<T>::size()
{
	return count;
}
template <class T>
void text_editor<T>::Add(T val)
{
	Node<T>* newNode = new Node<T>(val);
	if (head == 0)
		head = tail = newNode;
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
	count++;
}
template <class T>
T text_editor<T>::get_line(int pos)
{
	assert(pos >= 0 && pos<count);
	Node<T>* tmp = head;
	for (int i = 0; i<pos; i++)
		tmp = tmp->next;
	return tmp->value;
}

template <class T>
void text_editor<T>::Insertline(int pos, T val)
{
	assert(pos >= 0 && pos<count);
	Node<T>* tmp = head;
	Node<T>* newNode = new Node<T>(val);
	if (pos == 0)
	{
		newNode->next = head;
		head = newNode;
	}
	else
	{
		for (int i = 0; i < pos-1 ; i++)
			tmp = tmp->next;

		newNode->next = tmp->next;
		tmp->next = newNode;
	}
	count++;
}

template <class T>
void text_editor<T>::Deleteline(int pos)
{
	assert(pos >= 0 && pos<count);
	Node<T>* tmp = head;
	if (pos == 0)
	{
		head = head->next;
		delete tmp;
	}
	else
	{
		for (int i = 0; i<pos - 1; i++)
			tmp = tmp->next;
		Node<T>* del = tmp->next;
		tmp->next = del->next;
		delete del;
		if (pos == count - 1)
			tail = tmp;
	}
	count--;
}
template <class T>
void text_editor<T>::update(int pos, T val) //takes number of a line and update it with a new line 
{
	assert(pos >= 0 && pos < count);
	Node<T>* tmp = head;
	Node<T>* newNode = new Node<T>(val);
	if (pos == 0)
	{
		head->value = val;
	}
	else
	{
		for (int i = 0; i < pos; i++)
			tmp = tmp->next;

		newNode = tmp->next;

		tmp->value = val;
	}

}
template <class T>
void text_editor<T>::find(T word) //takes a word and display it's position 
{
	Node<T>* tmp = head;
	bool enter = false;
	string str;
	int line = 1;
	while (tmp) //breaks when there is a null
	{
		stringstream ss(tmp->value);
		while (ss >> str) //takes word by word in ss and puts it in str
		{
			if (str.compare(word) != std::string::npos) //compare word with str
			{
				cout << " Found \"" << word << "\" at line: " << line << endl;
				enter = true;
				if (line == line)
					break;
			}
		}
		tmp = tmp->next;
		line++;
	}
	if (enter == false)
	{
		cout << " This line doesn`t exist in the text." << endl;
	}
}
template <class T>
void text_editor<T>::findandreplace(T word1, T word2) //find a word and replace it with another
{
	Node<T>* tmp = head;
	string str;
	int line = 1;
	while (tmp)
	{
		stringstream ss1;
		stringstream ss(tmp->value);
		while (ss >> str){
			if (str.find(word1) != std::string::npos)
			{
				ss1 << word2 << " "; //puts the second word in ss1
			}
			else{
				ss1 << str << " "; //puts str in ss1
			}
		}
		tmp->value = ss1.str(); 
		tmp = tmp->next;
		line++;
	}
}
template <class T>
void text_editor<T>::swaplines(T val, int pos) //takes position of a line and the text of another line and swaps them
{
	Node<T> * tmp = head;
	Node<T>*swap = head;
	int c = 0;
	int n = 0;
	T v;
		while (tmp != NULL&& tmp->value != val)
		{
			tmp = tmp->next;
			c++;
		}
		if (tmp == NULL)
		{
			cout << " This line doesn`t exist in the text.\n";
		}
		else
		{
			int x = c;
			Deleteline(c);
			if (pos == count)
			{
			Add(val);
			for (int i = 0; i < pos - 1; i++)
			{
			swap = swap->next;
			v = swap->value;
			n++;
			}
			}
			else
			{
			Insertline(pos, val);
			for (int i = 0; i < pos+1 ; i++)
			{
			if (pos == 0)
			{
			v = swap->value;
			swap = swap->next;
			}
			else
			{
			swap = swap->next;
			v = swap->value;
			}
			n++;
			}
			}
			Deleteline(n);
			if (x == count)
			{
			Add(v);
			}
			else
			{
			Insertline(x, v);
			}
			}
}
template <class T>
void text_editor<T>::display() {
	for (int i = 0; i<count; i++)
		cout << " "<<get_line(i) << endl;
	if (count == 0)
	{
		cout << " No lines to display.\n";
	}
}
template <class T>
void text_editor<T>::clear()
{
	Node<T>*p = head;
	int n=0;
	while (p != NULL)
	{
		p = head->next;
		Deleteline(n);
		n++;
		if (n >= count)
		{
			break;
		}
	}
	count = 0;
}
template <class T>
text_editor<T>::~text_editor(void)
{
}