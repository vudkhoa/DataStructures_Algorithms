#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "myLib.h"
using namespace std;
enum Sex { MALE, FEMALE };

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

void parseJSONPassenger(std::string& idCard, std::string& firstName, std::string& lastName, Sex& sex, std::string JSON) {
    int length = (int)JSON.length();
    int i = 0;
    for (; i <= length - 1; i++) {
        if (JSON[i] != '#') {
            idCard = idCard + JSON[i];
        }
        else break;
    }
    i++;
    for (; i <= length - 1; i++) {
        if (JSON[i] != '#') {
            firstName = firstName + JSON[i];
        }
        else break;
    }
    i++;
    for (; i <= length - 1; i++) {
        if (JSON[i] != '#') {
            lastName = lastName + JSON[i];
        }
        else break;
    }
    i++;
    if (JSON[length - 1] == '0') sex = MALE;
    else sex = FEMALE;
}

std::string stringtifyPassenger(std::string idCard, std::string firstName, std::string lastName, Sex sex) {
    std::string Sx = sex == MALE ? "0" : "1";
    return idCard + "#" + firstName + "#" + lastName + "#" + Sx;
}

struct Passenger {
    std::string idCard;
    std::string firstName;
    std::string lastName;
    Sex sex;

    // Constructer
    Passenger() {};
    Passenger(std::string idCard, std::string firstName, std::string lastName, Sex sex) {
        this->idCard = idCard;
        this->firstName = firstName;
        this->lastName = lastName;
        this->sex = sex;
    }

    void prInfo() {
        std::cout << idCard << " --- " << firstName << "---" << lastName << " --- " << ((sex == MALE) ? "male" : "FeMale") << "\n";
    }
    // destructor 
    ~Passenger() {};
};

struct nodeAVLPassenger {
    Passenger info;
    nodeAVLPassenger* left;
    nodeAVLPassenger* right;
    int height = 1;

    // Constructor
    nodeAVLPassenger() {
        this->left = nullptr;
        this->right = nullptr;
    };
    nodeAVLPassenger(Passenger info) {
        this->info = info;
        this->left = nullptr;
        this->right = nullptr;
    }
    // Destructor
    ~nodeAVLPassenger() {};
};

class PassengerCLASS {
    private:
        nodeAVLPassenger* root = nullptr;
        int numberOfPassenger = 0;

        int heightNode(nodeAVLPassenger* head) {
            if (head != nullptr) return head->height;
            else return 0;
        }
        int getBalance(nodeAVLPassenger* head) {
            return heightNode(head->left) - heightNode(head->right);
        }

        nodeAVLPassenger* rotateLeft(nodeAVLPassenger* x) {
            nodeAVLPassenger* y = x->right;
            x->right = y->left;
            y->left = x;
            x->height = 1 + max(heightNode(x->left), heightNode(x->right));
            y->height = 1 + max(heightNode(y->left), heightNode(y->right));
            return y;
        }
        nodeAVLPassenger* rotateRight(nodeAVLPassenger* x) {
            nodeAVLPassenger* y = x->left;
            x->left = y->right;
            y->right = x;
            x->height = 1 + max(heightNode(x->left), heightNode(x->right));
            y->height = 1 + max(heightNode(y->left), heightNode(y->right));
            return y;
        }
        nodeAVLPassenger* insertPassenger(Passenger newInfo, nodeAVLPassenger* head) {

            if (head == nullptr) {
                numberOfPassenger++;
                return new nodeAVLPassenger(newInfo);
            }
            if (newInfo.idCard > head->info.idCard) head->right = insertPassenger(newInfo, head->right);
            else if (newInfo.idCard < head->info.idCard) head->left = insertPassenger(newInfo, head->left);
            else return head;

            head->height = 1 + max(heightNode(head->left), heightNode(head->right));
            int balance = getBalance(head);

            if (balance < -1 && newInfo.idCard > head->right->info.idCard)
                return rotateLeft(head);

            if (balance < -1 && newInfo.idCard < head->right->info.idCard) {
                head->right = rotateRight(head->right);
                return rotateLeft(head);
            }

            if (balance > 1 && newInfo.idCard < head->left->info.idCard)
                return rotateRight(head);

            if (balance > 1 && newInfo.idCard > head->left->info.idCard) {
                head->left = rotateLeft(head->left);
                return rotateRight(head);
            }
            return head;
        }

