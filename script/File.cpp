#include "File.h"

File::File(string name) {
    this->Name = name;
    this->Parent = nullptr;
    this->action = Action::None;
}

File::File(string name, Node* parent) {
    this->Name = name;
    this->Parent = parent;
    this->action = Action::None;
}

File::~File() { }

void File::print(string pwd) {
    // 위치 + 자신의 이름 출력
    cout << pwd << this->Name << endl;
}

void File::cut() {
    // Action을 Cut으로 등록
    this->action = Action::Cut;
}

void File::copy() {
    // Action을 Copy로 등록
    this->action = Action::Copy;
}

Node* File::paste() {
    if (action == Action::Copy) {
        // 새로운 객체를 리턴
        return new File(this->Name);
    }
    else if (action == Action::Cut) {
        this->action = Action::None;

        // 자신 객체를 리턴
        return this;
    }

    // No Action
    return nullptr;
}