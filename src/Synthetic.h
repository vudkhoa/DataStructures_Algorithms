#include "airplaneList.h"
#include "myLib.h"
#include "TimeDate.h"
#include "flightList.h"
#include "Passenger.h"
using namespace std;
namespace NS_synthetic {
    airplaneListClass airplaneListDATA; // co so du lieu chuyen bay chinh
    PassengerCLASS passengerListDATA; // co so du lieu hanh khach
    flightListCLASS flightListDATA; // co so du lieu chuyen bay
    // plane
    airplane* *airPlaneList_CPP = nullptr;
    int numberOfPlaneList_CPP = 0;

    void LoadDataToAirPlaneList() {
        airplaneListDATA.LoadDataPlaneList();
    }
    void SaveDataAirPlaneOnFile() {
        airplaneListDATA.saveDataPlaneList();
    }
    void takeData_airPlaneList(string searchCode_PlanePage) {
        if (searchCode_PlanePage == "") {
            airplaneListDATA.getDataPlaneALL(airPlaneList_CPP, numberOfPlaneList_CPP);
        }
        else {
            airplaneListDATA.getDataPlaneBySearch(airPlaneList_CPP, numberOfPlaneList_CPP, searchCode_PlanePage);
        }
    }
    string addPlaneToData_CPP(string ID, string Type, int ColNumber, int RowNumber) {
        if (ID.length() < 8) {
            return "Adding aircraft failed \nThe aircraft code must have 8 characters";
        }
        if (Type == "") return "The aircraft type field cannot be left blank.";     
        if ((ColNumber) <= 0) return "Column number must be greater than 0";
        if ((RowNumber) <= 0) return "Row number must be greater than 0";
        if (((RowNumber)) * ((ColNumber)) < 20) return "The number of seats \nmust be greater than 20";
        if (((RowNumber)) * ((ColNumber)) > 300) return "The number of seats \nmust be less than or equal to 300";
        return airplaneListDATA.addPlane(ID, Type, ColNumber, RowNumber, 0, true);
    }
    string deletePlaneOnData_CPP(string IDPlane) {
        if (false) { // may bay dang thuc hien 1 chuyen bay nao do
            return "The plane is making a flight";
        }
        return airplaneListDATA.deletePlane(IDPlane);
    } 
    
    string editPlaneToData_CPP(string oldId, int oldSEAT,string newId, string type, int col, int row) {
        if (oldId != newId &&  airplaneListDATA.findAirplane(newId) != -1) return "This aircraft code already exists";
        if (newId.length() < 8) return "aircraft failed \nThe aircraft code must have 8 characters";
        if (false) return ""; // ktra xem may bay co dang thuc hien chuyen bay hay khong/ hoac cho phep dong bo du lieu

        if (type == "") return "The aircraft type field cannot be left blank.";     
        if ((col) <= 0) return "Column number must be greater than 0";
        if ((row) <= 0) return "Row number must be greater than 0";
        if (((row)) * ((col)) < 20) return "The number of seats \nmust be greater than 20";

        if (((row)) * ((col)) > 300) return "The number of seats \nmust be less than or equal to 300";

        airplane *temp = airplaneListDATA.getPlaneToEdit(oldId);
        if (temp->isAvai == false) {
            if (((row)) * ((col)) < oldSEAT) return "The number of new seats must be \ngreater than the current number of seats";
        }
        if (temp == nullptr) return "Thao tac sai";

        nodeFlight** arr_flight_update_plane = nullptr;
        int n;

        flightListDATA.takeDataALLForlistFlight(arr_flight_update_plane, n);

        for (int i = 0; i <= n - 1; ++i) {
            if (arr_flight_update_plane[i]->information.planeCode == oldId && (arr_flight_update_plane[i]->information.flightStatus == AVAILABLE || arr_flight_update_plane[i]->information.flightStatus == UNAVAILABLE)) {
                arr_flight_update_plane[i]->information.planeCode = newId;
                arr_flight_update_plane[i]->information.numberOfTicket_total = col * row;
            }
        }

        temp->idPlane = newId;
        temp->typePlane = type;
        temp->colNumber = col;
        temp->rowNumber = row;
        return "Successfully edited the plane";
    }  

