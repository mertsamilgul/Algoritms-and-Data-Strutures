#include <iostream>
using namespace std;

template <typename  Key>
class Ring
{
    class Node
    {
        Key data;
        Node *next; // pointer of next element
        Node *prev; // pointer of previous element
        friend class Ring;
    };

    Node* first; // pointer of the first element

public:

    Ring() { first=NULL; }
    ~Ring(){ clear(); }

    const Ring<Key> &operator=(const Ring<Key> &i)
    {
        if(this==&i)
            return *this; // if same object return itself

        clear(); // clearing ring before assignment

        if(i.is_empty()) // if its empty return itselt(already cleared)
            return *this;

        Node *j=i.first; // get first element
        do{
            push(j->data);
            j=j->next;
        }while(j!=i.first); // scaning all of the ring

      return *this;
    }

    Ring(const Ring<Key> & i) { first=NULL; *this=i; }

    bool operator==(const Ring<Key> &i)
    {
        if(is_empty()&&i.is_empty()) // both empty, so equal
            return true;
        if(this->size()!=i.size()) // different size, not equal
            return false;

        Node *j=first;
        Node *k=i.first;

        do
        {
            if(j->data!=k->data) // if one node is different
                return false;    // return false
            j=j->next; k=k->next;
        }while(j!=first);

     return true; // every node is same return true
    }

    bool operator!=(const Ring<Key> &i)
    {
        return !(*this==i); // opposite of operator==
    }

    class Iterator
    {
        Node* ptr;  // pointer of the node
    public:
        friend class Ring;
        Iterator():ptr (first){}
        Iterator(Node* pNode):ptr(pNode){}
        Iterator(const Iterator & original) : ptr(NULL) {*this = original;};
        const Iterator& operator=(const Iterator & it)
        {
            this->ptr = it.ptr;
            return *this;
        }
        Iterator& operator--()
        {
            if (ptr)
                ptr = ptr->prev;  // pointer points previous element
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator iter = *this;
            --*this;
            return iter;
        }
        Iterator& operator++()
        {
            if (ptr)
                ptr = ptr->next;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator iter = *this;
            ++*this;
            return iter;
        }
        bool operator==(const Iterator &iter) const
        {
            return ptr==iter.ptr;
        }
        bool operator!=(const Iterator &iter) const
        {
            return ptr!=iter.ptr;
        }
        const Key &operator*() const
        {
            return ptr->data;
        }
        Iterator operator+(int i)
        {
            for (int j=0;j<i;j++)
                ptr=ptr->next;
            return *this;
        }
        Iterator operator-(int i)
        {
            for (int j=0;j<i;j++)
                ptr=ptr->prev;
            return *this;
        }
    };

    bool insert(const Key &data,Iterator &it)
    {
        if(it==NULL)
            return false;   // no element to insert

        Node *i=it.ptr;
        Node *j=new Node;
        j->data=data;

        j->next=i->next;
        i->next->prev=j;
        j->prev=i;
        i->next=j;
        return true;
    }

    bool remove(Iterator &it)
    {
        if(it==NULL)  // no element to remove
            return false;
        Node *i=it.ptr;
        if(i->next==i) // only 1 element in the ring
        {
            delete i; // delete the only node
            first=NULL; // now ring is empty
            it=NULL;
            return true;
        }
        it++;
        i->next->prev=i->prev;
        i->prev->next=i->next;
        if(i==first) first=i->next; // if removing first change it
        delete i;
        return true;
    }

    void clear()
    {
        if(is_empty()) return; // already empty
        Node *i=first;
        Node *j=first->prev; // j=last element
        while(i!=j)
        {
            i=i->next;
            delete first;
            first=i;
        }
        delete j;
        first=NULL;
    }

    bool is_empty() const
    {
        return !first; // if first is NULL return true, else false
    }

