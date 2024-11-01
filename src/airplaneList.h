#pragma once
#include "MyLib.h"
#include <fstream>
// Information of Plane
struct airplane {
    std::string idPlane; // key
    std::string typePlane;
    int colNumber; // 
    int rowNumber; // 

    // cac truong phu
    int flyTimes = 0;
    bool isAvai = false;
    // Constructor
    airplane() {};
    airplane(std::string idPlane, std::string typePlane, int rowNumber, int colNumber, int flyTimes, bool isAvai) {
        this->idPlane = idPlane;
        this->typePlane = typePlane;
        this->rowNumber = rowNumber;
        this->colNumber = colNumber;
        this->flyTimes = flyTimes;
        this->isAvai = isAvai;
    }
    void increaseFlyTimes() {
        flyTimes++;
    }
    // -- //
    void decreaseFlyTimes() {
        flyTimes--;
    }
    // -- //
    void prInfo() {
        std::cout << "ID:" << idPlane << " - TYPE:" << typePlane << " - ROW:" << rowNumber << " - COL:" << colNumber << " FLYTIME:" << flyTimes << " ISVAi:" << isAvai << endl;
    }
    // Check Seats
    ~airplane() {};
};

class airplaneListClass {
private:
    int index = -1;
    airplane* data[300];
    // Constructor
public:
    airplaneListClass() {};
    bool isEmpty() {
        if (this->index == -1) return true;
        return false;
    }
    // -- //
    airplane get_data(int index) {
        return *this->data[index];
    }
    // -- //
    int findAirplane(std::string idPlane) {
        if (this->index != -1) { 
            for (int i = 0; i <= this->index; i++) {
                if (this->data[i]->idPlane == idPlane) return i;
            }
        }
        return -1;
    }
    // -- //
    int countIndexPlane() {
        return this->index + 1;
    }
    // In danh sách //  ?????
    void show() {
        if (index >= 0) {
            for (int i = 0; i <= this->index; i++) {
                this->data[i]->prInfo();
            }
        }
    }
    // -- //
    string addPlane(std::string idPlane, std::string typePlane, int rowNumber, int colNumber, int flytimes, bool isAvai) {
        if (findAirplane(idPlane) != -1) return "This aircraft code already exists";
        if (index <= 299) {
            airplane* newAirplane = new airplane(idPlane, typePlane, rowNumber, colNumber, flytimes, isAvai);
            data[++index] = newAirplane;
            return "Added aircraft successfully";
        }
        return "Exceeding 300 aircraft, cannot be added";
    }
    // -- //
    string deletePlane(std::string idPlane) {
        int index = this->findAirplane(idPlane);
        if (index != -1) {
            if (this->data[index]->isAvai == false) return "This aircraft is in flight, cannot be deleted";
            delete this->data[index];
            for (int i = index; i <= this->index - 1; i++) {
                this->data[i] = this->data[i + 1];
            }
            --this->index;
            return "Deleted the plane successfully";
        }
        return "No plane found";
    }
    // Load data //
    void LoadDataPlaneList() {
        std::string JSON;
        int index;
        std::string idPlane;
        std::string typePlane;
        int rowNumber;
        int colNumber;
        int flyTimes;
        bool isAvai = 0;
        std::fstream out;
        out.open("C://Users//Acer//code//slint-cpp-template//UI_DEMO//src//airplaneList.txt");
        out >> index;
        index--;
        out.ignore();
        for (int i = 0; i <= index; i++) {
            idPlane = "";
            typePlane = "";
            rowNumber = 0;
            colNumber = 0;
            flyTimes = 0;
            isAvai = false;
            std::getline(out, JSON);
            NS_myLib::parseJSON_Plane(idPlane, typePlane, rowNumber, colNumber, flyTimes, isAvai, JSON);
            this->addPlane(idPlane, typePlane, rowNumber, colNumber, flyTimes, isAvai);
        }
        out.close();
    }
    // Save Data
    void saveDataPlaneList() {
        std::fstream inp;
        inp.open("C://Users//Acer//code//slint-cpp-template//UI_DEMO//src//airplaneList.txt", std::ios::out);
        int n = this->countIndexPlane();
        inp << n << "\n";
        for (int i = 0; i <= n - 1; i++) {
            std::string JSON = NS_myLib::stringtifyJSON_Plane(this->data[i]->idPlane, this->data[i]->typePlane, this->data[i]->rowNumber, this->data[i]->colNumber, this->data[i]->flyTimes, this->data[i]->isAvai);
            inp << JSON << "\n";
        }
        inp.close();
    }
    // -- //
    void deletePlaneList() {
        for (int i = 0; i <= this->index; i++) delete this->data[i];
    }
    // -- //
    void getDataPlaneALL(airplane**& arrPlane, int& numberOfPlane) {
        numberOfPlane = index + 1;
        arrPlane = new airplane * [index + 1];
        for (int i = 0; i <= index; ++i) arrPlane[i] = data[i];
    }
    // -- //
    void getDataPlaneBySearch(airplane**& arrPlane, int& numberOfPlane, std::string searchPlaneCode) {
        arrPlane = new airplane * [index + 1];
        int k = -1;
        for (int i = 0; i <= index; ++i) {
            if (NS_myLib::ExistenceCheck(searchPlaneCode, data[i]->idPlane) == true) {
                arrPlane[++k] = data[i];
            }
        }
        numberOfPlane = k + 1;
    }
    // -- //
    airplane* getPlaneToEdit(std::string idPlane) {
        for (int i = 0; i <= index; ++i) {
            if ((data[i])->idPlane == idPlane) return data[i];
        }
        return nullptr;
    }
    // -- //
    void quickSortPlaneList_BYID(airplane** list, int l, int r) {
        if (r <= 0) return;
        airplane* temp = nullptr;
        string p = list[r]->idPlane;
        int i = l - 1, j = l;
        while (j <= r) {
            if (p < list[j]->idPlane) ++j;
            else {
                temp = list[++i];
                list[i] = list[j];
                list[j++] = temp;
            }
        }
        if (l + 1 < i) quickSortPlaneList_BYID(list, l, i - 1);
        if (i < r - 1) quickSortPlaneList_BYID(list, i + 1, r);
    }
    void quickSortPlaneList_BYSEAT(airplane** list, int l, int r) {
        if (r <= 0) return;
        airplane* temp = nullptr;
        int p = list[r]->colNumber * list[r]->rowNumber;
        int i = l - 1, j = l;
        while (j <= r) {
            if (p < (list[j]->colNumber * list[j]->rowNumber)) ++j;
            else {
                temp = list[++i];
                list[i] = list[j];
                list[j++] = temp;
            }
        }
        if (l + 1 < i) quickSortPlaneList_BYSEAT(list, l, i - 1);
        if (i < r - 1) quickSortPlaneList_BYSEAT(list, i + 1, r);
    }
    
