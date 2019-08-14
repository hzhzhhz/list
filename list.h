#include <iostream>

template<class T>
class Node{
public:
    T _element;
    Node<T>* _next;
    Node(){
    }
    Node(const T & _data){
        this->_element=_data;
        this->_next=nullptr;
    }
    ~Node(){
        this->_next=nullptr;
    }
};

template <class T>
class List{
private:
    Node<T>* _first_ptr;
    size_t _length;
public:
    List(){
        _length=0;
        _first_ptr=nullptr;
    }
    List(const List& _temp_list){
        this->_length=_temp_list._length;
        if(this->_length==0){
            this->_first_ptr=nullptr;
        }
        else{
            Node<T>*sourceNode=_temp_list._first_ptr;
            this->_first_ptr=new Node<T>(sourceNode->_element);
            sourceNode=sourceNode->_next;
            Node<T>*targetNode=this->_first_ptr;
            while(sourceNode!=nullptr){
                targetNode->_next=new Node<T>(sourceNode->_element);
                targetNode=targetNode->_next;
                sourceNode=sourceNode->_next;
            }
            targetNode=nullptr;
        }
    }
    ~List(){
        while(_first_ptr!=nullptr){
            Node<T>* targetNode=_first_ptr->_next;
            delete _first_ptr;
            _first_ptr=targetNode;
        }
    }
    void insert(size_t theIndex,const T& _temp){
        if(theIndex<0||theIndex>_length){
            std::cout<<"error"<<std::endl;
        }
        if(theIndex==0){
            Node<T>*current_ptr=new Node<T>(_temp);
            current_ptr->_next=_first_ptr;
            _first_ptr=current_ptr;
        }
        else{
            Node<T>*temp_ptr=_first_ptr;
            for(size_t i=0;i<theIndex-1;i++){
                temp_ptr=temp_ptr->_next;
            }
            Node<T> *curr=new Node<T>(_temp);
            curr->_next=temp_ptr->_next;
            temp_ptr->_next=curr;
        }
        _length++;
    }
    void Delete(const size_t theIndex);
    void push_back(const T &temp);
    void pop_back();
    size_t size();
};

template<class T>
void List<T>::Delete(const size_t theIndex){
    if(theIndex<0||theIndex>_length-1){
        std::cout<<"index error"<<std::endl;
    }
    if(theIndex==0){
        Node<T>* temp_ptr=_first_ptr->_next;
        delete _first_ptr;
        _first_ptr=temp_ptr;
    }
    else if(theIndex==_length-1){
        Node<T>* temp_ptr=_first_ptr;
        for(size_t i=0;i<theIndex-1;i++){
            temp_ptr=temp_ptr->_next;
        }
        delete temp_ptr->_next;
        temp_ptr->_next=nullptr;
    }
    else{
        Node<T>* temp_ptr=_first_ptr;
        for(size_t i=0;i<theIndex-1;i++){
            temp_ptr=temp_ptr->_next;
        }
        Node<T> *current=temp_ptr->_next;
        delete temp_ptr;
        temp_ptr=current;
    }
    _length--;
}
template<class T>
void List<T>::push_back(const T &_temp){
    this->insert(0,_temp);
}
template<class T>
void List<T>::pop_back(){
    if(this->_length!=0)
        this->Delete(this->_length-1);
}
template<class T>
size_t List<T>::size(){
    return this->_length;
}