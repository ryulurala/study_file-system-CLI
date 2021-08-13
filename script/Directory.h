#pragma once

#include <vector>
#include "File.h"

using namespace std;

class Directory : public Node {
private:
    vector<Node*> _nodeList;    // 노드(파일/디렉토리) 목록

public:
    Directory(string name);
    Directory(string name, Node* parent);
    virtual ~Directory();

public:
    void add(string name);          // overload
    void add(Node* node);           // overload
    void remove(string name);       // overload
    void remove(Node* node);        // overload
    Node* findNode(string name);
    Directory* changeDirectory(string& pwd, string& args);
    virtual void print(string pwd); // override
    virtual void cut();             // override
    virtual void copy();            // override
    virtual Node* paste();          // override
};