    void selectionSortPlaneList_BYSTATUS(airplane** list, int n, int k) {
        airplane* temp = nullptr;
        if (k == 0) { // tim kiem cho unavailable len trc
            for (int i = 0; i <= n - 2; ++i) {
                for (int j = i + 1; j <= n - 1; ++j) {
                    if (list[i]->isAvai > list[j]->isAvai) {
                        temp = list[i];
                        list[i] = list[j];
                        list[j] = temp;
                    }
                }
            }
        }
        else {
            for (int i = 0; i <= n - 2; ++i) {
                for (int j = i + 1; j <= n - 1; ++j) {
                    if (list[i]->isAvai < list[j]->isAvai) {
                        temp = list[i];
                        list[i] = list[j];
                        list[j] = temp;
                    }
                }
            }
        }
    }
    void quickSortPlaneList_TYPE(airplane** list, int l, int r) {
        if (r <= 0) return;
        airplane* temp = nullptr;
        string p = list[r]->typePlane;
        int i = l - 1, j = l;
        while (j <= r) {
            if (p < list[j]->typePlane) ++j;
            else {
                temp = list[++i];
                list[i] = list[j];
                list[j++] = temp;
            }
        }
        if (l + 1 < i) quickSortPlaneList_TYPE(list, l, i - 1);
        if (i < r - 1) quickSortPlaneList_TYPE(list, i + 1, r);
    }

    void quickSortPlaneList_flightCount(airplane** list, int l, int r) {
        if (r <= 0) return;
        airplane* temp = nullptr;
        int p = list[r]->flyTimes;
        int i = l - 1, j = l;
        while (j <= r) {
            if (p < list[j]->flyTimes) ++j;
            else {
                temp = list[++i];
                list[i] = list[j];
                list[j++] = temp;
            }
        }
        if (l + 1 < i) quickSortPlaneList_flightCount(list, l, i - 1);
        if (i < r - 1) quickSortPlaneList_flightCount(list, i + 1, r);
    }
    // Destructor
    ~airplaneListClass() {};
};

