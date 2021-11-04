﻿#pragma once
#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<functional>

struct Student
{
    unsigned age;
    unsigned weight;
};

typedef std::string Key;
typedef Student Value;

class HashTable
{
public:
    //constructor
    HashTable();

    //deconstructor
    ~HashTable();

    //copy constructor.
    HashTable(const HashTable& b);

    //move copy constructor.
    HashTable(HashTable&& b);

    HashTable& operator=(const HashTable& b);
    HashTable& operator=(HashTable&& b);

    //swap two hash tables.
    void swap(HashTable& b);

    //clear hash table.
    void clear();

    //delete element by key.
    bool erase(const Key& k);

    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v);

    // Проверка наличия значения по заданному ключу.
    bool contains(const Key& k) const;

    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнере, следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него. 
    Value& operator[](const Key& k);

    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value& at(const Key& k);
    const Value& at(const Key& k) const;

    size_t size() const;
    bool empty() const;

    friend bool operator==(const HashTable& a, const HashTable& b);
    friend bool operator!=(const HashTable& a, const HashTable& b);

private:
    typedef std::vector<std::list<std::pair<Key, Value>>> HTable;
    int tsize, real_size;
    HTable table;
};

bool operator==(const HashTable& a, const HashTable& b);
bool operator!=(const HashTable& a, const HashTable& b);