    void sortPlaneList_planePage_BYID() {
        airplaneListDATA.quickSortPlaneList_BYID(airPlaneList_CPP, 0, numberOfPlaneList_CPP - 1);
    }
    void sortPlaneList_planePage_BYSEAT() {
        airplaneListDATA.quickSortPlaneList_BYSEAT(airPlaneList_CPP, 0, numberOfPlaneList_CPP - 1);
    }
    void sortPlaneList_planePage_BYSTATUS_A() {
        airplaneListDATA.selectionSortPlaneList_BYSTATUS(airPlaneList_CPP, numberOfPlaneList_CPP, 1);
    }
    void sortPlaneList_planePage_BYSTATUS_U() {
        airplaneListDATA.selectionSortPlaneList_BYSTATUS(airPlaneList_CPP, numberOfPlaneList_CPP, 0);
    }

    // statatical
    airplane* *statistical_airPlaneList = nullptr;
    int statistical_numberOfPlaneList = 0;

    void statistical_takeData_airPlaneList(string searchCode_PlanePage) {
        if (searchCode_PlanePage == "") {
            airplaneListDATA.getDataPlaneALL(statistical_airPlaneList, statistical_numberOfPlaneList);
        }
        else {
            airplaneListDATA.getDataPlaneBySearch(statistical_airPlaneList, statistical_numberOfPlaneList, searchCode_PlanePage);
        }
    }
    void statistical_sortID() {
        airplaneListDATA.quickSortPlaneList_BYID(statistical_airPlaneList, 0, statistical_numberOfPlaneList - 1);
    }
    void statistical_sortTYPE() {
        airplaneListDATA.quickSortPlaneList_TYPE(statistical_airPlaneList, 0, statistical_numberOfPlaneList - 1);
    }
    void statistical_sortFCOUNT() {
        airplaneListDATA.quickSortPlaneList_flightCount(statistical_airPlaneList, 0, statistical_numberOfPlaneList - 1);
    }
    void statistical_MACDINH() {
        airplaneListDATA.getDataPlaneALL(statistical_airPlaneList, statistical_numberOfPlaneList);
    }
    //

    // Passenger
    nodeAVLPassenger* *ALLPassenger = nullptr;
    int numberOfALLPassenger = 0;
    void LoadDATAToALLPASSENGERLIST() {
        passengerListDATA.loadDataPassenger();
    }
    void saveDataALLPASSENGERTOFILE() {
        passengerListDATA.saveDataPassenger();
    }
    void takeDATA_ALL_PASSENGER(string searchIDCard_ALLPASS) {
        if (searchIDCard_ALLPASS == "") {
            passengerListDATA.takeDataOfALLPassenger(ALLPassenger, numberOfALLPassenger);
        }
        else {
            passengerListDATA.takeDataOfALLPassenger_SEARCH(ALLPassenger, numberOfALLPassenger, searchIDCard_ALLPASS);
        }
    }

    // //  edit apassenger ALLPAGE
    string editPassengerALLPAGE_TO_CPP(string oldID, string newID, string firstName, string lastName, int sex) {
        if (newID != oldID) {
            if (passengerListDATA.search(newID) == true) return "This ID Card already exists";
        }
        if (newID.length() < 13) return "ID card must have 13 characters";
        if (firstName.length() < 1) return "The First Name field cannot be left blank";
        if (lastName == "") return "The Last Name field cannot be left blank";
        nodeAVLPassenger* editPassenger;
        passengerListDATA.exist(oldID, editPassenger);
        if (editPassenger == nullptr) return "OCD OCE";
        editPassenger->info.idCard = newID;
        editPassenger->info.firstName = firstName;
        editPassenger->info.lastName = lastName;
        editPassenger->info.sex = (sex == 0) ? MALE : FEMALE;
        return "Successfully edited passenger information";
    }