    void push(Key data)
    {
        Node *i=new Node; // creating new node
        i->data=data;
        if(is_empty()) // if ring is empty i is the first element
        {
            first=i;
            first->next=i;
            first->prev=i;
            return;
        }
        first->prev->next=i;
        i->prev=first->prev;
        i->next=first;
        first->prev=i;
    }

    void push_reverse(Key data)
    {
        Node *i=new Node;
        i->data=data;
        if(is_empty())
        {
            first=i;
            first->next=i;
            first->prev=i;
            return;
        }
        first->next->prev=i;
        i->next=first->next;
        i->prev=first;
        first->next=i;
    }

    void display()
    {
        if(is_empty())
        {
            cout << "Ring is empty" << endl;
            return;
        }
        Node *i=first;
        do
        {
            cout << i->data << " ";
            i=i->next;
        }while(i!=first);
        cout << endl;
    }

    int size() const
    {
        int c=0;
        Node *i=first;
        do
        {
            i=i->next;
            c++;        // count number of elements
        }while(i!=first);
        return c; // return number of elements
    }

    Iterator begin()
    {
        return Iterator(first);
    }

    Iterator end()
    {
        return Iterator(first->prev);
    }

    Iterator find(const Key data)
    {
        Iterator it=begin();
        if(!is_empty())
        {
            do
            {
                if(*it==data)
                    return it; // if found return iterator
                it++;
            }while(it.ptr!=first);
        }
        return NULL; // empty or not found
    }
};
template <typename Key>
void Split(Ring<Key> &a,Ring<Key> &result1,bool b1,int a1,Ring<Key> &result2,bool b2,int a2)
{
    // first, check if rings are empty if not delete all elements
    if(!result1.is_empty())
        result1.clear();
    if(!result2.is_empty())
        result2.clear();

    // Ring<Key>::Iterator was an error so I put typename
    typename Ring<Key>::Iterator iter1=a.begin(); // first Iterator points first element of the ring
    typename Ring<Key>::Iterator iter2=a.begin()+1; // second Iterator points second element of the ring

    for(int i=0;i<a1;i++,iter1=iter1+2)
    {
        if(b1) // if bool b1 is true push elements clockwise
            result1.push(*iter1);
        else // if not push elements anti-clockwise
            result1.push_reverse(*iter1);
    }
    for(int i=0;i<a2;i++,iter2=iter2+2)
    {
        if(b2)
            result2.push(*iter2);
        else
            result2.push_reverse(*iter2);
    }
}

int main()
{
    Ring<int> ring1,result1;

    ring1.push(1);
    ring1.push(2);
    ring1.push(3); // pushing some elements into the ring
    ring1.push(4);
    ring1.push(5);

    cout << "Size of the ring: " << ring1.size() << endl;

    Ring<int> result2=ring1; //copy cons

    result2.display();

    result1=ring1; // assignment op

    result1.display();

    result1.clear(); // clearing ring

    result1.display(); // displaying empty ring

    result1.push_reverse(1);
    result1.push_reverse(2);
    result1.push_reverse(3); // pushing some elements anti-clockwise
    result1.push_reverse(4);
    result1.push_reverse(5);

    result1.display();

    Ring<int>::Iterator it=ring1.begin();
    do
    {
        cout << *it << " "; // printing elemets with iterator
        it++;
    }while(it!=ring1.begin());
    cout << endl;

    Ring<int>::Iterator it2=ring1.find(3);

    ring1.remove(it2); // removes 3 from ring

    ring1.display();

    it2=ring1.find(2);

    ring1.insert(3,it2); // adds 3 again to the ring

    ring1.display();

    it2=ring1.end();
    cout << *it2 << endl;
    it=it2--;
    cout << *it << " " << *it2 << endl;
    it=--it2;
    cout << *it << " " << *it2 << endl;

    ////////////////////////////////////

    cout << endl << endl;

    Split(ring1,result1,true,5,result2,false,3);

    ring1.display();
    result1.display();
    result2.display();

    return 0;
}
