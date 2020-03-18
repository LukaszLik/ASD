#ifndef BST_H
#define BST_H

#include <iostream>
#include <utility>
#include <cmath>

template <class T>
class BST
{
    public:

        struct Node
        {
            T key;
            bool lidx;
            bool ridx;
            bool hasParent;
        };
        BST();
        virtual ~BST();

        class Iterator
        {
            private:
                int pos;
                const BST<T>& outer_class_ob;
                int endPos;

            public:
                Iterator (int x, const BST<T>& parent) : pos(x), outer_class_ob(parent), endPos(parent.last_pos + 1)
                {}

                Iterator (const Iterator&) = default;
                Iterator& operator=(const Iterator&) = default;
                Iterator (Iterator&&) = default;
                Iterator& operator=(Iterator&&) = default;

                bool operator==(const Iterator &it) const;
                bool operator!=(const Iterator &it) const { return !(this->pos == it.pos);}
                Iterator operator++() ;
                Iterator operator++(int) ;
                const T& operator*() const;
                const T* operator->() const;

                const int posMet() const {return pos;}
                const int endPosMet() const {return endPos;}

                friend BST<T>;

            bool operator==(const Iterator &it)
            {
                return this->pos == it.pos;
            }

        };
//
        //void insert(T value);
        //
        std::pair<BST<T>::Iterator, bool> insert (const T &value);
        void printInOrder() const;
        void printInOrder(int node_idx) const;
        Iterator search(const T &x) const;
        //BST<T>::Iterator search(T x);
        bool removeFirst(T x);
        int size() const;
        int depth(); //TODO
        int findMin(int node_idx);
        //void push_up(int idx);
        //void fix_leaf();
        bool fixTree(int pos);
        void resize (unsigned long long int new_size);
        int getLastPos() const;

        BST<T>& operator=(const BST<T> &obj);
        BST<T>& operator=(BST<T> &&obj);
        BST(const BST<T> &source);
        BST(BST<T> &&source) = default;

        Iterator begin() const
        {
            return Iterator(1, *this);
        }

        Iterator end() const
        {
            return Iterator(last_pos + 1, *this);
        }

        int current_size;
        unsigned long long int max_size;
        Node* tree_array;
        int last_pos;
    protected:
        void resize(BST<T> obj) const;

    private:

        //int leaf_pos_array[1000];
        //int leaf_num;
};

template <typename T>
typename BST<T>::Iterator BST<T>::Iterator::operator++()
{
    while(pos <= outer_class_ob.last_pos)
    {
                    pos++;
        if (outer_class_ob.tree_array[pos].hasParent == true)
        {
            return Iterator(pos, outer_class_ob);
        }

    }

    if (pos == outer_class_ob.last_pos)
        return Iterator(outer_class_ob.last_pos + 1, outer_class_ob);
}

template <typename T>
typename BST<T>::Iterator BST<T>::Iterator::operator++(int)
{


    while(pos <= outer_class_ob.last_pos)
    {
                    pos++;
        if (outer_class_ob.tree_array[pos].hasParent == true)
            return Iterator(pos, outer_class_ob);
    }

    if (pos == outer_class_ob.last_pos)
        return Iterator(outer_class_ob.last_pos + 1, outer_class_ob);
}

template <class T>
const T& BST<T>::Iterator::operator*() const
{
        return outer_class_ob.tree_array[pos].key;
}

template <class T>
const T* BST<T>::Iterator::operator->() const
{
    return &outer_class_ob.tree_array[pos].key;
}

template <class T>
BST<T>::BST() : max_size(4), current_size(0), last_pos (0)
{
    tree_array = new Node[max_size];

    for (int i = 0; i < max_size; i++)
    {
        tree_array[i].key = 0;
        tree_array[i].hasParent = false;
    }
    //ctor
}

template <class T>
BST<T>::BST(const BST<T> &source)
{
    this->max_size = source.max_size;
    this->current_size = source.current_size;
    this->last_pos = source.last_pos;

    this->tree_array = new Node[this->max_size];

    for (int i = 0; i < this->max_size;i++)
    {
        this->tree_array[i].key = source.tree_array[i].key;
        this->tree_array[i].hasParent = source.tree_array[i].hasParent;
    }
}

