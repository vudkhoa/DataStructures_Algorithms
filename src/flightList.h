#pragma once
#include "ticket.h"
#include "myLib.h"
#include "TimeDate.h"
enum STATUS { CANCEL, AVAILABLE, UNAVAILABLE, COMPLETE };

struct info_flight {
    string flightCode;
    NS_dateTime::dateTime departure;
    string destination;
    STATUS flightStatus;
    string planeCode;
    int numberOfTicket_booked;
    int numberOfTicket_total;
    NS_Ticket::ticket* ticket_list = nullptr;

    info_flight() {}
    info_flight(string flightCode, NS_dateTime::dateTime departure, string destination, STATUS status, string planeCode, int numberOfTicket_booked, int numberOfTicket_total, NS_Ticket::ticket* listTicket) {
        this->flightCode = flightCode;
        this->departure = departure;
        this->destination = destination;
        this->flightStatus = status;
        this->planeCode = planeCode;
        this->numberOfTicket_booked = numberOfTicket_booked;
        this->numberOfTicket_total = numberOfTicket_total;
        this->ticket_list = listTicket;
    }
    void pr() {
        cout << "\n";
        cout << "FlightCODE: " << this->flightCode << endl;
        cout << " DateTime: " << NS_dateTime::getStringDateTime(this->departure) << endl;
        cout << " FromTo: " << this->destination << endl;
        cout << " STATUS: ";
        if (this->flightStatus == CANCEL) cout << "CANCLE";
        else if (this->flightStatus == AVAILABLE) cout << "AVAILABLE";
        else if (this->flightStatus == UNAVAILABLE) cout << "UNAVAILABLE";
        else if (this->flightStatus == COMPLETE) cout << "COMPLETE";
        cout << endl;
        cout << " PlaneCODE: " << this->planeCode << endl;
        cout << " ticket booked: " << this->numberOfTicket_booked << endl;
        cout << " ticket total: " << this->numberOfTicket_total << endl;
        cout << " Info_______________________________________________________________________________________" << endl;;
        for (int i = 0; i < numberOfTicket_booked; ++i) {
            ticket_list[i].prTicket();
        }
    }
    ~info_flight() {}
};

struct nodeFlight {
    info_flight information;
    nodeFlight* next;
    nodeFlight() {}
    nodeFlight(info_flight info) {
        this->information = info;
        this->next = nullptr;
    }
    ~nodeFlight() {}
};