    // add passenger
    string addPassengerALLPAGE_TO_CPP(string IDCard, string firstName, string lastName, int sex) {
        if (IDCard.length() < 13) return "ID card must have 13 characters";
        if (passengerListDATA.search(IDCard) == true) return "This ID Card already exists";
        if (firstName == "") return "The First Name field cannot be left blank";
        if (lastName == "") return "The Last Name field cannot be left blank";
        if (sex == 7) {
            return "Must choose gender";
        }
        Sex newP_Sex = (sex == 0) ? MALE : FEMALE;
        Passenger newPassenger(IDCard, firstName, lastName, newP_Sex);
        passengerListDATA.insertNode(newPassenger);
        return "Added passengers successfully";
    }

    void sortALLPASSENGERLIST_BYID() {
        passengerListDATA.sortPASSENGERLIST_BYID(ALLPassenger, numberOfALLPassenger);
    }
    void sortALLPASSENGERLIST_BYFirstName() {
        passengerListDATA.sortPASSENGERLIST_BYFirstName(ALLPassenger, numberOfALLPassenger);
    }
    void sortALLPASSENGERLIST_BYLAST() {
        passengerListDATA.sortPASSENGERLIST_BYLAST(ALLPassenger, numberOfALLPassenger);
    }
    void sortALLPASSENGERLIST_BYMALE() {
        passengerListDATA.sortPASSENGERLIST_BYMALE(ALLPassenger, numberOfALLPassenger);
    }
    void sortALLPASSENGERLIST_BYFEMALE() {
        passengerListDATA.sortPASSENGERLIST_BYFEMALE(ALLPassenger, numberOfALLPassenger);
    }

    // flight
    nodeFlight* *flightList = nullptr;
    int numberOfFlight = 0;
    void LoadDataToFListFlight() {
        flightListDATA.loadDataFlight();
    }
    void saveDATAListFlight() {
        flightListDATA.saveDATAFlightList();
    }
    void takeDATAToflightList(string searchCode, string day, string month, string year, string des) {
        flightListDATA.takeDataALLForlistFlight(flightList, numberOfFlight); // khi nay minh se co tat ca cac phan tu
        if (searchCode != "") {
            flightListDATA.takeDATAbyFilterlistFlight_searchCode(flightList, numberOfFlight, searchCode);
        }
        if (day != "") {
            flightListDATA.takeDATAbyFilterlistFlight_day(flightList, numberOfFlight, day);
        }
        if (month != "") {
            flightListDATA.takeDATAbyFilterlistFlight_month(flightList, numberOfFlight, month);
        }
        if (year != "") {
            flightListDATA.takeDATAbyFilterlistFlight_year(flightList, numberOfFlight, year);
        }
        if (des != "") {
            flightListDATA.takeDATAbyFilterlistFlight_destination(flightList, numberOfFlight, des);
        }
    }   

    void sortFlightList_BYID_CPP() {
        flightListDATA.sort_ID(flightList, numberOfFlight);
    }
    void sortFlightList_BYTIME_CPP() {
        flightListDATA.sort_TIME(flightList, numberOfFlight);
    }
    
    string cancelFlight(string flightCode) {
        nodeFlight* tmp = flightListDATA.getFlightBySearch(flightCode);
        if (tmp == nullptr) return "NULL";
        tmp->information.flightStatus = CANCEL;
        airplane* pl = airplaneListDATA.getPlaneToEdit(tmp->information.planeCode);
        if (pl == nullptr) return "NULL";
        pl->isAvai = true;
        return "Flight canceled successfully";
    }

