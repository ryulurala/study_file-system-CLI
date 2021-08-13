#include "Directory.h"

using namespace std;

int main() {
    Directory* root = new Directory("/");

    // 루트('/')에서 시작!
    Directory* current = root;

    // 프롬프트 라인 출력: 현재 디렉토리 위치
    string pwd = current->Name;

    // cut or copy 노드를 가리키는 변수
    Node* node = nullptr;

    while (true) {
        // 현재 디렉토리명 출력
        cout << pwd << "> ";

        // 커맨드 입력
        string cmd;
        cin >> cmd;

        if (cmd == "exit") {
            // exit: 종료
            break;
        }
        else if (cmd == "ls") {
            // ls: 하위 디렉토리/파일 출력
            current->print(current->Name);
        }
        else if (cmd == "cd") {
            string arg;
            cin >> arg;
            
            // 최종 디렉토리 위치 문자열
            string destPwd(pwd);

            // 최종 목적지
            Directory* destDir = current->changeDirectory(destPwd, arg);

            if (destDir != nullptr) {
                // 최종 목적지 존재
                current = destDir;
                pwd = destPwd;
            }
        }
        else if (cmd == "add") {
            string arg;
            cin >> arg;

            // 추가
            current->add(arg);
        }
        else if (cmd == "rm") {
            string arg;
            cin >> arg;

            // 제거(메모리 해제까지)
            current->remove(arg);
        }
        else if (cmd == "cut") {
            string arg;
            cin >> arg;

            // 해당 노드 존재 여부
            node = current->findNode(arg);
            if (node == nullptr) {
                cout << "not found!" << endl;
            }
            else {
                node->cut();
            }
        }
        else if (cmd == "copy") {
            string arg;
            cin >> arg;

            // 해당 노드 존재 여부
            node = current->findNode(arg);
            if (node == nullptr) {
                cout << "not found!" << endl;
            }
            else {
                node->copy();
            }
        }
        else if (cmd == "paste") {
            if (node == nullptr) {
                cout << "no copy & cut file" << endl;
            }
            else {
                // paste
                Node* originOrNew = node->paste();
                if (originOrNew != nullptr) {
                    // 현재 디렉토리에 추가
                    current->add(originOrNew);
                }
                else {
                    cout << "no copy & cut file" << endl;
                }
            }
        }
    }

    // root부터 메모리 해제
    if (root != nullptr)
        delete root;

    return 0;
}