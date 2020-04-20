#include <iostream>
using namespace std;
template <typename Key,typename Info>
class Sequence{
    typedef struct Node
    {
        Info data;
        Key key;
        Node *next;
    }*node;
    node first;
    node last;
    int numberOfElements;
public:
    Sequence() // Constructor
    {
        first=NULL; // Creates an empty list
        last=NULL;
        numberOfElements=0;
    }
    ~Sequence() // Destructor
    {
        clear();
    }
    Sequence(const Sequence<Key,Info> &x) // Copy Constructor
    {
        node i,j=x.first;
        while(j)
        {
            pushFront(j->data,j->key);
            i=j;
            j=j->next;
        }
        last=i;
    }
    Sequence<Key,Info> &operator=(const Sequence<Key,Info> &x) // Assignment Operator
    {
        if(this==&x)
            return *this;
        clear();

        node j=x.first;
        while(j)
        {
            pushFront(j->data,j->key);
            j=j->next;
        }
        return *this;
    }
    bool operator==(const Sequence<Key,Info> &x) // Comparison Operator
    {

        node i=first;
        node j=x.first;

        if(!i&&!j) return 1; // If both are empty return true

        while(i && j)
        {
            if((i->data!=j->data) || (i->key!=j->key)) break; // If any of the nodes arent same no need to check others
            i=i->next; j=j->next;
        }
        if(i || j) return 0;
        return 1;
    }
    bool operator!=(const Sequence<Key,Info> &x)
    {
        return !(*this==x);
    }
    bool pushFront(Info data,Key key) // Pushes the given element as the last one
    {
        node i=new Node;
        if(!i) {cout << "Cant Allocate Memory"; return 0;}
        i->data=data;
        i->key=key; // Creating new node with given key and info.
        i->next=NULL;
        if(first==NULL)
        {
            first=i;
            last=i; // If list is empty first element will be the new created one.
            numberOfElements++;
            return 1;
        }
        last->next=i;
        last=i;
        numberOfElements++;
        return 1;
    }
    bool pushBack(Info data,Key key) // Pushes the given elemeny as the first one
    {
        node i=new Node;
        if(!i) {cout << "Cant Allocate Memory"; return 0;}
        i->data=data;
        i->key=key;
        if(first==NULL)
        {
            i->next=NULL;
            first=i;
            last=i;
            numberOfElements++;
            return 1;
        }
        i->next=first;
        first=i;
        numberOfElements++;
        return 1;
    }
    node findElement(int pos) const // Finds the element with given position
    {
        if(pos>numberOfElements-1) return NULL; // There are no elements in this position
        node i=first;
        for(int j=0;j<pos;j++)
            i=i->next;
        return i;
    }
    bool removeByKey(Key key) // Removes all elements with the given key
    {
        bool p=0;
        node i=first;
        if(!i) return 0; // Empty List
        if(i->key==key) // If the first has the given key
        {
            first=first->next;
            delete i;
            p=1;
        }
        i=first;
        while(i->next)
        {
            if(i->next->key==key)
            {
                if(i->next==last) last=i;
                node tmp=i->next;
                i->next=i->next->next;
                delete tmp;
                p=1;
            }
            i=i->next;
        }
        return p;
    }
    bool removeByInfo(Info data) // Removes all elements with the given info
    {
        node i=first;
        if(!i) return 0; // Empty List
        bool p=0;
        if(i->data==data)
        {
            first=first->next;
            delete i;
            p=1;
        }
        i=first;
        while(i->next)
        {
            if(i->next->data==data)
            {
                if(i->next==last) last=i;
                node tmp=i->next;
                i->next=i->next->next;
                delete tmp;
                p=1;
            }
            i=i->next;
        }
        return p;
    }
    bool removeByPos(int pos) // Removes the element with the given position
    {
        if(pos>numberOfElements-1) return 0;
        node i=first;
        if(pos==0)
        {
            first=first->next;
            delete i;
            return 1;
        }
        i=findElement(pos-1);
        if(i->next==last) last=i;
        node tmp=i->next;
        i->next=i->next->next;
        delete tmp;
        return 1;
    }
    int NumberOfElements() const // Returns number of elements in the list
    {
        return numberOfElements;
    }
    bool isEmpty() // Returns true if empty false if not
    {
        return !first;
    }
    void clear() // Deletes all the elements in the list
    {
        node i=first;
        while(i)
        {
            i=i->next;
            delete first;
            first=i;
        }
        last=NULL;
    }
    void print() // Prints the whole list with spaces between elements
    {
        if(isEmpty()) {cout << "Empty Sequence" << endl; return; }
        node i=first;
        while(i)
        {
            cout << i->data << " ";
            i=i->next;
        }
        cout << endl;
    }
};
template <typename Key,typename Info>
Sequence<Key,Info> produce(const Sequence<Key,Info> &s1,int start1,int len1,const Sequence<Key,Info> &s2,int start2,int len2,int limit)
{
    Sequence<Key,Info> s3;
    int len1_=0,len2_=0;
    for(int i=0;i<limit;i++)
    {
        if(len1_!=len1)
        {
            if(start1==s1.NumberOfElements()) start1=0;
            s3.pushFront(s1.findElement(start1)->data,s1.findElement(start1)->key);
            len1_++; start1++;
            continue;
        }
        if(len2_!=len2)
        {
            if(start2==s2.NumberOfElements()) start2=0;
            s3.pushFront(s2.findElement(start2)->data,s2.findElement(start2)->key);
            len2_++; start2++;
            if(len2_==len2)
            {
                len2_=0; len1_=0;
            }
        }
    }
    return s3;
}
int main()
{
    Sequence<int,int> s1,s2,s3;

    s1.print();// Trying to print empty list

    s1.pushFront(20,6);
    s1.pushFront(30,5);
    s1.pushBack(10,7);

    s1.print(); // Printing list with 3 elements

    if(s1.isEmpty()) cout << "Empty List";
    else cout << "Sequence is not empty" << endl;

    s3=s1;
    s3.print(); // Printing s3 which is equal to s1

    if(s1==s3) { cout << "Same Sequence" << endl;}


    s1.clear();
    s2.clear();
    s1.pushFront(10,1);
    s1.pushFront(20,1);
    s1.pushFront(30,2);
    s1.pushFront(40,1);
    s1.pushFront(50,1);
    s1.pushFront(60,1);
    s1.pushFront(70,9);
    s1.pushFront(80,5);

    s1.print();

    s2.pushFront(1,1);
    s2.pushFront(2,2);
    s2.pushFront(3,3);
    s2.pushFront(4,4);
    s2.pushFront(5,5);
    s2.pushFront(6,6);
    s2.pushFront(7,7);
    s2.pushFront(8,8);
    s2.pushFront(9,9);
    s2.print();

    s3=produce(s1,2,2,s2,1,3,11); // Same example we did in the first lab
    s3.print();
    return 0;
}
