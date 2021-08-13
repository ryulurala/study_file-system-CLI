#pragma once

#include "Node.h"

using namespace std;

class File : public Node {
public:
    File(string name);
    File(string name, Node* parent);
    ~File();

public:
    virtual void print(string pwd);     // override
    virtual void cut();                 // override
    virtual void copy();                // override
    virtual Node* paste();              // override
};
