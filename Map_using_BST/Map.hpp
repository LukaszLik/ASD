/*
 * File:   Map.hpp
 * Author: lik_1145951
 *
 * Created on 1 kwietnia 2019, 11:53
 */

#ifndef MAP_HPP
#define	MAP_HPP
#include "BST.h"
#include <utility>
#include <cstring>

template <class K, class V>
class Map
{
    //template <class T>
    class MapElem
    {
        public:
            std::pair<K,V> tree_val;

            MapElem() = default;
            MapElem(const std::pair<K,V> &key_value) : tree_val(key_value)
            {}

            MapElem(const K &key, const V &value)
            {
                tree_val.first = key;
                tree_val.second = value;
            }

            bool operator==(const MapElem &map_elem) const
            {return this->tree_val.first == map_elem.tree_val.first;}

            bool operator>(const MapElem &map_elem) const
            {return this->tree_val.first > map_elem.tree_val.first;}

            bool operator<(const MapElem &map_elem) const
            {return this->tree_val.first < map_elem.tree_val.first;}

            bool operator>=(const MapElem &map_elem) const
            {return this->tree_val.first >= map_elem.tree_val.first;}

            bool operator<=(const MapElem &map_elem) const
            {return this->tree_val.first <= map_elem.tree_val.first;}

            void operator=(const MapElem &map_elem)
            {
                this->tree_val.first = map_elem.tree_val.first;
                this->tree_val.second = map_elem.tree_val.second;
            }

            void operator=(const int &val)
            {
                this->tree_val.first = val;
                this->tree_val.second = val;
            }

            friend std::ostream& operator<< (std::ostream& stream, const MapElem &map_elem)
            {
                stream << "[" << map_elem.tree_val.first << "],   " << map_elem.tree_val.second;
                return stream;
            }
    };

    friend BST<MapElem>;
    //ITERATOR
     class Iterator
        {
            private:
                int pos;
                const BST<MapElem>& outer_class_ob;
                int endPos;

            public:
                friend MapElem;
                friend Map<K,V>;
                friend BST<MapElem>;

                Iterator (int x, const BST<MapElem>& parent) : pos(x), outer_class_ob(parent), endPos(parent.last_pos + 1)
                {}

                Iterator (const Iterator&) = default; //
                Iterator& operator=(const Iterator&) = default; //
                Iterator (Iterator&&) = default; //
                Iterator& operator=(Iterator&&) = default; //

                //TODO
                bool operator==(const Iterator &it) ; //
                bool operator!=(const Iterator &it)
                { return !(this->pos == it.pos);} //

                Iterator operator++();
                Iterator operator++(int);
                V& operator*();
                V* operator->();

                const int posMet() const {return pos;}
                const int endPosMet() const {return endPos;}



        };
        //KONIEC ITERATOR

        //CONST ITERATOR
     class ConstIterator
        {
            private:
                int pos;
                const BST<MapElem>& outer_class_ob;
                int endPos;

            public:
                friend MapElem;
                friend Map<K,V>;
                friend BST<MapElem>;

                ConstIterator (int x, const BST<MapElem>& parent) : pos(x), outer_class_ob(parent), endPos(parent.last_pos + 1)
                {}

                ConstIterator (const ConstIterator&) = default; //
                ConstIterator& operator=(const ConstIterator&) = default; //
                ConstIterator (ConstIterator&&) = default; //
                ConstIterator& operator=(ConstIterator&&) = default; //

                //TODO
                bool operator==(const ConstIterator &it) const; //
                bool operator!=(const ConstIterator &it) const { return !(this->pos == it.pos);} //
                ConstIterator operator++();
                ConstIterator operator++(int);
                const V& operator*() const;
                const V* operator->() const;

                const int posMet() const {return pos;}
                const int endPosMet() const {return endPos;}



        };
        //KONIEC CONST ITERATOR

    public:
        Map() : tree_obj(new BST<MapElem>)
        {}

        int size() const;

        //TODOOOOO
        std::pair<Map<K,V>::Iterator, bool> insert (const K &key, const V &value);
        bool remove (const K &key);

        void printInOrder() const;
        bool removeFirst(K x);
        Iterator find(const K x);
        ConstIterator find(const K x) const;
        std::pair<MapElem,bool> searchMapElem(const K &x) const;

        Map<K,V>& operator=(const Map<K,V> &obj);
        Map<K,V>& operator=(Map<K,V> &&obj);
        Map<K,V>(const Map<K,V> &source);
        Map<K,V>(Map<K,V> &&source) = default;

        //

        Iterator begin()
        {
            return Iterator(1, *tree_obj);
        }

        ConstIterator begin() const
        {
            return ConstIterator(1, *tree_obj);
        }

        Iterator end()
        {
            return Iterator(tree_obj->last_pos + 1, *tree_obj);
        }

        ConstIterator end() const
        {
            return ConstIterator(tree_obj->last_pos + 1, *tree_obj);
        }


    private:
        BST<MapElem> *tree_obj;

};

// iteratory
template <class K, class V>
bool Map<K,V>::Iterator::operator==(const Iterator &it)
{
    return this->pos == it.pos;
}

template <class K, class V>
typename Map<K,V>::Iterator Map<K,V>::Iterator::operator++()
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

template <class K, class V>
typename Map<K,V>::Iterator Map<K,V>::Iterator::operator++(int)
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

template <class K, class V>
V& Map<K,V>::Iterator::operator*()
{
    return outer_class_ob.tree_array[pos].key.tree_val.second;
}