template <class T>
BST<T>::~BST()
{
    delete[] tree_array;
    //dtor
}

// OPERATORY //

template <class T>
BST<T>& BST<T>::operator=(const BST<T> &obj)
{
    delete[] this->tree_array;

    this->max_size = obj.max_size;
    this->current_size = obj.current_size;
    this->last_pos = obj.last_pos;

    this->tree_array = new Node[this->max_size];

    for (int i = 0; i < this->max_size; i++)
    {
        this->tree_array[i].key = obj.tree_array[i].key;
        this->tree_array[i].hasParent = obj.tree_array[i].hasParent;
    }

    return *this;
}

template <class T>
BST<T>& BST<T>::operator=(BST<T> &&obj)
{
    this -> current_size = obj.current_size;
    for (int i = 1; i <= obj.current_size; i++)
    {
        this -> tree_array[i].key = obj.tree_array[i].key;
        this -> tree_array[i].lidx = obj.tree_array[i].lidx;
        this -> tree_array[i].ridx = obj.tree_array[i].ridx;
    }

   return *this;
}

// METODY //
template <class T>
void BST<T>::resize(unsigned long long int new_size)
{
    Node* temp_arr = new Node[new_size];

    for (int i = 0; i < max_size; i++)
    {
        temp_arr[i].key = tree_array[i].key;
        temp_arr[i].hasParent = tree_array[i].hasParent;
    }

    for (int i = max_size; i < new_size; i++)
    {
        temp_arr[i].key = 0;
        temp_arr[i].hasParent = false;
    }

    Node* arr_to_delete = tree_array;
    tree_array = temp_arr;
    delete[] arr_to_delete;
    max_size = new_size;
}

// nowy insert
template <class T>
std::pair<typename BST<T>::Iterator, bool> BST<T>::insert (const T &value)
{
    auto search_val = search(value);

    if (current_size != 0 && search_val == (this -> end()))
    {
        bool idx = true;
        char parent_flag = 1;
        int parent_pos;
        int current_pos = 1;

        while (idx)
        {
            if (value >= tree_array[current_pos].key)
            {

                parent_pos = current_pos;
                idx = tree_array[(2* current_pos) + 1].hasParent;
                current_pos = (2* current_pos) + 1;
                parent_flag = '1';
            }

            if (value < tree_array[current_pos].key)
            {

                parent_pos = current_pos;
                idx = tree_array[2* current_pos].hasParent;
                current_pos = 2* current_pos;

                parent_flag = '2';
            }
        }

        // insertion
        tree_array[current_pos].key = value;
        tree_array[current_pos].hasParent = true;

        if (last_pos < current_pos)
            last_pos = current_pos;
        current_size++;

        //resize
        if ((max_size - last_pos) <= pow(2,(unsigned long long int)(log2(last_pos))))
        {
            resize(max_size + pow(2, (unsigned long long int) (log2(last_pos)) +1));
        }

        auto ret_val = std::make_pair(Iterator(current_pos, *this), true);
        return ret_val;
    }

    else if (current_size == 0)
    {
        tree_array[1].key = value;
        tree_array[1].hasParent = true;
        current_size++;
        last_pos = 1;

        auto ret_val = std::make_pair(Iterator(1, *this), true);
        return ret_val;
    }

    auto ret_val = std::make_pair(this -> end(), false);
    return ret_val;
}