    void updateFlightByTime() {
        nodeFlight*tmp = NS_synthetic::flightListDATA.getHead();
        airplane* plane = nullptr;
        while (tmp != nullptr) {
            NS_dateTime::Format(tmp->information.departure);

            if (NS_dateTime::pastFuture(tmp->information.departure) == false) {
                if (tmp->information.flightStatus == CANCEL) continue;
                if (tmp->information.flightStatus == AVAILABLE || tmp->information.flightStatus == UNAVAILABLE) {
                    tmp->information.flightStatus = COMPLETE;
                    plane = NS_synthetic::airplaneListDATA.getPlaneToEdit(tmp->information.planeCode);
                    plane->isAvai = true;
                    plane->increaseFlyTimes();
                }
            }
            tmp = tmp->next;
        }
    }

    // add flight
    string addFlight_to_CPP(string flightCode, string day, string month, string year, string hour, string minute, string destination, string planeCode) {
        if (flightCode.length() != 8) return "Flight Code must have 8 characters";
        if (flightListDATA.getFlightBySearch(flightCode) != nullptr) {
            return "This flight code already exists";
        }
        airplane* tmp = airplaneListDATA.getPlaneToEdit(planeCode);
        if (tmp == nullptr) return "No plane found";
        else {
            if (tmp->isAvai == false) return "The plane is on another flight *";
        }
        tmp->isAvai = false; //????
        NS_dateTime::dateTime departure(day, month, year, hour, minute, "");
        NS_dateTime::Format(departure);
        STATUS stt = AVAILABLE;
        NS_Ticket::ticket *ticketList = nullptr;
        info_flight newFlight(flightCode, departure, destination, stt, planeCode, 0, tmp->colNumber * tmp->rowNumber, ticketList);
        flightListDATA.insertElement(newFlight);
        return "Successful flight initiation";
    }

    // edit flight
    bool checkFlightCanEdit(string flightCode) {
        nodeFlight* tmp = flightListDATA.getFlightBySearch(flightCode);
        if (tmp->information.flightStatus == CANCEL || tmp->information.flightStatus == COMPLETE) {
            return false;
        }
        return true;
    }
    string editflight_to_cpp(string oldFlightCode, string newFlightCode, string day, string month, string year, string hour, string minute, string destination, string planeCode) {
        if (newFlightCode.length() != 8) return "Flight Code must have 8 characters";
        nodeFlight* nodeF = flightListDATA.getFlightBySearch(oldFlightCode);
        if (oldFlightCode != newFlightCode) {
            if (flightListDATA.getFlightBySearch(newFlightCode) != nullptr) {
                return "This flight code already exists";
            }
        }
        airplane* oldPlane = airplaneListDATA.getPlaneToEdit(nodeF->information.planeCode);
        airplane* tmp = airplaneListDATA.getPlaneToEdit(planeCode);
        if (tmp == nullptr) return "No plane found";
        else {
            if (tmp->isAvai == false && nodeF->information.planeCode != planeCode) return "The plane is on another flight *";
        }
        if (oldPlane->colNumber * oldPlane->rowNumber > tmp->colNumber * tmp->rowNumber) return "The number of new aircraft seat \nmust be larger than the old aircraft";
        oldPlane->isAvai = true;
        tmp->isAvai = false;
        // thay doi

        nodeF->information.flightCode = newFlightCode;
        NS_dateTime::dateTime departure(day, month, year, hour, minute, "");
        NS_dateTime::Format(departure);
        nodeF->information.departure = departure;
        nodeF->information.destination = destination;
        nodeF->information.planeCode = planeCode;
        nodeF->information.numberOfTicket_total = tmp->colNumber * tmp->rowNumber;
        return "Flight editing was successful";
    }
    void filterFlightBetween(NS_dateTime::dateTime start, NS_dateTime::dateTime end) {
        flightListDATA.takeDataALLForlistFlight(flightList, numberOfFlight);
        flightListDATA.takeDATAbyperiod(flightList, numberOfFlight, start, end);
    }
    // --------------------

    // flightOFPASSENGERPAGE
    nodeFlight** flightListOfPassengerPage = nullptr;
    int numberOfFlightPassengerPage = 0;