class flightListCLASS {
    private:
        nodeFlight* head;
        int numberOfFlight;
    public:
        flightListCLASS() {
            head = nullptr;
            numberOfFlight = 0;
        }
        ~flightListCLASS() {}
        bool isEmpty() {
            return (this->head == nullptr ? true : false);
        }
        nodeFlight* getHead() {
            return head;
        }
        int getNumberOfFlight() {
            return numberOfFlight;
        }
        void pr() {
            nodeFlight* tmp = this->head;
            while (tmp != nullptr) {
                tmp->information.pr();
                tmp = tmp->next;
            }
        }
        nodeFlight* getFlightBySearch(std::string searchFlightCode) {
            nodeFlight* tmp = this->head;
            while (tmp != nullptr) {
                if (tmp->information.flightCode == searchFlightCode) {
                    return tmp;
                }
                tmp = tmp->next;
            }
            return nullptr;
        }
        // -- //
        void insert_last(nodeFlight*& head, info_flight flight) {
            nodeFlight* newNode = new nodeFlight(flight);
            if (head == nullptr) {
                head = newNode;
                numberOfFlight++;
                return;
            }
            else {
                nodeFlight* tmp = head;
                while (tmp->next != nullptr)
                    tmp = tmp->next;
                tmp->next = newNode;
                numberOfFlight++;
            }
            return;
        }
        // -- //
        void insertAfter(nodeFlight* head, info_flight flight) {
            if (head == nullptr) return;
            nodeFlight* newNode = new nodeFlight(flight);
            newNode->next = head->next;
            head->next = newNode;
            return;
        }
        // -- //
        void insertHere(nodeFlight* head, info_flight flight) {
            if (head == nullptr) return;
            insertAfter(head, flight);
            info_flight temp = head->information;
            head->information = (head->next)->information;
            (head->next)->information = temp;
        }
        // -- //
        void insertElement(info_flight infoFlight) {
            if (getFlightBySearch(infoFlight.flightCode) != nullptr) return;
            this->numberOfFlight++;
            nodeFlight* newNodeFlight = new nodeFlight(infoFlight);

            if (head == nullptr) {
                head = newNodeFlight;
                return;
            }
            nodeFlight* tmp = this->head;

            while ((tmp->information).flightCode < infoFlight.flightCode) {
                if (tmp->next == nullptr) {
                    tmp->next = newNodeFlight;
                    return;
                }
                tmp = tmp->next;
            }
            insertHere(tmp, infoFlight);
        }
        // -- //
        void takeDataALLForlistFlight(nodeFlight** &arr, int& getNumber_Flight) {
            getNumber_Flight = numberOfFlight;
            arr = new nodeFlight*[getNumber_Flight];
            int i = -1;
            nodeFlight* tmp = head;
            while (tmp != nullptr) {
                arr[++i] = tmp;
                tmp = tmp->next;
            }
        }
        // -- //
        void takeDATAbyFilterlistFlight_searchCode(nodeFlight** &arr, int & getNumber_Flight, string searchCode) {
            bool* finded = new bool[getNumber_Flight];
            for (int i = 0; i <= getNumber_Flight - 1; ++i) finded[i] = false;
            for (int i = 0; i <= getNumber_Flight - 1; ++i) {
                if (NS_myLib::ExistenceCheck(searchCode, arr[i]->information.flightCode) == true) {
                    finded[i] = true;
                }
            }
            int j = -1;
            for (int i = 0; i <= getNumber_Flight - 1; ++i) {
                if (finded[i] == true) {
                    arr[++j] = arr[i];
                }
            }
            getNumber_Flight = j + 1;
            delete[] finded;
        }
        void takeDATAbyFilterlistFlight_day(nodeFlight** &arr, int & getNumber_Flight, string day) {
            bool* finded = new bool[getNumber_Flight];
            for (int i = 0; i <= getNumber_Flight - 1; ++i) finded[i] = false;
            for (int i = 0; i <= getNumber_Flight - 1; ++i) {
                if (NS_myLib::String_to_Number(day) == NS_myLib::String_to_Number(arr[i]->information.departure.day)) {
                    finded[i] = true;
                }
            }
            int j = -1;
            for (int i = 0; i <= getNumber_Flight - 1; ++i) {
                if (finded[i] == true) {
                    arr[++j] = arr[i];
                }
            }
            getNumber_Flight = j + 1;
            delete[] finded;
        }
        void takeDATAbyFilterlistFlight_month(nodeFlight** &arr, int & getNumber_Flight, string month) {
            bool* finded = new bool[getNumber_Flight];
            for (int i = 0; i <= getNumber_Flight - 1; ++i) finded[i] = false;
            for (int i = 0; i <= getNumber_Flight - 1; ++i) {
                if (NS_myLib::String_to_Number(month) == NS_myLib::String_to_Number(arr[i]->information.departure.month)) {
                    finded[i] = true;
                }
            }
            int j = -1;
            for (int i = 0; i <= getNumber_Flight - 1; ++i) {
                if (finded[i] == true) {
                    arr[++j] = arr[i];
                }
            }
            getNumber_Flight = j + 1;
            delete[] finded;
        }
        void takeDATAbyFilterlistFlight_year(nodeFlight** &arr, int & getNumber_Flight, string year) {
            bool* finded = new bool[getNumber_Flight];
            for (int i = 0; i <= getNumber_Flight - 1; ++i) finded[i] = false;
            for (int i = 0; i <= getNumber_Flight - 1; ++i) {
                if (NS_myLib::String_to_Number(year) == NS_myLib::String_to_Number(arr[i]->information.departure.year)) {
                    finded[i] = true;
                }
            }
            int j = -1;
            for (int i = 0; i <= getNumber_Flight - 1; ++i) {
                if (finded[i] == true) {
                    arr[++j] = arr[i];
                }
            }
            getNumber_Flight = j + 1;
            delete[] finded;
        }

