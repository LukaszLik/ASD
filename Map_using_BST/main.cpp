#include <iostream>
#include <string>
#include "Map.hpp"

using namespace std;

template <typename Iterator>
void printDebugInfo(const std::pair<Iterator, bool> &insert_info) { std::cout << (insert_info.second ? "Dodano "  : "Nie dodano ;/") << std::endl; }

template <typename Iterator>
void printDebugInfo(const Iterator &find_info)
{
    if (find_info.posMet() == find_info.endPosMet())
        std::cout << "Nie znaleziono\n";


    else
        cout << "Znaleziono\n";
}

template <typename K, typename V>
void printSetSizeAndElems(Map<K, V> &m)
{
std::cout << "Size: " << m.size() << std::endl;
for(auto &e : m) std::cout << e << ", ";
std::cout << std::endl;
}

template <typename K, typename V>
void printSetSizeAndElems(const Map<K, V> &m)
{
std::cout << "Size: " << m.size() << std::endl;
for(const auto &e : m) std::cout << e << ", ";
std::cout << std::endl;
}

int main()
{
Map<int, std::string> m;
printDebugInfo(m.insert(  8, "eight"  ));
printDebugInfo(m.insert(  4, "four"  ));
printDebugInfo(m.insert(  10, "ten"  ));
printDebugInfo(m.insert(  10, "ten"  ));
printDebugInfo(m.insert(  2, "two"  ));
printDebugInfo(m.insert(  5, "five"  ));
printDebugInfo(m.insert(  9, "nine"  ));
printDebugInfo(m.insert(  12, "twelve"  ));
printDebugInfo(m.insert(  12, "twelve"  ));
printDebugInfo(m.insert(  1, "one"  ));
printDebugInfo(m.insert(  14, "fourteen"  ));
printDebugInfo(m.insert(  7, "seven"  ));
{
auto m2 = m;
printSetSizeAndElems(m2);
}
auto it = m.find(10);
*it = "10 (poprawione)";
printDebugInfo(m.find(5));
m.removeFirst(4);
printDebugInfo(m.find(5));
m.removeFirst(12);
m.removeFirst(14);
printDebugInfo(m.insert(  0, "zero"  ));
printDebugInfo(m.insert(  16, "sixteen"  ));
{
Map<int, std::string> m3;
m3 = m;
printSetSizeAndElems(m3);
}
m.removeFirst(8);
printSetSizeAndElems(m);
const auto m4 = m;
printSetSizeAndElems(m4);
auto it2 = m4.find(10);
// *it2 = "nie powinno sie skompilowac";
// m4[2] = "nie powinno sie skompilowac";

printSetSizeAndElems(m);

return 0;
}