    void takeDATAToflightList_PassengerPage(string searchCode, string day, string month, string year, string des) {
        flightListDATA.takeDataALLForlistFlight(flightListOfPassengerPage, numberOfFlightPassengerPage); // khi nay minh se co tat ca cac phan tu
        if (searchCode != "") {
            flightListDATA.takeDATAbyFilterlistFlight_searchCode(flightListOfPassengerPage, numberOfFlightPassengerPage, searchCode);
        }
        if (day != "") {
            flightListDATA.takeDATAbyFilterlistFlight_day(flightListOfPassengerPage, numberOfFlightPassengerPage, day);
        }
        if (month != "") {
            flightListDATA.takeDATAbyFilterlistFlight_month(flightListOfPassengerPage, numberOfFlightPassengerPage, month);
        }
        if (year != "") {
            flightListDATA.takeDATAbyFilterlistFlight_year(flightListOfPassengerPage, numberOfFlightPassengerPage, year);
        }
        if (des != "") {
            flightListDATA.takeDATAbyFilterlistFlight_destination(flightListOfPassengerPage, numberOfFlightPassengerPage, des);
        }
    }   

    // Ticket
    int ticket_numberOfFlightList = 0;

    info_flight *ticket_flight = nullptr;
    airplane ticket_airplane;
    Passenger *ticket_passenger = nullptr;
    int number_PassengerFlight = 0;
    Passenger *passengerListFlight = nullptr;
    Passenger *SLINT_flightPassenger = nullptr;
    
    void ticket_takeData_flight(string searchFlightCode) {
        flightListDATA.getDataFlightBySearch(ticket_flight, searchFlightCode);
        std::cout << endl;
        std::cout << "Day: " <<  ticket_flight->departure.day << endl;
        std::cout << "Month: " << ticket_flight->departure.month << endl;
        std::cout << "Year: " << ticket_flight->departure.year << endl;
        std::cout << "Hour: " << ticket_flight->departure.hour << endl;
        std::cout << "Minute: " << ticket_flight->departure.minute;
        std::cout << endl;
        ticket_flight->pr();
    } 
    void ticket_takeData_airplane() {
        std::cout << "\n";
        std::string planeCode = ticket_flight->planeCode;
        int index = airplaneListDATA.findAirplane(planeCode);
        if (index == -1) {
            ticket_airplane.typePlane = "######";
            ticket_airplane.idPlane = "########";
            return;
        }
        ticket_airplane = airplaneListDATA.get_data(index);
        ticket_airplane.prInfo();
    }
    
