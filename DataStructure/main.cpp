#include <iostream>
#include "node.h"

using namespace std;

class dnode
{
public:
    typedef double value_type;
private:
    value_type data_field;
    dnode       *link_fore;
    dnode       *link_back;
};//Class for doubly link node


class node
{
public:
    typedef double value_type;

    node (const value_type& init_data = value_type(), node* init_link=NULL)
    {
        data_field= init_data;
        link_field= init_link;
    }
    
    void set_data(const value_type& new_data);
    void set_link(node* new_link)
    {
        
    }
    value_type data() const;
    const node* link() const{return link_field;}
    node* link(){return link_field;}
    
private:
    value_type data_field;
    node *link_field;
    node *head_ptr;
    node *tail_ptr;
};

size_t list_length(const node* head_ptr)
{
    size_t answer=0;
    const node *cursor;
    for(cursor = head_ptr;cursor!=NULL;cursor=cursor->link())
        ++answer;
    return answer;
};


node* list_search(node* head_ptr, const node::value_type& target)
{
    node* cursor;
    for(cursor=head_ptr;cursor!= NULL;cursor=cursor->link())
        if(target==cursor->data())  return cursor;
    return NULL;
}

const node* list_search(const node* head_ptr, const node::value_type& target)
{
    const node* cursor;
    for(cursor=head_ptr;cursor!= NULL;cursor=cursor->link())
        if(target==cursor->data())  return cursor;
    return NULL;
}

node* list_locate(node* head_ptr, size_t position)
{
    node* cursor = head_ptr;
    size_t i;
    assert(0<position);
    for(i=1;(cursor!= NULL && i<position);++i)
        cursor = cursor->link();
    return cursor;
}
const node * list_locate(const node* head_ptr, size_t position)
{
    const node* cursor = head_ptr;
    size_t i;
    assert(0<position);
    for(i=1;(cursor!= NULL && i<position);++i)
        cursor = cursor->link();
    return cursor;
}

void list_insert(node* previous_ptr,const node::value_type& entry)
{
    node* insert_ptr;
    insert_ptr = new node;
    insert_ptr-> set_data(entry);
    insert_ptr->set_link(previous_ptr->link());
    previous_ptr->set_link(insert_ptr);
}

void list_head_insert(node*& head_ptr, const node:: value_type& entry)
{
    head_ptr = new node(entry,head_ptr);
}

void list_head_remove (node* head_ptr)
{
    node* remove_ptr;
    remove_ptr = head_ptr;
    head_ptr = head_ptr->link();
    delete remove_ptr;
}

void list_remove(node* previous_ptr)
{
    node* remove_ptr;
    remove_ptr = previous_ptr-> link();
    delete remove_ptr;
}
void list_clear(node*& head_ptr)
{
    while(head_ptr !=NULL)
        list_head_remove(head_ptr);
}

void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
{
    head_ptr=NULL;      tail_ptr=NULL;
    if(source_ptr==NULL)    return;
    list_head_insert(head_ptr, source_ptr->data());
    tail_ptr=head_ptr;
    source_ptr=source_ptr->link();
    while (source_ptr!=NULL)
    {
        list_insert(tail_ptr, source_ptr->data());
        tail_ptr = tail_ptr->link();
        source_ptr=source_ptr->link();
    }
}




class bag
{
public:
    typedef std::size_t size_type;
    bag();
    bag(const bag& source);
    ~bag();
    typedef double value_type;

    
public:
    void operator = (const bag& source);
    void operator += (const bag& addend);
    void operator + ();//have to write below operator myself
    void operator ==(const bag& source);
    void operator != (const bag& source);
    
public:
    bool erase_one(const value_type& target);
    size_type count(const value_type& target) const;
    void insert(const value_type& entry);
    void show_contents() const;
  
private:
    node* head_ptr;
    size_type many_nodes;
};

bag::bag()
{
    head_ptr=NULL;
    many_nodes=0;
}
bag::bag(const bag& source)
{
    node *tail_ptr;
    list_copy(source.head_ptr, head_ptr, tail_ptr);
}
bag::~bag()
{
    list_clear(head_ptr);
    many_nodes = 0;
}
void bag::operator=(const bag& source)
{
    node* tail_ptr;
    if(this == & source)
        return;
    list_clear(head_ptr);
    list_copy(source.head_ptr, head_ptr, tail_ptr);
    many_nodes=source.many_nodes;
}
void bag::operator+=(const bag& addend)
{
    node* copy_tail_ptr;
    node* copy_head_ptr;
    
    if(addend.many_nodes>0)
    {
        list_copy(addend.head_ptr, copy_tail_ptr, copy_head_ptr);
        copy_tail_ptr-> set_link(head_ptr);
        head_ptr = copy_head_ptr;
        many_nodes+=addend.many_nodes;
    }
}

bool bag::erase_one(const value_type &target)
{
    node* target_ptr;
    target_ptr   = list_search(head_ptr, target);
    if(target_ptr == NULL)
        return false;
    target_ptr->set_data(head_ptr->data());
    list_head_remove(head_ptr);
    --many_nodes;
    return true;
}

void bag::insert(const value_type &entry)
{
    list_head_insert(head_ptr, entry);
    ++many_nodes;
}

bag::size_type bag::count (const value_type & target) const
{
    size_type answer = 0;
    const node* cursor;
    cursor = list_search(head_ptr, target);
    
    while(cursor!=NULL)
    {
        ++answer;
        cursor = cursor->link();
        cursor = list_search(cursor, target);
    }
    return answer;
}

void bag::show_contents() const
{
    /*while()
    {
        
    }*/
    std::cout << " "<<endl;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    node *nodeList = new node();
    bag *test=  new bag();
    int testVar;
    
    
    nodeList->set_data(8);
    nodeList->set_data(9);
    nodeList->set_data(4);
    nodeList->set_data(2);
   
    
    
    
    
    
    return 0;
    
   
}
