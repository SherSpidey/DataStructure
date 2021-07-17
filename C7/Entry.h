//
// Created by 62736 on 2021/7/14.
//

#ifndef DATASTRUCTURE_ENTRY_H
#define DATASTRUCTURE_ENTRY_H

#endif //DATASTRUCTURE_ENTRY_H

template<typename K, typename V>
struct Entry {  //词条模板类
    K key;
    V value;

    explicit Entry(K k = K(), V v = V()) : key(k), value(v) {};

    Entry(Entry<K, V> const &e) : key(e.key), value(e.value) {};

    //比较器，判等器
    bool operator<(Entry<K, V> const &e) { return key < e.key; }

    bool operator>(Entry<K, V> const &e) { return key > e.key; }

    bool operator==(Entry<K, V> const &e) { return key == e.key; }

    bool operator!=(Entry<K, V> const &e) { return key != e.key; }
};
