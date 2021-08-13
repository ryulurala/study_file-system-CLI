#pragma once

#include <iostream>
#include <string>

using namespace std;

enum class Action {
    None,
    Cut,
    Copy,
};

class Node {
public:
    string Name;
    Node* Parent;
    Action action;

public:
    virtual ~Node();

public:
    virtual void print(string pwd) = 0;
    virtual void cut() = 0;
    virtual void copy() = 0;
    virtual Node* paste() = 0;
};