        nodeAVLPassenger* maxNode(nodeAVLPassenger* head) {
            nodeAVLPassenger* temp = head;
            while (temp->right != nullptr) temp = temp->right;
            return temp;
        }

        void deleteAll(nodeAVLPassenger*& head) {
            if (head != nullptr) {
                deleteAll(head->left);
                deleteAll(head->right);
                delete head;
            }
        }
    public:
        int getNumberOfPassenger() {
            return numberOfPassenger;
        }
        void exist(std::string idCard, nodeAVLPassenger*& temp) {
            if (root == nullptr) return;
            nodeAVLPassenger* tmp = root;
            while (tmp != nullptr) {
                if (tmp->info.idCard == idCard) {
                    temp = tmp;
                    return;
                }
                if (tmp->info.idCard < idCard) tmp = tmp->right;
                else tmp = tmp->left;
            }
        }
        void show() {
            if (root == nullptr) return;
            nodeAVLPassenger** STACK = new nodeAVLPassenger * [numberOfPassenger];
            int index = -1;
            nodeAVLPassenger* cur = root;
            while (index != -1 || cur != nullptr) {
                while (cur != nullptr) {
                    cout << cur->info.idCard << "!!" << cur->info.firstName << "!!" << cur->info.lastName << "!!" << cur->info.sex << endl;
                    STACK[++index] = cur;
                    cur = cur->left;
                }
                cur = STACK[index];
                index--;
                cur = cur->right;
            }
        }

        // lay toan bo danh sach
        void takeDataOfALLPassenger(nodeAVLPassenger**& arr, int& num) {
            arr = new nodeAVLPassenger * [numberOfPassenger];
            int i = -1;
            num = numberOfPassenger;
            nodeAVLPassenger** STACK = new nodeAVLPassenger * [numberOfPassenger];
            int index = -1;
            nodeAVLPassenger* cur = root;
            while (index != -1 || cur != nullptr) {
                while (cur != nullptr) {
                    
                    STACK[++index] = cur;
                    cur = cur->left;
                }
                cur = STACK[index];
                arr[++i] = cur;
                index--;
                cur = cur->right;
            }
            return;
        }
        void takeDataOfALLPassenger_SEARCH(nodeAVLPassenger**& arr, int& num, string searchCODEIDCard) {
            arr = new nodeAVLPassenger * [numberOfPassenger];
            int i = -1;
            nodeAVLPassenger** STACK = new nodeAVLPassenger * [numberOfPassenger];
            int index = -1;
            nodeAVLPassenger* cur = root;
            while (index != -1 || cur != nullptr) {
                while (cur != nullptr) {
                    if (NS_myLib::ExistenceCheck( searchCODEIDCard, cur->info.idCard)) {
                        arr[++i] = cur;
                    }
                    STACK[++index] = cur;
                    cur = cur->left;
                }
                cur = STACK[index];
                index--;
                cur = cur->right;
            }
            num = i + 1;
            return;
        }
        bool isEmpty() {
            if (root == nullptr) return true;
            return false;
        }
        bool search(std::string idCard) {
            nodeAVLPassenger* temp = nullptr;
            exist(idCard, temp);
            if (temp == nullptr) return false;
            return true;
        }
        Passenger getInfoPassenger(std::string idCard, std::string firstName, std::string lastName, Sex sex) {
            Passenger newPassenger(idCard, firstName, lastName, sex);
            return newPassenger;
        }

        void insertNode(Passenger newPassenger) {
            root = insertPassenger(newPassenger, root);
        }

