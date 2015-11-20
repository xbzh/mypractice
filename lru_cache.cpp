/*
 * 使用一个hash map和一个双向队列来实现简单的lru算法。
 * c++11之前，hash_map不在c++标准库中，而在ext中。
 * 当然也可以直接用map来替换hash_map。
 */

#include <iostream>
#include <vector>
#include <ext/hash_map>
using namespace std;
using namespace __gnu_cxx;

template<class K,class V>
struct Node 
{
	K key;
	V value;
	Node *next,*prev;	
};

template<class K,class V>
class LRUCache
{
public:
	LRUCache(size_t size)
	{
		entries = new Node<K,V>[size];	
		for(int i = 0; i < size; ++i)
			free_entries.push_back(entries+i);
		head = new Node<K,V>();
		tail = new Node<K,V>();
		head->prev = NULL;
		head->next = tail;
		tail->prev = head;
		tail->next = NULL;
	}
	
	~LRUCache()
	{
		delete head;
		delete tail;
		delete []entries;
		head = NULL;
		tail = NULL;
		entries = NULL;
	}
	
	void Put(K key,V value)
	{
		Node<K,V> * p = hash_map_[key];
		if(p)
		{
			detach(p);
			p->value = value;
			attach(p);
		}
		else
		{
			if(free_entries.size() > 0)
			{
				p = free_entries.back();
				free_entries.pop_back();
			}
			else
			{
				p = tail->prev;
				detach(p);
				hash_map_.erase(p->key);
			}

			p->key = key;
			p->value = value;
			hash_map_[key] = p;
			attach(p);
		}
	}
	V Get(K key)	
	{
		Node<K,V> * p = hash_map_[key];
		if(p)
		{
			detach(p);
			attach(p);
			return p->value;
		}
		else
			return V();
	}
protected:
	void detach(Node<K,V>* node)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;	
	}
	void attach(Node<K,V>* node)
	{
		node->prev = head;
		node->next = head->next;
		head->next->prev = node;
		head->next = node;
	}
private:
	Node<K,V> *entries;
	Node<K,V> *head,*tail;
	hash_map<K,Node<K,V> *> hash_map_;
	vector<Node<K,V> *> free_entries;
};

int main()
{
	LRUCache<int,string> lru(10);
	lru.Put(3,"abcd");	
	cout<<lru.Get(3);
	return 0;
}