template <class K, class V>
V* Map<K,V>::Iterator::operator->()
{
    return &outer_class_ob.tree_array[pos].key.tree_val.second;
}


//CONSTITER
template <class K, class V>
bool Map<K,V>::ConstIterator::operator==(const ConstIterator &it) const
{
    return this->pos == it.pos;
}

template <class K, class V>
typename Map<K,V>::ConstIterator Map<K,V>::ConstIterator::operator++()
{
    while(pos <= outer_class_ob.last_pos)
    {
        pos++;

        if (outer_class_ob.tree_array[pos].hasParent == true)
            return ConstIterator(pos, outer_class_ob);
    }

    if (pos == outer_class_ob.last_pos)
        return ConstIterator(outer_class_ob.last_pos + 1, outer_class_ob);
}

template <class K, class V>
typename Map<K,V>::ConstIterator Map<K,V>::ConstIterator::operator++(int)
{
    while(pos <= outer_class_ob.last_pos)
    {
        pos++;

        if (outer_class_ob.tree_array[pos].hasParent == true)
            return ConstIterator(pos, outer_class_ob);
    }

    if (pos == outer_class_ob.last_pos)
        return ConstIterator(outer_class_ob.last_pos + 1, outer_class_ob);
}

template <class K, class V>
const V& Map<K,V>::ConstIterator::operator*() const
{
    return outer_class_ob.tree_array[pos].key.tree_val.second;
}

template <class K, class V>
const V* Map<K,V>::ConstIterator::operator->() const
{
    return &outer_class_ob.tree_array[pos].key.tree_val.second;
}
//

// metody
template <class K, class V>
Map<K,V>& Map<K,V>::operator=(const Map<K,V> &obj)
{
    delete this->tree_obj;

    this->tree_obj = new BST<MapElem>;

    this->tree_obj = obj.tree_obj;
}

template <class K, class V>
Map<K,V>& Map<K,V>::operator=(Map<K,V> &&obj)
{
    delete this->tree_obj;

    this->tree_obj = new BST<MapElem>;

    this->tree_obj = obj.tree_obj;
}

template <class K, class V>
Map<K,V>::Map(const Map<K,V> &source)
{
    this-> tree_obj = source.tree_obj;
}


template <class K, class V>
int Map<K,V>::size() const
{
    return tree_obj->size();
}

template <class K, class V>
std::pair<typename Map<K,V>::Iterator, bool> Map<K,V>::insert (const K &key, const V &value)
{
    MapElem elem (key, value);
    auto added = (tree_obj->insert(elem));

    auto first_ret = find(key);
    if (added.second)
    {
        auto retval = std::make_pair(first_ret, true);
        return retval;
    }

    else
    {
        auto retval = std::make_pair(first_ret, false);
        return retval;
    }
}

template <class K, class V>
void Map<K,V>::printInOrder() const
{
    tree_obj -> printInOrder();

}


// wyszukać indeks i później usunąć? z iteratorem?
template <class K, class V>
bool Map<K,V>::removeFirst(K x)
{
    auto retval = searchMapElem(x);

    if (retval.second == true)
    {
        tree_obj -> removeFirst(retval.first);
        return true;
    }

    else
        return false;
}


template <class K, class V>
typename Map<K,V>::Iterator Map<K,V>::find(const K x)
{
        int current_pos = 1;
        bool idx = true;

        while (idx != false)
        {
            if (x > tree_obj->tree_array[current_pos].key.tree_val.first)
            {
                idx = tree_obj->tree_array[2 * current_pos + 1].hasParent;
                current_pos = 2 * current_pos + 1;
            }

            else if (x < tree_obj->tree_array[current_pos].key.tree_val.first)
            {
                idx = tree_obj->tree_array[2 * current_pos].hasParent;
                current_pos = 2 * current_pos;
            }

            else
                return Map<K,V>::Iterator(current_pos, *tree_obj);
        }

        return this -> end();
}

template <class K, class V>
typename Map<K,V>::ConstIterator Map<K,V>::find(const K x) const
{
        int current_pos = 1;
        bool idx = true;

        while (idx != false)
        {
            if (x > tree_obj->tree_array[current_pos].key.tree_val.first)
            {
                idx = tree_obj->tree_array[2 * current_pos + 1].hasParent;
                current_pos = 2 * current_pos + 1;
            }

            else if (x < tree_obj->tree_array[current_pos].key.tree_val.first)
            {
                idx = tree_obj->tree_array[2 * current_pos].hasParent;
                current_pos = 2 * current_pos;
            }

            else
                return Map<K,V>::ConstIterator(current_pos, *tree_obj);
        }

        return this -> end();
}

template <class K, class V>
std::pair<typename Map<K,V>::MapElem, bool> Map<K,V>::searchMapElem(const K &x) const
{
        int current_pos = 1;
        bool idx = true;

        while (idx != false)
        {
            if (x > tree_obj->tree_array[current_pos].key.tree_val.first)
            {
                idx = tree_obj->tree_array[2 * current_pos + 1].hasParent;
                current_pos = 2 * current_pos + 1;
            }

            else if (x < tree_obj->tree_array[current_pos].key.tree_val.first)
            {
                idx = tree_obj->tree_array[2 * current_pos].hasParent;
                current_pos = 2 * current_pos;
            }

            else
            {
                auto retval = std::make_pair(tree_obj->tree_array[current_pos].key.tree_val, true);
                return retval;
            }
        }

        MapElem xret (0,0);
        auto retval = std::make_pair(xret, false);
        return retval;
}

//
#endif	/* MAP_HPP */