template <class T>
bool BST<T>::removeFirst(T x)
{
    auto pos = search(x);

    // lisc
    if (tree_array[2*(pos.pos)].hasParent == false && tree_array[2*(pos.pos) + 1].hasParent == false)
    {
        tree_array[pos.pos].hasParent = false;
        current_size--;
        return true;
    }

       //2 dzieci
    else if (tree_array[2*(pos.pos)].hasParent == true  && tree_array[2*(pos.pos) + 1].hasParent == true)
    {

        int right_child_pos = pos.pos *2 + 1;
        int min_node_idx = findMin(right_child_pos);

        tree_array[pos.pos].key = tree_array[min_node_idx].key;

        if (tree_array[min_node_idx * 2].hasParent == false && tree_array[2 * min_node_idx + 1].hasParent == false)
            tree_array[min_node_idx].hasParent = false;

        else
            fixTree(min_node_idx);

        current_size--;

        return true;
    }

    // 1 dziecko
    else if ((tree_array[2 * pos.pos].hasParent == true || tree_array[2 * pos.pos + 1].hasParent == true))
    {

        if (tree_array[2 * pos.pos].hasParent == true)
        {
            int current_pos = 2 * pos.pos;
            tree_array[pos.pos].key = tree_array[pos.pos*2].key;

            if (tree_array[current_pos * 2].hasParent == false && tree_array[2 * current_pos + 1].hasParent == false)
                tree_array[current_pos].hasParent = false;

            else
                fixTree(current_pos);
        }

        else
        {
            int current_pos = 2 * pos.pos + 1;
            tree_array[pos.pos].key = tree_array[pos.pos*2 + 1].key;

            if (tree_array[current_pos * 2].hasParent == false && tree_array[2 * current_pos + 1].hasParent == false)
                tree_array[current_pos].hasParent = false;

            else
                fixTree(current_pos);
        }

        current_size--;
        return true;
    }

    return false;
}

template <class T>
bool BST<T>::fixTree(int pos)
{

    // lisc
    if (tree_array[2*(pos)].hasParent == false && tree_array[2*(pos) + 1].hasParent == false)
    {
        tree_array[pos].hasParent = false;
        return true;
    }

       //2 dzieci
    else if (tree_array[2*(pos)].hasParent == true && tree_array[2*(pos) + 1].hasParent == true)
    {
        int right_child_pos = pos *2 + 1;
        int min_node_idx = findMin(right_child_pos);

        tree_array[pos].key = tree_array[min_node_idx].key;

        if (tree_array[min_node_idx * 2].hasParent == false && tree_array[2 * min_node_idx + 1].hasParent == false)
            tree_array[min_node_idx].hasParent = false;

        else
            fixTree(min_node_idx);

        return true;
    }

    // 1 dziecko
    else if ((tree_array[2 * pos].hasParent == false || tree_array[2 * pos + 1].hasParent == false))
    {
        if (tree_array[2 * pos].hasParent == true)
        {
            int current_pos = 2 * pos;
            tree_array[pos].key = tree_array[pos*2].key;

            if (tree_array[current_pos * 2].hasParent == false && tree_array[2 * current_pos + 1].hasParent == false)
                tree_array[current_pos].hasParent = false;

            else
                fixTree(current_pos);
        }

        else
        {
            int current_pos = 2 * pos + 1;
            tree_array[pos].key = tree_array[pos*2 + 1].key;

            if (tree_array[current_pos * 2].hasParent == false && tree_array[2 * current_pos + 1].hasParent == false)
            {
                tree_array[current_pos].hasParent = false;
            }
            else
                fixTree(current_pos);

        }

        return true;
    }

    return false;
}

template <typename T>
typename BST<T>::Iterator BST<T>::search(const T &x) const
{
        int current_pos = 1;
        bool idx = true;

        while (idx != false)
        {
            if (x > tree_array[current_pos].key)
            {
                idx = tree_array[2 * current_pos + 1].hasParent;
                current_pos = 2 * current_pos + 1;
            }

            else if (x < tree_array[current_pos].key)
            {
                idx = tree_array[2 * current_pos].hasParent;
                current_pos = 2 * current_pos;
            }

            else
                return BST<T>::Iterator(current_pos, *this);
        }

        return this -> end();

}

template <class T>
int BST<T>::size() const
{
    return current_size;
}
// PRINTS //

template <class T>
void BST<T>::printInOrder(int node_idx) const
{
    if (tree_array[node_idx * 2].hasParent)
        printInOrder(node_idx * 2);

    std::cout << tree_array[node_idx].key << std::endl;

    if (tree_array[2 * node_idx + 1].hasParent)
        printInOrder((node_idx *2) + 1);

}

template <class T>
void BST<T>::printInOrder() const
{
    printInOrder(1);
}

template <class T>
int BST<T>::findMin(int node_idx)
{
    while (tree_array[node_idx*2].hasParent)
        node_idx *= 2;

    return node_idx;
}

template <class T>
int BST<T>::getLastPos() const
{
    return last_pos;
}

#endif // BST_H