        void takeDATAbyFilterlistFlight_destination(nodeFlight** &arr, int & getNumber_Flight, string des) {
            bool* finded = new bool[getNumber_Flight];
            for (int i = 0; i <= getNumber_Flight - 1; ++i) finded[i] = false;
            for (int i = 0; i <= getNumber_Flight - 1; ++i) {
                if (NS_myLib::ExistenceCheck(des, arr[i]->information.destination)) {
                    finded[i] = true;
                }
            }
            int j = -1;
            for (int i = 0; i <= getNumber_Flight - 1; ++i) {
                if (finded[i] == true) {
                    arr[++j] = arr[i];
                }
            }
            getNumber_Flight = j + 1;
            delete[] finded;
        }
        // -- //
        void takeDATAbyperiod(nodeFlight** &arr, int & getNumber_Flight, NS_dateTime::dateTime start, NS_dateTime::dateTime end) {
            bool* finded = new bool[getNumber_Flight];
            for (int i = 0; i <= getNumber_Flight - 1; ++i) finded[i] = false;
            for (int i = 0; i <= getNumber_Flight - 1; ++i) {
                if (NS_dateTime::centerTimeA_B(start, end, arr[i]->information.departure) == true) {
                    finded[i] = true;
                }
            }
            int j = -1;
            for (int i = 0; i <= getNumber_Flight - 1; ++i) {
                if (finded[i] == true) {
                    arr[++j] = arr[i];
                }
            }
            getNumber_Flight = j + 1;
            delete[] finded;
        }
        // -- //
        void getDataFlightBySearch(info_flight *&arrFlight, std::string searchFlightCode) {
            nodeFlight *tmp = this->head;
            while (tmp != nullptr) {
                if (tmp->information.flightCode == searchFlightCode) {
                    arrFlight = &tmp->information;
                    return;
                }
                tmp = tmp->next;
            }
        }
        // -- //
        void deleteALLMemmory() {
            if (head == nullptr) return;
            nodeFlight* before = head;
            nodeFlight* after = head->next;
            while (before != nullptr) {
                delete before;
                before = after;
                if (after == nullptr) return;
                after = after->next;
            }
        }
        // -- //
        void parseJSON_Flight (std::string& flightCode, NS_dateTime::dateTime& departure, std::string& destination, STATUS& flightStatus, std::string& planeCode, int& numberOfTicket_booked, int& numberOfTicket_total, NS_Ticket::ticket*& ticket_list, std::string JSON) {
            flightCode = "";
            destination = "";
            planeCode = "";
            std::string strTicket_JSON = "";
            std::string strDateTime = "";
            std::string strStatus = "";
            std::string strNumberOfTicket_booked = "";
            std::string strNumberOfTicket_total = "";

            int length = ((int)JSON.length());
            int i = 0;
            for (; i <= length - 1; ++i) {
                if (JSON[i] != '#') {
                    flightCode = flightCode + JSON[i];
                }
                else break;
            }
            ++i;
            for (; i <= length - 1; ++i) {
                if (JSON[i] != '#') {
                    strDateTime = strDateTime + JSON[i];
                }
                else break;
            }
            departure = NS_dateTime::getTimeFormUnFormat(strDateTime);
            ++i;
            for (; i <= length - 1; ++i) {
                if (JSON[i] != '#') {
                    destination = destination + JSON[i];
                }
                else break;
            }
            ++i;
            for (; i <= length - 1; ++i) {
                if (JSON[i] != '#') {
                    strStatus = strStatus + JSON[i];
                }
                else break;
            }
            int status = NS_myLib::String_to_Number(strStatus);
            if (status == 0) flightStatus = CANCEL;
            else if (status == 1) flightStatus = AVAILABLE;
            else if (status == 2) flightStatus = UNAVAILABLE;
            else if (status == 3) flightStatus = COMPLETE;
            ++i;
            for (; i <= length - 1; ++i) {
                if (JSON[i] != '#') {
                    planeCode = planeCode + JSON[i];
                }
                else break;
            }
            ++i;
            for (; i <= length - 1; ++i) {
                if (JSON[i] != '#') {
                    strNumberOfTicket_booked = strNumberOfTicket_booked + JSON[i];
                }
                else break;
            }
            numberOfTicket_booked = String_to_Number(strNumberOfTicket_booked);

            ++i;
            for (; i <= length - 1; ++i) {
                if (JSON[i] != '#') {
                    strNumberOfTicket_total = strNumberOfTicket_total + JSON[i];
                }
                else break;
            }
            numberOfTicket_total = String_to_Number(strNumberOfTicket_total);
            
            ++i;
            if (numberOfTicket_booked == 0) {
                ticket_list = nullptr;
            }
            else {
                ticket_list = new NS_Ticket::ticket[numberOfTicket_booked];

                for (int j = 0; j < numberOfTicket_booked; ++j) {
                    for (; i <= length - 1; ++i) {
                        if (JSON[i] != '.') {
                            ticket_list[j].TICKET_CODE = ticket_list[j].TICKET_CODE + JSON[i];
                        }
                        else break;
                    }
                    ++i;
                    for (; i <= length - 1; ++i) {
                        if (JSON[i] != '#') {
                            ticket_list[j].IDCard = ticket_list[j].IDCard + JSON[i];
                        }
                        else break;
                    }
                    ++i;
                }
            }
        }
        // -- //
        void loadDataFlight() {
            std::string JSON;
            int index;

            std::string flightCode;
            NS_dateTime::dateTime departure;
            std::string destination;
            STATUS flightStatus;
            std::string planeCode;
            int numberOfTicket_booked = 0;
            int numberOfTicket_total = 0;
            NS_Ticket::ticket* ticket_list;

            std::fstream out;
            out.open("C://Users//Acer//code//slint-cpp-template//UI_DEMO//src//flightList.txt", ios::in);
            if (out.is_open()) cout << endl << "MO FILE THANH CONG" << endl;
            else cout << endl << "THAT BAI" << endl;

            out >> index;
            index--;
            out.ignore();
            for (int i = 0; i <= index; i++) {
                flightCode = "";
                destination = "";
                planeCode = "";
                numberOfTicket_booked = 0;
                numberOfTicket_total = 0;
                ticket_list = nullptr;

                std::getline(out, JSON);

                parseJSON_Flight(flightCode, departure, destination, flightStatus, planeCode, numberOfTicket_booked, numberOfTicket_total, ticket_list, JSON);

                info_flight tmp;
                tmp.flightCode = flightCode;
                tmp.departure = departure;
                tmp.destination = destination;
                tmp.flightStatus = flightStatus;
                tmp.planeCode = planeCode;
                tmp.numberOfTicket_booked = numberOfTicket_booked;
                tmp.numberOfTicket_total = numberOfTicket_total;
                tmp.ticket_list = ticket_list;
                insertElement(tmp);

            }
            out.close();
        }
        void saveDATAFlightList() {
            std::fstream in;
            in.open("C://Users//Acer//code//slint-cpp-template//UI_DEMO//src//flightList.txt", ios::out);
            if (in.is_open()) cout << endl << "MO FILE THANH CONG" << endl;
            else cout << endl << "THAT BAI" << endl;
            std::string JSON = "";

            in << numberOfFlight << endl;

            nodeFlight* tmp = this->head;
            while (tmp != nullptr) {
                JSON = tmp->information.flightCode + "#";
                JSON = JSON + NS_dateTime::getStringDateTime(tmp->information.departure) + "#";
                JSON = JSON + tmp->information.destination + "#";
                std::string strStatus;
                if (tmp->information.flightStatus == CANCEL) strStatus = "0";
                if (tmp->information.flightStatus == AVAILABLE) strStatus = "1";
                if (tmp->information.flightStatus == UNAVAILABLE) strStatus = "2";
                if (tmp->information.flightStatus == COMPLETE) strStatus = "3";
                JSON = JSON + strStatus + "#";
                JSON = JSON + tmp->information.planeCode + "#";
                JSON = JSON + NS_myLib::Number_to_String(tmp->information.numberOfTicket_booked) + "#";
                JSON = JSON + NS_myLib::Number_to_String(tmp->information.numberOfTicket_total);
                std::string strTicket = "";
                for (int i = 0; i <= tmp->information.numberOfTicket_booked - 1; ++i) {
                    strTicket = "#" + tmp->information.ticket_list[i].TICKET_CODE + "." +tmp->information.ticket_list[i].IDCard;
                    JSON = JSON + strTicket;
                }
                in << JSON << endl;
                tmp = tmp->next;
            }
        }
        // -- Selection Sort //
        void sort_ID(nodeFlight** arr, int n) {
            nodeFlight* tmp;
            for (int i = 0; i <= n - 2; ++i) {
                for (int j = i + 1; j <= n - 1; ++j) {
                    if (arr[i]->information.flightCode > arr[j]->information.flightCode) {
                        tmp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = tmp;
                    }
                }
            }
        }
        void sort_TIME(nodeFlight** arr, int n) {
            nodeFlight* tmp;
            for (int i = 0; i <= n - 2; ++i) {
                for (int j = i + 1; j <= n - 1; ++j) {
                    if (NS_dateTime::beforeAfter(arr[i]->information.departure, arr[j]->information.departure) == true) {
                        tmp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = tmp;
                    }
                }
            }
        }
};