/*################################################################
# list.cc                                                        #
# Muhammad Najib                                                 #
# Project 4 Lists                                                #
# 4 March 2015                                                   #
# This program provides a class called 'list', which creates a   #
# doubly-linked  list and provides functions to manipulate list  #
# such as adding, removing, searching items or nodes in list etc.#
################################################################*/

#include "list.h"
#include <iostream>
using namespace std;

// List node constructors

list_node::list_node() : prev(NULL), next(NULL) {}

list_node::list_node(list_node *p, list_node *n) : prev(p), next(n) {}

list_node::list_node(list_node *p, const list_element & d, list_node * n):
  prev(p), data(d), next(n) {}

// List constructors/destructor/assignment

list::list() 
{
  _init();
}

list::~list()
{
  _destroy();
}

list::list(const list & orig)
{
  _copy(orig);
}

list & list::operator=(const list & rhs)
{
  if (this != &rhs) {
    _destroy();
    _copy(rhs);
  }
  return *this;
}

//_init func to initialize the list
//vaiables _size and _current initialized to zero
//_front and _rear sentinels created
//_current points to _rear sentinel initially
void list::_init()
{
  _size = 0;
  _current_index = 0;
  _front = new list_node();
  _current = _rear = new list_node(_front,NULL);
  _front -> next = _rear;
}


//copy constructor created 
//same _init func to initialize list
//creates a temp pointer to orig list
//temp moves along the list and provides
//data to add func of new list
void list::_copy(const list & orig)
{
  _init(); 
  list_node* temp = orig._front->next;

  if(temp-> next == NULL) return;
 
  for( ; temp -> next != orig._rear; temp = temp -> next)
    add(temp -> data,0);     
   
}


//_destroy func used by destructor
//removes node at zero index until all eliminated
void list::_destroy()
{

  if(size() == 0) return;
  
  for(_set_current_index(0) ; size() > 0; remove_at(0));
             
}

//add func to add new node with item at certain index
//new node created with nodes before and at index doubly
//linked to the new node. _current adjusted
void list::add(const list_element & item, size_t index)
{
  _set_current_index(index);
  
  //special case of index == 0 due to _front sentinel
  if (index == 0)
    {

      list_node* new_member = new list_node(_front, item , _current);
     
      _current -> prev = new_member;
      _front -> next = new_member;
      _current = new_member;
      _size++;
     
      return;
      }
 
  //for all other cases
  list_node* new_member = new list_node(_current -> prev , item , _current);

  _current -> prev = new_member;
   new_member -> prev -> next = new_member;  
  _current = new_member;
  _size++;
      
}

//func removes node at given index
//creates a new pointer to node at given index
//current moves to next node and doubly linked to 
//node before index. Newly created pointer deletes 
//node at index.
void list::remove_at(size_t index)
{

  if(index >= size())
    return;

  _set_current_index(index);

  list_node * removable ; removable = _current;

  _current = _current -> next;
  _current -> prev = removable -> prev;
  _current -> prev -> next = _current;
  delete removable;
  _size = _size -1; 

  return;
}


//func finds and removes given item at lowest index
void list::remove(const list_element & item)
{ 
 
  _set_current_index(0);

  //while loop moves _current pointer until item found
  while (_current_index < size())
    {
      if(get(_current_index) == item)
	break;
        
      _current_index ++;
      _current = _current -> next;  
    } 

  //if not found, set current_index to zero and return
  if ( _current_index == size())
    {
      _set_current_index(0);
      return;
    }

  //once index found, same as remove_at
  list_node * removable = _current;

  _current = _current -> next;
  _current -> prev = removable -> prev;
  _current -> prev -> next = _current;

  delete removable;
  _size = _size - 1;

  return;
}

//return index of item for lowest index
//while loop moves _current from first to last node
//if data equals item, idex returned
//else size of list returned
size_t list::find(const list_element & item) const
{
  _set_current_index(0);
 
  while (_current_index < size())
    {
      if ( _current -> data == item)
	return _current_index;
      
      _current = _current -> next;
      _current_index++;
    } 

  _set_current_index(0);
 
  return size();

}

//get func returns data from node at said index
list_element list::get(size_t index) const
{
  _set_current_index(index);
  return _current -> data; 
}

//returns private variable _size of list
size_t list::size() const
{
  return _size;
}

//outputs list using ostream operator
void list::output(std::ostream & ostr) const
{
  size_t i =0;
  ostr <<"<";

  for (; i < size(); i++)
    {
      if(i !=  size()-1)
	ostr<<get(i)<<", ";

      else
	ostr<<get(i);
    }

  ostr<<'>';

}

//sets current index to given index
//while loop moves _current pointer until index equals _current_index
void list::_set_current_index(size_t index) const
{

  while (_current_index != index)
    {
      if ( index < _current_index)
	{
	  _current = _current -> prev;
	  _current_index = _current_index - 1;       	
	}

      else
	{
	  _current = _current -> next;
          _current_index = _current_index + 1;
        }

    }
}