        void loadDataPassenger() {
            std::string idCard = "";
            std::string lastName = "";
            std::string firstName = "";
            Sex sex;
            std::string JSON = "";
            std::fstream data;
            data.open("C://Users//Acer//code//slint-cpp-template//UI_DEMO//src//PassengerList.txt", std::ios::in);
            int n;
            data >> n;
            data.ignore();
            for (int i = 1; i <= n; i++) {
                idCard = "";
                lastName = "";
                firstName = "";
                std::getline(data, JSON);
                parseJSONPassenger(idCard, firstName, lastName, sex, JSON);
                Passenger newPassenger(idCard, firstName, lastName, sex);
                root = insertPassenger(newPassenger, root);
            }
            data.close();
        }
        void saveDataPassenger() {
            std::fstream data;
            data.open("C://Users//Acer//code//slint-cpp-template//UI_DEMO//src//PassengerList.txt", std::ios::out);
            data << numberOfPassenger << endl;
            if (root == nullptr) return;
            nodeAVLPassenger** STACK = new nodeAVLPassenger * [numberOfPassenger];
            int index = -1;
            nodeAVLPassenger* cur = root;
            while (index != -1 || cur != nullptr) {
                while (cur != nullptr) {
                    Passenger INFO = cur->info;
                    string JSON = stringtifyPassenger(INFO.idCard, INFO.firstName, INFO.lastName, INFO.sex);
                    data << JSON << endl;
                    STACK[++index] = cur;
                    cur = cur->left;
                }
                cur = STACK[index];
                index--;
                cur = cur->right;
            }
            data.close();
        }
        void sortPASSENGERLIST_BYID(nodeAVLPassenger** arr, int n) {
            nodeAVLPassenger* temp;
            for (int i = 0; i <= n - 2; i++) {
                for (int j = i + 1; j <= n - 1; ++j) {
                    if (arr[i]->info.idCard > arr[j]->info.idCard) {
                        temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                    }
                }
            }
        }
        void sortPASSENGERLIST_BYFirstName(nodeAVLPassenger** arr, int n) {
            nodeAVLPassenger* temp;
            for (int i = 0; i <= n - 2; i++) {
                for (int j = i + 1; j <= n - 1; ++j) {
                    if (arr[i]->info.firstName > arr[j]->info.firstName) {
                        temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                    }
                }
            }
        }
        void sortPASSENGERLIST_BYLAST(nodeAVLPassenger** arr, int n) {
            nodeAVLPassenger* temp;
            for (int i = 0; i <= n - 2; i++) {
                for (int j = i + 1; j <= n - 1; ++j) {
                    if (arr[i]->info.lastName > arr[j]->info.lastName) {
                        temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                    }
                }
            }
        }
        void sortPASSENGERLIST_BYMALE(nodeAVLPassenger** arr, int n) {
            nodeAVLPassenger* temp;
            for (int i = 0; i <= n - 2; i++) {
                for (int j = i + 1; j <= n - 1; ++j) {
                    if (arr[i]->info.sex > arr[j]->info.sex) {
                        temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                    }
                }
            }
        }
        void sortPASSENGERLIST_BYFEMALE(nodeAVLPassenger** arr, int n) {
            nodeAVLPassenger* temp;
            for (int i = 0; i <= n - 2; i++) {
                for (int j = i + 1; j <= n - 1; ++j) {
                    if (arr[i]->info.sex < arr[j]->info.sex) {
                        temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                    }
                }
            }
        }
        // -- //
        void getInfo_bySearch(Passenger *&info, std::string IDCARD) {
            info == nullptr;
            if (root == nullptr) return;
            nodeAVLPassenger* tmp = root;
            while (tmp != nullptr) {
                if (tmp->info.idCard == IDCARD) {
                    info = &tmp->info;
                    return;
                }
                if (tmp->info.idCard < IDCARD) tmp = tmp->right;
                else tmp = tmp->left;
            }
            // nodeAVLPassenger** STACK = new nodeAVLPassenger * [numberOfPassenger];
            // int index = -1;
            // nodeAVLPassenger* cur = root;
            // while (index != -1 || cur != nullptr) {
            //     while (cur != nullptr) {
            //         STACK[++index] = cur;
            //         cur = cur->left;
            //     }

            //     cur = STACK[index];
            //     if (cur->info.idCard == IDCARD) {
            //         info = &cur->info;
            //         return;
            //     }
            //     index--;
            //     cur = cur->right;
            // }
        }
        void sortTICKETPASSENGERLIST_BYID(Passenger *&arr, int n) {
            Passenger temp; 
            for (int i = 0; i < n - 1; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    if (arr[i].idCard > arr[j].idCard) {
                        cout << "i: " << i << endl;
                        temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                    }
                }
            }
        }
        void sortTICKETPASSENGERLIST_BYNAME(Passenger *&arr, int n) {
            Passenger temp;
            for (int i = 0; i < n - 1; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    string s1 = arr[i].firstName + arr[i].lastName;
                    string s2 = arr[j].firstName + arr[j].lastName;
                    if (s1 > s2) {
                        temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                    }
                }
            }
        }
        // -- //
        void deleteAll() {
            deleteAll(root);
        }
};