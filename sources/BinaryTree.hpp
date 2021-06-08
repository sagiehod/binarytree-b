
#include <iostream>
#include <unordered_map>
#include <utility>      // std::pair, std::make_pair

// forward_list::push_front
#include <iostream>
#include <vector>
#include <map>
using namespace std;

namespace ariel {

template <typename T>
class BinaryTree {
private:




//node
class Node{
  public:
  T value;
  Node * left;
  Node * right;
  Node(T val):value(val),left(nullptr),right(nullptr){}
};


void copy(const Node& from, Node& to){
        if(from.left!=nullptr) {
                to.left = new Node(from.left->value);
                copy(*from.left,*to.left);
        }
        if(from.right!=nullptr) {
                to.right = new Node(from.right->value);
                copy(*from.right,*to.right);
        }
}
Node * find_n( T & find, Node * node){

        if(node == nullptr) {return nullptr;}
        if(node->value == find) {return node;}

        Node *  l  = find_n(find,node->left);

        if(l!=nullptr) {return l;}

        Node *  r  = find_n(find,node->right);

        return r;
}

//member
Node * root_tree;

map<T,Node *> map_tree;

public:
  BinaryTree() : root_tree(nullptr) {
  }
  //deep
  BinaryTree(const BinaryTree<T> & other){

      std::cout << "/* message */" << '\n';
          if(other.root_tree!=nullptr) {
                  root_tree = new Node(other.root_tree->value);
                  copy(*other.root_tree,*root_tree);
          }
  }

  //Shallow
  BinaryTree(BinaryTree<T> && other) noexcept {
    std::cout << "/* message */" << '\n';
          root_tree = other.root_tree;
          other.root_tree = nullptr;
  }
  //------Operators-----
   BinaryTree& operator=(BinaryTree other){
       std::cout << "/* message */" << '\n';
       if(this == &other){
           return *this;
       }
       if(root_tree != nullptr){
           delete this->root_tree;
       }
      root_tree = new Node(other.root_tree->value);
       copy(*other.root_tree,*this->root_tree);
       return *this;

   }

   BinaryTree& operator=(BinaryTree&& other) noexcept{
       std::cout << "/* message */" << '\n';
       *this->root_tree = other.root_tree;
   }

  ~BinaryTree() {};

BinaryTree& add_root(T x);
BinaryTree& add_left(T exsist,T insert_);
BinaryTree& add_right(T exsist,T insert_);

class it
{
private:

  void recu_in(Node* v){
    if(v == nullptr){return ;}
    recu_in(v->left);
    vec.push_back(v);
    recu_in(v->right);
  }
  void recu_pre(Node* v){
    if(v == nullptr){return ;}
    vec.push_back(v);
    recu_pre(v->left);
    recu_pre(v->right);
  }
  void recu_post(Node* v){
    if(v == nullptr){return ;}
    recu_post(v->left);
    recu_post(v->right);
    vec.push_back(v);
  }

public:
  Node * current;
  vector<Node*> vec;
  it():current(nullptr){}
  it(Node* temp):current(temp){}
  it(Node* root , char type){
    if(root != nullptr){
      if(type == 'i'){
        recu_in(root);
      }
      if(type == 'e'){
        recu_pre(root);
      }
      if(type == 't'){
        recu_post(root);
      }
      current = vec.at(0);
    }else{
      current =nullptr;
    }
  }

T &operator*() const {
        return current->value;
}

T *operator->() const {
        return &(current->value);
}

it &operator++(){
    if(vec.size()>1){
      vec.erase(vec.begin());
      current = vec[0];
    }else{
      current =nullptr;
    }
  return *this;
}

 it operator++(int){
          it temp(vec[0]);
          ++*this;
        return temp;
}

bool operator==(const it &other) const {
        return current == nullptr;
}

bool operator!=(const it &other) const {
        return !(*this == other);
}

};
it begin(){
  return it(root_tree,'i');

}
it end(){
  return it();
  }
it   begin_preorder(){
  return it(root_tree,'e');
}
it  end_preorder(){
  return it();
}
it   begin_inorder(){
  return it(root_tree,'i');
}
it   end_inorder(){
  return it();
}
it   begin_postorder(){
  return it(root_tree,'t');
}
it end_postorder(){

    return it();
}
friend ostream& operator<<(ostream& os,BinaryTree<T>& tree){


        for (auto& x: tree.map_tree){
            os << ' ' << x.first;
         }
        return os;
}
};
template <typename T>
BinaryTree<T>& BinaryTree<T>::add_root(T x){
  if(root_tree == nullptr){
    root_tree=new Node(x);
  }else{
    root_tree->value=x;
  }

            return *this;
    }
template <typename T>
BinaryTree<T>& BinaryTree<T>::add_left(T exsist,T insert_){

Node * found = find_n(exsist,root_tree);
  if(found==nullptr){  throw invalid_argument{" not exist"};}
  if(found->left ==nullptr){
    found->left = new Node(insert_);

  }else{
    found->left ->value = insert_;

  }
        return *this;
}
template <typename T>
BinaryTree<T>& BinaryTree<T>::add_right(T exsist,T insert_){
  Node * found = find_n(exsist,root_tree);
    if(found==nullptr){  throw invalid_argument{" not exist"};}
    if(found->right ==nullptr){
      found->right = new Node(insert_);

    }else{
      found->right ->value = insert_;

    }
          return *this;
}


}