    void ticket_takeData_search_passenger(std::string IDCARD) {
        ticket_passenger = nullptr;
        cout << "Find: " << endl;
        passengerListDATA.getInfo_bySearch(ticket_passenger, IDCARD);
        if (ticket_passenger != nullptr) ticket_passenger->prInfo();
    }
    void ticket_addPassenger(std::string IDCARD, string TICKET_CODE, std::string firstName, std::string lastName, int sex) {
        cout << ticket_flight->numberOfTicket_booked << endl;
        cout << IDCARD << " " << TICKET_CODE << endl;
        NS_Ticket::push(ticket_flight->ticket_list, ticket_flight->numberOfTicket_booked, IDCARD, TICKET_CODE);
        Passenger tmp;
        tmp.firstName = firstName;
        tmp.lastName = lastName;
        tmp.idCard = IDCARD;
        if (sex == 1) tmp.sex = MALE;
        else if (sex == 2) tmp.sex = FEMALE;
        passengerListDATA.insertNode(tmp);

        cout << endl << "Danh sach hanh khach cap nhat: ";
        passengerListDATA.show();
        cout << endl;
        // ticket_flight->pr();
        flightListDATA.pr();
    }
    void ticket_erasePassenger(std::string IDCARD) {
        NS_Ticket::pull(ticket_flight->ticket_list, ticket_flight->numberOfTicket_booked, IDCARD);
        ticket_flight->pr();
        flightListDATA.pr();
    }
    void ticket_takeData_cancel_passenger(string &lastName, string &firstName, string &idCard, int &sex, string TICKET_CODE) {
        for (int i = 0; i < ticket_flight->numberOfTicket_booked; ++i) {
            if (TICKET_CODE == ticket_flight->ticket_list[i].TICKET_CODE) {
                idCard = ticket_flight->ticket_list[i].IDCard;
                ticket_passenger = nullptr;
                passengerListDATA.getInfo_bySearch(ticket_passenger, idCard);
                if (ticket_passenger != nullptr) {
                    firstName = ticket_passenger->firstName;
                    lastName = ticket_passenger->lastName;
                    if (ticket_passenger->sex == 0) sex = 1;
                    else sex = 2;
                }
                return;
            }
        }
    }
    void passengerListFlight_search(string idCard) {
        int dem = 0;
        cout << endl << "START";
        cout << endl << "ID: " << idCard << endl;
        for (int i = 0; i < NS_synthetic::ticket_flight->numberOfTicket_booked; ++i) {
            if (NS_myLib::ExistenceCheck(idCard, NS_synthetic::passengerListFlight[i].idCard) == true) {
                cout << "FIND:";
                
                dem++;
            }
        }
        Passenger *PF = nullptr;
        PF = new Passenger [dem];
        NS_synthetic::number_PassengerFlight = dem;
        dem = -1;
        for (int i = 0; i < NS_synthetic::ticket_flight->numberOfTicket_booked; ++i) {
            if (NS_myLib::ExistenceCheck(idCard, NS_synthetic::passengerListFlight[i].idCard) == true) {
                dem++;
                PF[dem] = NS_synthetic::passengerListFlight[i];
            }
        }
        NS_synthetic::SLINT_flightPassenger = PF;
        cout << "END" << endl;
    }
    void passengerListFlight_takeData_list () {
        passengerListFlight = new Passenger [ticket_flight->numberOfTicket_booked];
        number_PassengerFlight = ticket_flight->numberOfTicket_booked;
        for (int i = 0; i < ticket_flight->numberOfTicket_booked; ++i) {
            Passenger *x = nullptr;
            passengerListDATA.getInfo_bySearch(x, ticket_flight->ticket_list[i].IDCard);
            passengerListFlight[i].idCard = x->idCard;
            passengerListFlight[i].firstName = x->firstName;
            passengerListFlight[i].lastName = x->lastName;
            passengerListFlight[i].sex = x->sex;
            // passengerListFlight[i].prInfo();
        } 
        SLINT_flightPassenger = passengerListFlight;
    }

    void ticket_sortPassengerList (int IDSort) {
        cout << "Chose_sort: " << IDSort << endl;
        if (IDSort == 1) {
            passengerListDATA.sortTICKETPASSENGERLIST_BYID(SLINT_flightPassenger, number_PassengerFlight);
            passengerListDATA.sortTICKETPASSENGERLIST_BYID(passengerListFlight, ticket_flight->numberOfTicket_booked);
        }
        else if (IDSort == 0) {
            passengerListFlight_takeData_list();
            
        }
        else if (IDSort == 2) {
            passengerListDATA.sortTICKETPASSENGERLIST_BYNAME(SLINT_flightPassenger, number_PassengerFlight);
            passengerListDATA.sortTICKETPASSENGERLIST_BYNAME(passengerListFlight, ticket_flight->numberOfTicket_booked);
        }
    }

    void Release_memory() {
        airplaneListDATA.deletePlaneList();
        delete[] airPlaneList_CPP;
        delete[] statistical_airPlaneList;
        passengerListDATA.deleteAll();
        delete[] ALLPassenger;
        flightListDATA.deleteALLMemmory();
        delete[] flightList;
        delete[] flightListOfPassengerPage;
        delete[] ticket_passenger;
        delete[] SLINT_flightPassenger;
        // delete[] ticket_flight;
        // delete[] passengerListFlight;
    }
}
