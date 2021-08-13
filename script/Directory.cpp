#include "Directory.h"

Directory::Directory(string name) {
    this->Name = name;
    this->Parent = nullptr;
    this->action = Action::None;
}

Directory::Directory(string name, Node* parent) {
    this->Name = name;
    this->Parent = parent;
    this->action = Action::None;
}

Directory::~Directory() {
    for (Node* node : this->_nodeList) {
        delete node;
    }
}

void Directory::add(string name) {
    if (name.empty())
        return;

    // 중복 검사
    if (this->findNode(name) != nullptr) {
        cout << "duplicated!" << endl;
        return;
    }

    // 디렉토리 or 파일 생성
    Node* node;
    if (name.back() == '/') 
        node = new Directory(name, this);   // 디렉토리
    else 
        node = new File(name, this);        // 파일

    // 노드 리스트에 추가
    this->_nodeList.push_back(node);
}

void Directory::add(Node* node) {
    if (node == nullptr)
        return;

    // 중복 검사
    if (this->findNode(node->Name) != nullptr) {
        // 메모리 낭비 방지
        // copy한 파일은 삭제
        if (node->Parent == nullptr) delete node;

        cout << "duplicated!" << endl;
        return;
    }
    
    // Action이 cut이라면 parent 존재하므로
    if (node->Parent != nullptr) {
        // 해당 디렉토리의 리스트에서 제거
        ((Directory*)node->Parent)->remove(node);
    }

    // parent 등록
    node->Parent = this;

    // 리스트에 추가
    this->_nodeList.push_back(node);
}

void Directory::remove(string name) {
    for (int i = 0; i < this->_nodeList.size(); i++) {
        if (this->_nodeList[i]->Name == name) {
            // 객체 제거
            delete this->_nodeList[i];

            // 리스트에서 제거
            this->_nodeList.erase(this->_nodeList.begin() + i);
        }
    }
}

void Directory::remove(Node* node) {
    for (int i = 0; i < this->_nodeList.size(); i++) {
        if (this->_nodeList[i]->Name == node->Name) {
            // 리스트에서만 제거
            this->_nodeList.erase(this->_nodeList.begin() + i);
        }
    }
}

void Directory::print(string pwd) {
    if (pwd == this->Name) {
        // 처음 접근에 대해서
        pwd = "";
    }
    else{
        // 해당 디렉토리명 출력
        cout << pwd << this->Name << endl;

        // 현재 위치 + 해당 디렉토리명
        pwd += this->Name;
    }

    for (Node* node : this->_nodeList) {
        // 각 노드들에 대해 출력
        node->print(pwd);
    }
}

Directory* Directory::changeDirectory(string& pwd, string& args) {
    if (args.empty())
        return this;    // 최종 목적지
    
    int index = args.find('/');
    if (index == string::npos)
        return nullptr;

    string arg = args.substr(0, index + 1);
    args = args.substr(index + 1);

    // 절대 경로
    if (arg == "/") {
        Node* root = this;
        while (root->Parent != nullptr) {
            root = root->Parent;
        }
        pwd = arg;

        // 다음 디렉토리
        return ((Directory*)root)->changeDirectory(pwd, args);
    }

    // 상대 경로
    if (arg == "../" && this->Parent != nullptr) {
        int currentNameLen = this->Name.length();
        int pwdLen = pwd.length();
        
        pwd = pwd.substr(0, pwdLen - currentNameLen);
        
        // 이전 디렉토리
        return ((Directory*)this->Parent)->changeDirectory(pwd, args);
    }

    Node* nextDirectory = this->findNode(arg);
    if (nextDirectory != nullptr) {
        pwd += arg;

        // 다음 디렉토리
        return ((Directory*)nextDirectory)->changeDirectory(pwd, args);
    }

    return nullptr;
}

Node* Directory::findNode(string name) {
    for (Node* node : this->_nodeList) {
        // Name명 비교
        if (node->Name == name) {
            return node;
        }
    }

    return nullptr;
}

void Directory::cut() {
    this->action = Action::Cut;
    
    for (Node* node : this->_nodeList) {
        // 노드의 Action을 Cut으로 등록
        node->cut();
    }
}

void Directory::copy() {
    this->action = Action::Copy;
    
    for (Node* node : this->_nodeList) {
        // 노드의 Action을 Copy로 등록
        node->copy();
    }
}

Node* Directory::paste() {
    if (action == Action::Copy) {
        // 새로운 디렉토리 생성
        Directory* copyDirectory = new Directory(this->Name);

        for (Node* node : this->_nodeList) {
            // 새로운 노드들을 생성
            Node* copyNode = node->paste();

            // 새로운 디렉토리에 push
            copyDirectory->_nodeList.push_back(copyNode);
        }

        return copyDirectory;
    }
    else if (action == Action::Cut) {
        for (Node* node : this->_nodeList) {
            // 노드의 Action을 None으로 초기화
            node->paste();
        }
        this->action = Action::None;

        // 자신을 리턴
        return this;
    }

    // No Action
    return nullptr;
}