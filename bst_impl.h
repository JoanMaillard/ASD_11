//
// Created by Olivier Cuisenaire on 23.05.20.
//

#ifndef ASD1_LABS_2020_BST_IMPL_H
#define ASD1_LABS_2020_BST_IMPL_H

// fonctions récursives n'ayant pas à connaitre root

template<typename Key>
void bst<Key>::insert(Node<Key> *&r, Key const &k) {
        if (r == nullptr) {
            r = new Node<Key>{k, nullptr, nullptr};
        } else if (k == r->key) {
            // k already there : do nothing.
        } else if (k < r->key) {
            insert(r->left, k);
        } else { // k > r->key
            insert(r->right, k);
        }
    }

template<typename Key>
void bst<Key>::to_stream(Node<Key> *r, std::ostream &s) noexcept {
    if (r) {
        s << r->key;
        if (r->right or r->left) { // r has children
            s << "(";
            if (r->left) to_stream(r->left, s);
            else s << ".";

            s << ",";

            if (r->right) to_stream(r->right, s);
            else s << ".";

            s << ")";
        }
    }
}

// méthodes de la classe bst

template<typename Key>
bst<Key>::bst() : root(nullptr) {}

template<typename Key>
bst<Key>& bst<Key>::operator=(bst<Key> const &other) {
	bst<Key> temp(other);
	std::swap(root, temp.root);
	return *this;
}

template<typename Key>
bst<Key>::bst(bst<Key> const &other) {
	if (other.root == nullptr)
		return;
	root = new Node<Key>{other.root->key, other.root->left, other.root->right};
	newTreeFrom(root);
}

template<typename Key>
void bst<Key>::newTreeFrom(Node<Key>* currentNode) {
	if (currentNode->left != nullptr) {
		currentNode->left = new Node<Key>{currentNode->left->key,
									  currentNode->left->left,
									  currentNode->left->right};
		newTreeFrom(currentNode->left);
	}
	if (currentNode->right != nullptr) {
		currentNode->right = new Node<Key>{currentNode->right->key,
									   currentNode->right->left,
									   currentNode->right->right};
		newTreeFrom(currentNode->right);
	}
}

template<typename Key>
bst<Key>::~bst() {
    if (root == nullptr)
		return;
	deleteTreeFrom(root);
	delete root;
}

template<typename Key>
void bst<Key>::deleteTreeFrom(Node<Key>* currentNode) {
	if (currentNode->left != nullptr) {
		deleteTreeFrom(currentNode->left);
		delete currentNode->left;
	}
	if (currentNode->right != nullptr) {
		deleteTreeFrom(currentNode->right);
		delete currentNode->right;
	}
}

template<typename Key>
bool bst<Key>::contains(Key const& k) const noexcept {
	if (root == nullptr)
		return false;
	return contains(root, k);
}

template<typename Key>
bool bst<Key>::contains(Node<Key>* currentNode, Key const& k) const noexcept {
	if (k == currentNode->key)
		return true;
	else if (k < currentNode->key && currentNode->left != nullptr)
		return contains(currentNode->left, k);
	else if (k > currentNode->key && currentNode->right != nullptr)
		return contains(currentNode->right, k);

	return false;
}



template<typename Key>
void bst<Key>::insert(Key const& k) {
    insert(root, k);
}

template<typename Key>
void identer(Node<Key> *r, std::ostream &s,const std::string& prefix, bool estGauche, size_t hauter)
{

   if( r != nullptr )
   {
      std::string addPrefix = "";
      if(hauter > 1){
         s << prefix;
         s <<  "|_ " ;
         // print the value of the node
         addPrefix += (estGauche ? "|  " : "   ");
      }
      else if(hauter == 1){
         s <<  "|_ " ;
         addPrefix += (estGauche ? "|  " : "   ");
      }
      s << r->key << "\n";
      // enter the next tree level - left and right branch
      if(r->right != nullptr || r->left != nullptr ) {
         identer(r->left, s, prefix + addPrefix, true, hauter + 1);
         identer(r->right, s, prefix + addPrefix, false, hauter + 1);
      }
   }
   else{
      s << prefix <<"|_ .\n";
   }
}



template<typename Key>
void bst<Key>::display_indented(std::ostream &s) const noexcept {
    if(root == nullptr) return;
    std::string prefix="";
    identer(root,s,prefix,false,0);
}

template <typename Key>
std::ostream& operator<<(std::ostream& s, bst<Key> const& t)
{
    bst<Key>::to_stream(t.root, s);
    return s;
}

template<typename Fn, typename Key>
void croissant(Node<Key> *r, Fn f) {
   if (r != nullptr){
      croissant(r->left, f);
      f(r->key);
      croissant(r->right, f);
   }
}

template<typename Key>
template<typename Fn>
void bst<Key>::visit_in_order(Fn f) const {
   if(root != nullptr)
      croissant(root, f);
}

template<typename Key>
void linearizeTree(Node<Key>* node, Node<Key>*& L, size_t& n) {
   if (node != nullptr) {
      linearizeTree(node->right, L, n);
      node->right = L;
      L = node;
      n += 1;
      linearizeTree(node->left, L, n);
      node->left = nullptr;
   }
}

template<typename Key>
void bst<Key>::linearize() noexcept {
   size_t n = 0;
   Node<Key>* linearizedTree = nullptr;
   linearizeTree(this->root,linearizedTree, n);
   root = linearizedTree;
}

template<typename Key>
Node<Key>* arborize(Node<Key>*& node, Node<Key>*& L, size_t n){
   Node<Key>* r = node;
   if (n != 0){
      Node<Key>* rg = arborize(r,L,(n-1)/2);
      r = L;
      r->left = rg;
      L = L->right;
      r->right = arborize(r,L,n/2);
      return r;
   }
   else
      return nullptr;

}

template<typename Key>
void bst<Key>::balance() noexcept {
   size_t n = 0;
   Node<Key>* linearizedTree = nullptr;
   linearizeTree(root,linearizedTree,n);
   root = arborize(root,linearizedTree,n);
}

#endif //ASD1_LABS_2020_BST_IMPL_H
