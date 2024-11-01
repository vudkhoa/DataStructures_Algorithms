#include "homePage.h"
#include <iostream>
#include <string>
#include "slint.h"
#include "Synthetic.h"
#include <vector>
#include <thread>
#include "myLib.h"
using namespace std;
string currentTime = NS_myLib::getStringClock(NS_myLib::getCurrClock());
void RenderListPlane(auto ui) {
    std::vector <plane> DataTorenderListPlane_CPP;
    plane temp;
    for (int i = 0; i <= NS_synthetic::numberOfPlaneList_CPP - 1; ++i) {
        temp.IDPlane = NS_synthetic::airPlaneList_CPP[i]->idPlane;
        temp.typePlane = NS_synthetic::airPlaneList_CPP[i]->typePlane;
        temp.ColNumber = NS_synthetic::airPlaneList_CPP[i]->colNumber;
        temp.RowNumber = NS_synthetic::airPlaneList_CPP[i]->rowNumber;
        temp.isAvai = NS_synthetic::airPlaneList_CPP[i]->isAvai;
        DataTorenderListPlane_CPP.push_back(temp);
    }
    auto DataTorenderListPlane_SLINT = std::make_shared<slint::VectorModel<plane>>(DataTorenderListPlane_CPP);
    ui->global<functionAPP>().set_PlanePage_PlaneList(DataTorenderListPlane_SLINT);
    ui->global<functionAPP>().set_PlanePage_numberOfPlaneList(NS_synthetic::numberOfPlaneList_CPP);
}
// ---------------------
void statistical_RenderListPlane(auto ui) {
    std::vector <plane> DataTorenderListPlane_CPP;
    plane temp;
    for (int i = 0; i <= NS_synthetic::statistical_numberOfPlaneList - 1; ++i) {
        temp.IDPlane = NS_synthetic::statistical_airPlaneList[i]->idPlane;
        temp.typePlane = NS_synthetic::statistical_airPlaneList[i]->typePlane;
        temp.ColNumber = NS_synthetic::statistical_airPlaneList[i]->colNumber;
        temp.RowNumber = NS_synthetic::statistical_airPlaneList[i]->rowNumber;
        temp.isAvai = NS_synthetic::statistical_airPlaneList[i]->isAvai;
        temp.flyTimes = NS_synthetic::statistical_airPlaneList[i]->flyTimes;
        DataTorenderListPlane_CPP.push_back(temp);
    }
    auto DataTorenderListPlane_SLINT = std::make_shared<slint::VectorModel<plane>>(DataTorenderListPlane_CPP);
    // list statistical
    ui->global<statistical_data>().set_statisticalPage_planeList(DataTorenderListPlane_SLINT);

    if (NS_synthetic::statistical_numberOfPlaneList != 0) 
        ui->global<statistical_global>().set_size_airplaneList(NS_synthetic::statistical_numberOfPlaneList);
    else ui->global<statistical_global>().set_size_airplaneList(-1);
}


void ticket_Render_information(auto ui, info_flight *info, airplane ticket_airplane, int ticket_list_size, NS_Ticket::ticket *ticket_list) {
    ticket DATA_ticket; 
    DATA_ticket.info.IDPlane = ticket_airplane.idPlane;
    DATA_ticket.info.typePlane = ticket_airplane.typePlane;
    DATA_ticket.info.ColNumber = ticket_airplane.colNumber;
    DATA_ticket.info.RowNumber = ticket_airplane.rowNumber;
    DATA_ticket.info.isAvai = ticket_airplane.isAvai;
    DATA_ticket.info.flyTimes = ticket_airplane.flyTimes;
    ui->global<ticket_global>().set_flightStatus(info->flightStatus);
    ui->global<ticket_global>().set_flightCode(NS_myLib::to_shared_string(info->flightCode));
    std::string time = "";
    time = time + info->departure.hour + ":" + info->departure.minute;
    cout << time << endl;
    ui->global<ticket_global>().set_information(DATA_ticket);
    ui->global<ticket_global>().set_toFlight(NS_myLib::to_shared_string(info->destination));

    ui->global<ticket_global>().set_timeDepartingFlight(NS_myLib::to_shared_string(time));
    time = "";

    // NS_dateTime::plusThreeHour(info->departure.day, info->departure.month, info->departure.year, info->departure.hour, info->departure.minute);
    time = NS_dateTime::plusThreeHour(info->departure.day, info->departure.month, info->departure.year, info->departure.hour, info->departure.minute);

    cout << time << endl;
    ui->global<ticket_global>().set_timeArrivingFlight(NS_myLib::to_shared_string(time));
    time = "";
    time = time + info->departure.day + "/" + info->departure.month + "/" + info->departure.year;
    cout << time << endl;
    ui->global<ticket_global>().set_dateFlight(NS_myLib::to_shared_string(time));
}

void ticket_render_rowcol(auto ui, info_flight *info, airplane ticket_airplane, int ticket_list_size, NS_Ticket::ticket *ticket_list) {
    vector <index> tmp_row;

    for (int i = 0; i < ticket_airplane.rowNumber; ++i) {
        tmp_row.push_back({ticket_airplane.rowNumber, ticket_airplane.colNumber, false});
    }
    auto apply_ticket_row = std::make_shared<slint::VectorModel<index>>(tmp_row);
    ui->global<ticket_global>().set_row(apply_ticket_row);

    vector <index> tmp_col;
    for (int i = 0; i < ticket_airplane.colNumber; ++i) {
        tmp_col.push_back({ticket_airplane.rowNumber, ticket_airplane.colNumber, false});
    }
    auto apply_ticket_col = std::make_shared<slint::VectorModel<index>>(tmp_col);
    ui->global<ticket_global>().set_col(apply_ticket_col);

    vector <index> chosse;
    for (int i = 0; i < ticket_airplane.rowNumber; ++i) {
        for (int j = 0; j < ticket_airplane.colNumber; ++j) {
            chosse.push_back({i, j, false});
        }
    }
    for (int z = 0; z < ticket_list_size; z++) {
        chosse[NS_myLib::String_to_Number(ticket_list[z].TICKET_CODE)].check = true;
    }
    auto apply_ticket_chosse = std::make_shared<slint::VectorModel<index>>(chosse);
    ui->global<ticket_global>().set_z(apply_ticket_chosse);
}

void ticket_render_z(auto ui, airplane ticket_airplane, int ticket_list_size, NS_Ticket::ticket *ticket_list) {
    vector <index> chosse;
    for (int i = 0; i < ticket_airplane.rowNumber; ++i) {
        for (int j = 0; j < ticket_airplane.colNumber; ++j) {
            chosse.push_back({i, j, false});
        }
    }
    for (int z = 0; z < ticket_list_size; z++) {
        chosse[NS_myLib::String_to_Number(ticket_list[z].TICKET_CODE)].check = true;
    }
    auto apply_ticket_chosse = std::make_shared<slint::VectorModel<index>>(chosse);
    ui->global<ticket_global>().set_z(apply_ticket_chosse);
}

void ticket_render_passengerList(auto ui, Passenger *SLINT_flightPassenger) {
    vector <passengerSLINT> information;
    for(int i = 0; i < NS_synthetic::number_PassengerFlight; ++i) {
        passengerSLINT tmp;
        tmp.IDCard = NS_myLib::to_shared_string(SLINT_flightPassenger[i].idCard);
        tmp.firstName = NS_myLib::to_shared_string(SLINT_flightPassenger[i].firstName);
        tmp.lastName = NS_myLib::to_shared_string(SLINT_flightPassenger[i].lastName);
        if (SLINT_flightPassenger[i].sex == MALE) tmp.sex = 0;
        else tmp.sex = 1;
        for (int j = 0; j < NS_synthetic::ticket_flight->numberOfTicket_booked; ++j) {
            if (NS_synthetic::ticket_flight->ticket_list[j].IDCard == SLINT_flightPassenger[i].idCard) {
                tmp.seat = NS_myLib::String_to_Number(NS_synthetic::ticket_flight->ticket_list[j].TICKET_CODE);
                break;
            }
        }
        information.push_back(tmp);
    }
    auto apply_ticket_passengerList = std::make_shared<slint::VectorModel<passengerSLINT>>(information);
    ui->global<ticket_global>().set_passengerList(apply_ticket_passengerList);
}

void ALLPASSENGER_RenderList(auto ui) {
    std::vector <passengerSLINT> DATAToRenderLISTALLPASSENGER;
    passengerSLINT temp;
    for (int i = 0; i <= NS_synthetic::numberOfALLPassenger - 1; ++i) {
        temp.IDCard = NS_synthetic::ALLPassenger[i]->info.idCard;
        temp.firstName = NS_synthetic::ALLPassenger[i]->info.firstName;
        temp.lastName = NS_synthetic::ALLPassenger[i]->info.lastName;
        temp.sex = NS_synthetic::ALLPassenger[i]->info.sex;
        DATAToRenderLISTALLPASSENGER.push_back(temp);
    }
    auto DATATORENDER = std::make_shared<slint::VectorModel<passengerSLINT>>(DATAToRenderLISTALLPASSENGER);
    ui->global<functionAPP>().set_AllPassengerPage_listAllPassenger(DATATORENDER);
    ui->global<functionAPP>().set_AllPassengerPage_numberOfPassengerList(NS_synthetic::numberOfALLPassenger);
}

void RENDER_flightList(auto ui) {
    std::vector <flightSLINT> DATAtoRENDERLISTFLIGHT;
    flightSLINT temp;
    for (int i = 0; i <= NS_synthetic::numberOfFlight - 1; ++i) {
        temp.flightCode = NS_synthetic::flightList[i]->information.flightCode;
        temp.departure = NS_dateTime::getStringDateTime(NS_synthetic::flightList[i]->information.departure);
        temp.destination = NS_synthetic::flightList[i]->information.destination;
        if (NS_synthetic::flightList[i]->information.flightStatus == CANCEL) temp.state = 0;
        if (NS_synthetic::flightList[i]->information.flightStatus == AVAILABLE) temp.state = 1;
        if (NS_synthetic::flightList[i]->information.flightStatus == UNAVAILABLE) temp.state = 2;
        if (NS_synthetic::flightList[i]->information.flightStatus == COMPLETE) temp.state = 3;
        temp.planeCode = NS_synthetic::flightList[i]->information.planeCode;
        temp.numberOfTicket_BOOKED = NS_synthetic::flightList[i]->information.numberOfTicket_booked;
        temp.totalTicket = NS_synthetic::flightList[i]->information.numberOfTicket_total;
        DATAtoRENDERLISTFLIGHT.push_back(temp);
    }
    auto DATAflightListSLINT = std::make_shared<slint::VectorModel<flightSLINT>>(DATAtoRENDERLISTFLIGHT);
    ui->global<functionAPP>().set_flightLIST_flightPage(DATAflightListSLINT);
    ui->global<functionAPP>().set_numberOfFlightList_flightPage(NS_synthetic::numberOfFlight);
}

void renderListFlight_PassengerPage(auto ui) {
    std::vector <flightSLINT> DATAtoRENDERLISTFLIGHT;
    flightSLINT temp;
    for (int i = 0; i <= NS_synthetic::numberOfFlightPassengerPage - 1; ++i) {
        temp.flightCode = NS_synthetic::flightListOfPassengerPage[i]->information.flightCode;
        temp.departure = NS_dateTime::getStringDateTime(NS_synthetic::flightListOfPassengerPage[i]->information.departure);
        temp.destination = NS_synthetic::flightListOfPassengerPage[i]->information.destination;
        if (NS_synthetic::flightListOfPassengerPage[i]->information.flightStatus == CANCEL) temp.state = 0;
        if (NS_synthetic::flightListOfPassengerPage[i]->information.flightStatus == AVAILABLE) temp.state = 1;
        if (NS_synthetic::flightListOfPassengerPage[i]->information.flightStatus == UNAVAILABLE) temp.state = 2;
        if (NS_synthetic::flightListOfPassengerPage[i]->information.flightStatus == COMPLETE) temp.state = 3;
        temp.planeCode = NS_synthetic::flightListOfPassengerPage[i]->information.planeCode;
        temp.numberOfTicket_BOOKED = NS_synthetic::flightListOfPassengerPage[i]->information.numberOfTicket_booked;
        temp.totalTicket = NS_synthetic::flightListOfPassengerPage[i]->information.numberOfTicket_total;
        DATAtoRENDERLISTFLIGHT.push_back(temp);
    }
    auto DATAflightListSLINT = std::make_shared<slint::VectorModel<flightSLINT>>(DATAtoRENDERLISTFLIGHT);
    ui->global<functionAPP>().set_passengerPage_listFlight(DATAflightListSLINT);
    ui->global<functionAPP>().set_passengerPage_numberOfListFlight(NS_synthetic::numberOfFlightPassengerPage);
}
slint::SharedString to_shared_string(const string& stdString){
    return slint::SharedString(stdString); 
}
string to_std_string(const slint::SharedString& ShaStr){
    return string(ShaStr);
}
void thread2() {
    auto ui = homePage::create();
    NS_myLib::clockDateTime curr = NS_myLib::getCurrClock();
    
    NS_synthetic::LoadDataToAirPlaneList(); // chung cho plane va statictical
    NS_synthetic::LoadDATAToALLPASSENGERLIST(); // lay du lieu danh sach hanh khach
    NS_synthetic::LoadDataToFListFlight();
    // Khoi hien thi ban dau-----------------------------------------------------------------------------------------
    NS_synthetic::takeDATAToflightList("", "", "", "", "");
    NS_synthetic::takeData_airPlaneList("");
    NS_synthetic::statistical_takeData_airPlaneList(""); 
    NS_synthetic::takeDATA_ALL_PASSENGER("");
    NS_synthetic::takeDATAToflightList_PassengerPage("","","","","");

    RenderListPlane(ui);
    statistical_RenderListPlane(ui);
    ALLPASSENGER_RenderList(ui);
    RENDER_flightList(ui);
    renderListFlight_PassengerPage(ui);
    // --------------------------------------------------------------------------------------------------------------
    //  khoi thoi gian
    ui->global<functionAPP>().on_getDayFromStringTime([&] (slint::SharedString time) -> slint::SharedString {
        std::string std_time(time);
        NS_dateTime::dateTime temp = NS_dateTime::getTimeFormUnFormat(std_time);
        return slint::SharedString(temp.day);
    });
    ui->global<functionAPP>().on_getMonthFromStringTime([&] (slint::SharedString time) -> slint::SharedString {
        std::string std_time(time);
        NS_dateTime::dateTime temp = NS_dateTime::getTimeFormUnFormat(std_time);
        return slint::SharedString(temp.month);
    });
    ui->global<functionAPP>().on_getYearFromStringTime([&] (slint::SharedString time) -> slint::SharedString {
        std::string std_time(time);
        NS_dateTime::dateTime temp = NS_dateTime::getTimeFormUnFormat(std_time);
        return slint::SharedString(temp.year);
    });
    ui->global<functionAPP>().on_getMinuteFromStringTime([&] (slint::SharedString time) -> slint::SharedString {
        std::string std_time(time);
        NS_dateTime::dateTime tmp = NS_dateTime::getTimeFormUnFormat(std_time);
        return slint::SharedString(tmp.minute);
    });
    ui->global<functionAPP>().on_getHourFromStringTime([&] (slint::SharedString time) -> slint::SharedString {
        std::string std_time(time);
        NS_dateTime::dateTime tmp = NS_dateTime::getTimeFormUnFormat(std_time);
        return slint::SharedString(tmp.hour);
    });

    //
    // KHOI CHUAN HOA NHAP XUAT
    ui->global<functionAPP>().on_standardInputFlightCode([&] (slint::SharedString inp, slint::SharedString lastValue) -> slint::SharedString {
        std::string myStr(inp);
        std::string myLastValue(lastValue);
        myStr = NS_myLib::standardInputFlightCode(myStr, myLastValue);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputFlightCode([&] (slint::SharedString inp) -> slint::SharedString {
        std::string myStr(inp);
        return slint::SharedString(NS_myLib::checkInputFlightCode(myStr));
    });

    ui->global<functionAPP>().on_standardInputFlightCodeSearch([&] (slint::SharedString inp, slint::SharedString lastValue) -> slint::SharedString {
        std::string myStr(inp);
        std::string myLastValue(lastValue);
        myStr = NS_myLib::standardInputFlightCodeSearch(myStr, myLastValue);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputFlightCodeSearch([&] (slint::SharedString inp) -> slint::SharedString {
        std::string myStr(inp);
        return slint::SharedString(NS_myLib::checkInputFlightCodeSearch(myStr));
    });

    ui->global<functionAPP>().on_standardInputDay([&] (slint::SharedString str, slint::SharedString lastValue) -> slint::SharedString {
        std::string myStr(str);
        std::string myLastValue((lastValue));
        myStr = NS_myLib::standardInputDay(myStr, myLastValue);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputDay([&] (slint::SharedString str) -> slint::SharedString {
        std::string myStr(str);
        return slint::SharedString(NS_myLib::checkInputDay(myStr));
    });

    ui->global<functionAPP>().on_standardInputMonth([&] (slint::SharedString str, slint::SharedString lastValue) -> slint::SharedString {
        std::string myStr(str);
        std::string mylastValue(lastValue);
        myStr = NS_myLib::standardInputMonth(myStr, mylastValue);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputMonth([&] (slint::SharedString str) -> slint::SharedString {
        std::string myStr(str);
        return slint::SharedString(NS_myLib::checkInputMonth(myStr));
    });

    ui->global<functionAPP>().on_standardInputYear([&] (slint::SharedString str, slint::SharedString lastValue) -> slint::SharedString {
        std::string myStr(str);
        std::string myLastvalue(lastValue);
        myStr = NS_myLib::standardInputYear(myStr, myLastvalue);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputYear([&] (slint::SharedString str) -> slint::SharedString {
        std::string myStr(str);
        return slint::SharedString(NS_myLib::checkInputYear(myStr));
    });

    ui->global<functionAPP>().on_standardInputHour([&] (slint::SharedString str, slint::SharedString lastValue) -> slint::SharedString {
        std::string myStr(str);
        std::string myLast(lastValue);
        myStr = NS_myLib::standardInputHour(myStr, myLast);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputHour([&] (slint::SharedString str) -> slint::SharedString {
        std::string myStr(str);
        return slint::SharedString(NS_myLib::checkInputHour(myStr));
    });

    ui->global<functionAPP>().on_standardInputMinute([&] (slint::SharedString str, slint::SharedString lastValue) -> slint::SharedString {
        std::string myStr(str);
        std::string myLast(lastValue);
        myStr = NS_myLib::standardInputMinute(myStr, myLast);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputMinute([&] (slint::SharedString str) -> slint::SharedString {
        std::string myStr(str);
        return slint::SharedString(NS_myLib::checkInputMinute(myStr));
    });

    ui->global<functionAPP>().on_standardInputDes([&] (slint::SharedString str, slint::SharedString lastValue) -> slint::SharedString {
        std::string myStr(str);
        std::string myLastValue(lastValue);
        myStr = NS_myLib::standardInputDes(myStr, myLastValue);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputDes([&] (slint::SharedString str) -> slint::SharedString {
        std::string myStr(str);
        return slint::SharedString(NS_myLib::checkInputDes(myStr));
    });

    ui->global<functionAPP>().on_standardInputIDPlane([&] (slint::SharedString str, slint::SharedString lastvalue) -> slint::SharedString {
        std::string myStr(str);
        std::string myLastvalue(lastvalue);
        myStr = NS_myLib::standardInputIDPlane(myStr, myLastvalue);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputIDPlane([&] (slint::SharedString str) -> slint::SharedString {
        std::string myStr(str);
        return slint::SharedString(NS_myLib::checkInputIDPlane(myStr));
    });

    ui->global<functionAPP>().on_standardInputIDPlaneSearch([&] (slint::SharedString str, slint::SharedString lastvalue) -> slint::SharedString {
        std::string myStr(str);
        std::string myLastvalue(lastvalue);
        myStr = NS_myLib::standardInputIDPlaneSearch(myStr, myLastvalue);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputIDPlaneSearch([&] (slint::SharedString str) -> slint::SharedString {
        std::string myStr(str);
        return slint::SharedString(NS_myLib::checkInputIDPlaneSearch(myStr));
    });

    ui->global<functionAPP>().on_standardInputNumber([&] (slint::SharedString str, slint::SharedString lasValue) -> slint::SharedString {
        std::string myStr(str);
        std::string myLastValue(lasValue);
        myStr = NS_myLib::standardInputNumber(myStr, myLastValue);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputNumber([&] (slint::SharedString str) -> slint::SharedString {
        std::string myStr(str);
        return slint::SharedString(NS_myLib::checkInputNumber(myStr));
    });

    ui->global<functionAPP>().on_standardInputIDCard([&] (slint::SharedString IDCard, slint::SharedString lastValue) -> slint::SharedString {
        std::string myStr(IDCard);
        std::string myLastValue(lastValue);
        myStr = NS_myLib::standardInputNumberIDCard(myStr, myLastValue);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputIDCard([&] (slint::SharedString str) -> slint::SharedString {
        std::string myStr(str);
        return slint::SharedString(NS_myLib::checkInputNumberIDCard(myStr));
    });

    ui->global<functionAPP>().on_standardInputFirstName([&] (slint::SharedString firstName, slint::SharedString lastValue) -> slint::SharedString {
        std::string myStr(firstName);
        std::string myLast(lastValue);
        myStr = NS_myLib::standardInputFirstName(myStr, myLast);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputFirstName([&] (slint::SharedString str) -> slint::SharedString {
        std::string myStr(str);
        return slint::SharedString(NS_myLib::checkInputFirstName(myStr));
    });

    ui->global<functionAPP>().on_standardInputLastName([&] (slint::SharedString lastName, slint::SharedString lastValue) -> slint::SharedString {
        std::string myStr(lastName);
        std::string myLast(lastValue);
        myStr = NS_myLib::standardInputLastName(myStr, myLast);
        return slint::SharedString(myStr);
    });
    ui->global<functionAPP>().on_catchErorrInputLastName([&] (slint::SharedString str) -> slint::SharedString {
        std::string myStr(str);
        return slint::SharedString(NS_myLib::checkInputLastName(myStr));
    });
    // --------------------------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------------------------
    // KHOI XU LY THONG TIN
    ui->global<functionAPP>().on_handlePassengerPage_searchFlight_BYCPP([&] (slint::SharedString DAY, slint::SharedString MONTH, slint::SharedString YEAR, slint::SharedString DES, slint::SharedString FilterFLIGHT_CODE) -> slint::SharedString {
        std::string day(DAY);
        std::string month(MONTH);
        std::string year(YEAR);
        std::string des(DES);
        std::string flightCode(FilterFLIGHT_CODE);
        NS_dateTime::dateTime passengerPageDATETIME_INPUT(day, month, year, "0", "0", "0");
        if (day != "" && month != "" && year != "" ) { // co day du ngay thang nam
            if (NS_dateTime::checkDate(passengerPageDATETIME_INPUT) == false) return "This Time do not exits";
            // loc danh sach trong TH co du ngay thang nam
        }
        if (day != "" && month != "" && year == "") { // chi co ngay thang
            if (NS_dateTime::checkDate_Day_Month(passengerPageDATETIME_INPUT) == false) return "This Time do not exits";
            // loc danh sach trong TH co ngay thang
        }
        NS_synthetic::takeDATAToflightList_PassengerPage(flightCode, day, month, year, des);
        renderListFlight_PassengerPage(ui);
        return "";
    });

    ui->global<functionAPP>().on_checkPlaneAvailable([&] (slint::SharedString idPlane) -> bool {
        std::string STD_IDPLANE(idPlane);
        airplane* temp =  NS_synthetic::airplaneListDATA.getPlaneToEdit(STD_IDPLANE);
        if (temp != nullptr) {
            if (temp->isAvai == true) return true;
        }
        return false;
    });
    ui->global<functionAPP>().on_handlAddPlaneByCPP([&] (slint::SharedString addPlaneID, slint::SharedString addTypePlane, slint::SharedString addColNumber, slint::SharedString addRowNumber, slint::SharedString searcodePlanePage) -> slint::SharedString {
        std::string ID(addPlaneID);
        std::string Type(addTypePlane);
        std::string ColNumber(addColNumber);
        std::string RowNumber(addRowNumber);  
        std::string searcodePlanePageSTD(searcodePlanePage);
        string status;
        status = slint::SharedString(NS_synthetic::addPlaneToData_CPP(ID, Type, NS_myLib::String_to_Number(ColNumber), NS_myLib::String_to_Number(RowNumber)));
        NS_synthetic::takeData_airPlaneList("");
        NS_synthetic::statistical_takeData_airPlaneList("");
        RenderListPlane(ui);
        statistical_RenderListPlane(ui);
        return slint::SharedString(status);
    });

    ui->global<functionAPP>().on_handleEditPlane_PlanePageByCPP([&] (slint::SharedString IDPLANE_BEFORE_EDIT, int SEAT_BEFORE_EDIT,slint::SharedString ID_PLANE_A_E, slint::SharedString TYPEPLANE_A_E, slint::SharedString ColPLANE_A_E, slint::SharedString RowPLANE_A_E, slint::SharedString searchCodePlanePage, int modeSearch) -> slint::SharedString {
        std::string STD_ID_BE(IDPLANE_BEFORE_EDIT);
        std::string STD_ID_AE(ID_PLANE_A_E);
        std::string STD_TYPE_AE(TYPEPLANE_A_E);
        std::string STD_COL_AE(ColPLANE_A_E);
        std::string STD_ROW_AE(RowPLANE_A_E);
        std::string STD_searchCode(searchCodePlanePage);
        auto rs = slint::SharedString(NS_synthetic::editPlaneToData_CPP(STD_ID_BE, SEAT_BEFORE_EDIT, STD_ID_AE, STD_TYPE_AE, NS_myLib::String_to_Number(STD_COL_AE), NS_myLib::String_to_Number(STD_ROW_AE)));
        if (modeSearch == 1) {
            NS_synthetic::sortPlaneList_planePage_BYID();
        }
        if (modeSearch == 2) {
            NS_synthetic::sortPlaneList_planePage_BYSEAT();
        }
        if (modeSearch == 3) {
            NS_synthetic::sortPlaneList_planePage_BYSTATUS_A();
        }
        if (modeSearch == 4) {
            NS_synthetic::sortPlaneList_planePage_BYSTATUS_U();
        }
        RENDER_flightList(ui);
        RenderListPlane(ui);
        statistical_RenderListPlane(ui);
        return rs;
    });

    ui->global<functionAPP>().on_handleSearchPlane_PlanePageByID_BYCPP([&] (slint::SharedString SEARCH_IDPLANE_INP_PlanePage) {
        std::string STD_SEARCH_ID_PLANE_PlP(SEARCH_IDPLANE_INP_PlanePage);
        NS_synthetic::takeData_airPlaneList(STD_SEARCH_ID_PLANE_PlP);
        RenderListPlane(ui);
    });

    ui->global<functionAPP>().on_handleDeletePlaneCPP([&] (slint::SharedString str, slint::SharedString searchCodePlane) {
        string status;
        std::string myStr(str);
        std::string STD_searchodeo(searchCodePlane);
        status = slint::SharedString(NS_synthetic::deletePlaneOnData_CPP(myStr));
        NS_synthetic::takeData_airPlaneList(STD_searchodeo);
        NS_synthetic::statistical_takeData_airPlaneList(STD_searchodeo);
        RenderListPlane(ui);
        statistical_RenderListPlane(ui);
        return slint::SharedString(status);
    });
    ui->global<functionAPP>().on_handleSortPlaneList_BYID([&] () {
        NS_synthetic::sortPlaneList_planePage_BYID();
        RenderListPlane(ui);
    });

    ui->global<functionAPP>().on_handleSortPlanePlist_BYSEAT([&] () {
        NS_synthetic::sortPlaneList_planePage_BYSEAT();
        RenderListPlane(ui);
    });

    ui->global<functionAPP>().on_handleSortPlaneList_BYSTATUS_A([&] () {
        NS_synthetic::sortPlaneList_planePage_BYSTATUS_A();
        RenderListPlane(ui);
    });

    ui->global<functionAPP>().on_handleSortPlaneList_BYSTATUS_U([&] () {
        NS_synthetic::sortPlaneList_planePage_BYSTATUS_U();
        RenderListPlane(ui);
    });

    ui->global<statistical_data>().on_get_dataSLINT([&] (slint::SharedString a) -> string {
        std::string planeCode (a);
        string check = "";
        check = NS_myLib::checkInputIDPlaneSearch(planeCode);
        return string(check);
    });

    ui->global<statistical_data>().on_standardize_planeCode([&] (slint::SharedString a) -> slint::SharedString {
        std::string str(a);
        for (int i = 0; i < str.length(); i++) {
            NS_myLib::toUppercase(str[i]);
        }
        return slint::SharedString(str);
    });

    ui->global<statistical_data>().on_find_planeCode([&] (slint::SharedString slint_str){
        vector <plane> informationPlane_tmp;
        std::string str(slint_str);
        NS_synthetic::statistical_takeData_airPlaneList(str);
        statistical_RenderListPlane(ui);
    }); 

    ui->global<statistical_data>().on_sort_click([&] (int a) {
        int ID_SORT(a);
        if (ID_SORT == 1) NS_synthetic::statistical_sortID();
        else if (ID_SORT == 2) NS_synthetic::statistical_sortTYPE();
        else if (ID_SORT == 3) NS_synthetic::statistical_sortFCOUNT();
        else NS_synthetic::statistical_MACDINH();
        statistical_RenderListPlane(ui);
    });

    // search ID Card ALL PASS PAGE
    ui->global<functionAPP>().on_handleSearch_ALLPassenger_BYCPP([&] (slint::SharedString searchCodeIDCard_ALL_PP) {
        std::string mySearchCode(searchCodeIDCard_ALL_PP);
        NS_synthetic::takeDATA_ALL_PASSENGER(mySearchCode);
        ALLPASSENGER_RenderList(ui);
        return;
    });


    // sort passenger ALL
    ui->global<functionAPP>().on_handleSortPassengerALLLASSPAFE_ID([&] () {
        NS_synthetic::sortALLPASSENGERLIST_BYID();
        ALLPASSENGER_RenderList(ui);
    });
    ui->global<functionAPP>().on_handleSortPassengerALLLASSPAFE_FirstName([&] () {
        NS_synthetic::sortALLPASSENGERLIST_BYFirstName();
        ALLPASSENGER_RenderList(ui);
    });
    ui->global<functionAPP>().on_handleSortPassengerALLLASSPAFE_LastName([&] () {
        NS_synthetic::sortALLPASSENGERLIST_BYLAST();
        ALLPASSENGER_RenderList(ui);
    });
    ui->global<functionAPP>().on_handleSortPassengerALLLASSPAFE_Sex_MALE([&] () {
        NS_synthetic::sortALLPASSENGERLIST_BYMALE();
        ALLPASSENGER_RenderList(ui);
    });
    ui->global<functionAPP>().on_handleSortPassengerALLLASSPAFE_Sex_FEMALE([&] () {
        NS_synthetic::sortALLPASSENGERLIST_BYFEMALE();
        ALLPASSENGER_RenderList(ui);
    });

    // edit passenger PASSALL
    ui->global<functionAPP>().on_handleEditPass_ALLPASS_byCPP([&] (slint::SharedString IDCard_BE, slint::SharedString IDCard_AE, slint::SharedString newFirstName, slint::SharedString newLastName, int newSex, slint::SharedString searchIDPAseengger) -> slint::SharedString {
        std::string STD_ID_BE(IDCard_BE);
        std::string STD_ID_AE(IDCard_AE);
        std::string STD_FN(newFirstName);
        std::string STD_LN(newLastName);
        std::string STD_SEARCHCODE(searchIDPAseengger);
        auto rs = slint::SharedString(NS_synthetic::editPassengerALLPAGE_TO_CPP(STD_ID_BE, STD_ID_AE, STD_FN, STD_LN, newSex)); // string tra ve ket qua cua viec chinh sua
        ALLPASSENGER_RenderList(ui);
        return rs;
    });

    ui->global<functionAPP>().on_handleADDPASSENGER_ALLPASS_BYCPP([&] (slint::SharedString ID, slint::SharedString firstName, slint::SharedString lastName, int sex, slint::SharedString searchCODE) {
        std::string STD_ID(ID);
        std::string STD_FIRSTNAME(firstName);
        std::string STD_LASTNAME(lastName);
        std::string STD_SEARCHCODE(searchCODE);
        string resultADD = NS_synthetic::addPassengerALLPAGE_TO_CPP(STD_ID, STD_FIRSTNAME, STD_LASTNAME, sex);

        NS_synthetic::takeDATA_ALL_PASSENGER("");
        ALLPASSENGER_RenderList(ui);
        return slint::SharedString(resultADD);
    });

    ui->global<functionAPP>().on_exit([&] () {

    });

    ui->global<functionAPP>().on_connect_passengerFlight([&] (slint::SharedString searchFlightCode){
        string flightCode(searchFlightCode);
        ui->global<ticket_global>().set_seat_passenger(-1);
        ui->global<ticket_global>().set_chose_passengerListFlight_list(-1);
        NS_synthetic::ticket_takeData_flight(flightCode);
        NS_synthetic::ticket_takeData_airplane();
        ticket_Render_information(ui, NS_synthetic::ticket_flight, NS_synthetic::ticket_airplane, NS_synthetic::ticket_flight->numberOfTicket_booked, NS_synthetic::ticket_flight->ticket_list);
        ticket_render_rowcol(ui, NS_synthetic::ticket_flight, NS_synthetic::ticket_airplane, NS_synthetic::ticket_flight->numberOfTicket_booked, NS_synthetic::ticket_flight->ticket_list);
        NS_synthetic::passengerListFlight_takeData_list();
        ticket_render_passengerList(ui, NS_synthetic::SLINT_flightPassenger);
    });


    ui->global<functionAPP>().on_handleFilter_period_BYCPP([&] (slint::SharedString startDay, slint::SharedString startMonth, slint::SharedString startYear, slint::SharedString endDay, slint::SharedString endMonth,slint::SharedString endYear) -> slint::SharedString {
        std::string stDay(startDay);
        std::string stMonth(startMonth);
        std::string stYear(startYear);
        std::string edDay(endDay);
        std::string edMonth(endMonth);
        std::string edYear(endYear);

        if (stDay == "") return "The Day Start field cannot be left blank";
        if (stMonth == "") return "The Month Start field cannot be left blank";
        if (stYear == "") return "The Year Start field cannot be left blank";

        if (edDay == "") return "The Day End field cannot be left blank";
        if (edMonth == "") return "The Month End field cannot be left blank";
        if (edYear == "") return "The Year End field cannot be left blank";
        NS_dateTime::dateTime start(stDay, stMonth, stYear, "0", "0", "0"); NS_dateTime::Format(start);
        NS_dateTime::dateTime end(edDay, edMonth, edYear, "23", "59", "59"); NS_dateTime::Format(end);

        if (NS_dateTime::checkDate(start) == false) return startDay + "/" + startMonth + "/" + startYear + " do not exits";
        int yearNumber = NS_myLib::String_to_Number(stYear);
        if (yearNumber < 1980 || yearNumber > 2100) return "1980 <= start year <= 2100";

        if (NS_dateTime::checkDate(end) == false) return endDay+ "/" + endMonth + "/" + endYear + " do not exits";
        yearNumber = NS_myLib::String_to_Number(edYear);
        if (yearNumber < 1980 || yearNumber > 2100) return "1980 <= end year <= 2100";

        if (NS_dateTime::beforeAfter(start, end) == false) {
            return "Time start must lie before time end";
        }
        NS_synthetic::filterFlightBetween(start, end);
        RENDER_flightList(ui);
        return "";
    });
    ui->global<functionAPP>().on_sortFlightList_BYID([&] {
        NS_synthetic::sortFlightList_BYID_CPP();
        RENDER_flightList(ui);
    });
    ui->global<functionAPP>().on_sortFlightList_BYTIME([&] {
        NS_synthetic::sortFlightList_BYTIME_CPP();
        RENDER_flightList(ui);
    });
    ui->global<functionAPP>().on_handleFilter_search_flightPage_BYCPP([&] (slint::SharedString flightCodeSearch, slint::SharedString day, slint::SharedString month, slint::SharedString year, slint::SharedString des) -> slint::SharedString {
        std::string STD_flightCode(flightCodeSearch);
        std::string STD_day(day);
        std::string STD_month(month);
        std::string STD_year(year);
        std::string STD_des(des);
        NS_dateTime::dateTime DATETIME_INPUT_FLIGHTSEARCH(STD_day, STD_month, STD_year, "0", "0", "0");
        if (STD_day != "" && STD_month != "" && STD_year != "") {
                if (NS_dateTime::checkDate(DATETIME_INPUT_FLIGHTSEARCH) == false) return day + "/" + month + "/" + year + " do not exits";
        }

        if (STD_day != "" && STD_month != "" && STD_year == "") {
                if (NS_dateTime::checkDate_Day_Month(DATETIME_INPUT_FLIGHTSEARCH) == false) return day + "/" + month + " do not exits";
        }
        if (STD_year != "") {
                int year_num = NS_myLib::String_to_Number(STD_year);
                if (year_num < 1980 || year_num > 2100) {
                    return "1980 <= year <= 2100";    
                }
        }

        NS_synthetic::takeDATAToflightList(STD_flightCode, STD_day, STD_month, STD_year, STD_des);
        RENDER_flightList(ui);
        return "";
    });

    ui->global<functionAPP>().on_handleADDFLIGHT_BYCPP([&] (slint::SharedString flightCode, slint::SharedString day, slint::SharedString month, slint::SharedString year, slint::SharedString hour, slint::SharedString minute, slint::SharedString des, slint::SharedString idPlaneHasChoose, slint::SharedString searchCODE) -> slint::SharedString {
        std::string STD_flightCode(flightCode);
        std::string STD_day(day);
        std::string STD_month(month);
        std::string STD_year(year);
        std::string STD_hour(hour);
        std::string STD_minute(minute);
        std::string STD_des(des);
        std::string STD_idPlane(idPlaneHasChoose);

        std::string STD_searchCode(searchCODE);

        if (STD_flightCode == "") return "The flight code field cannot be left blank";
        if (STD_day == "") return "The Day field cannot be left blank";
        if (STD_month == "") return "The Month field cannot be left blank";
        if (STD_year == "") return "The Year field cannot be left blank";
        if (STD_hour == "") return  "The Hour field cannot be left blank";
        if (STD_minute == "") return  "The Minute field cannot be left blank";
        if (STD_des == "") return  "The Destination field cannot be left blank";
        if (STD_idPlane == "") return  "The ID Plane field cannot be left blank";

        NS_dateTime::dateTime DATETIME_INPUT_FLIGHTSEARCH(STD_day, STD_month, STD_year, STD_hour, STD_minute, "");

        if (STD_day != "" && STD_month != "" && STD_year != "") {
            if (NS_dateTime::checkDate(DATETIME_INPUT_FLIGHTSEARCH) == false) return day + "/" + month + "/" + year + " do not exits";
        }
        if (STD_day != "" && STD_month != "" && STD_year == "") {
            if (NS_dateTime::checkDate_Day_Month(DATETIME_INPUT_FLIGHTSEARCH) == false) return day + "/" + month + " do not exits";
        }
        if (STD_year != "") {
            int year_num = NS_myLib::String_to_Number(STD_year);
            if (year_num < 1980 || year_num > 2100) {
                return "1980 <= year <= 2100";
            }
        }
        if (NS_dateTime::pastFuture(DATETIME_INPUT_FLIGHTSEARCH) == false) {
            return "Do not initialize flights in the past";
        }
        if (NS_dateTime::checkTimeBefore(DATETIME_INPUT_FLIGHTSEARCH) < 180) {
            return "The flight must be initiated at \nleast 3 hours from the current date";
        }
        std::string resultAddFlight = NS_synthetic::addFlight_to_CPP(STD_flightCode, STD_day, STD_month, STD_year, STD_hour, STD_minute, STD_des, STD_idPlane);

        NS_synthetic::takeDATAToflightList("", "", "", "", "");
        NS_synthetic::takeDATAToflightList_PassengerPage("","","","","");
        renderListFlight_PassengerPage(ui);
        RenderListPlane(ui);
        RENDER_flightList(ui);
        return slint::SharedString(resultAddFlight);
    });

    ui->global<functionAPP>().on_checkFlightCanEdit([&] (slint::SharedString flightCode) -> bool {
        std::string std_flightCode(flightCode);
        return NS_synthetic::checkFlightCanEdit(std_flightCode);
    });
    ui->global<functionAPP>().on_checkFlightToCancel([&] (slint::SharedString flightCode) -> int {
        std::string std_flightCode(flightCode);
        nodeFlight* tmp = NS_synthetic::flightListDATA.getFlightBySearch(std_flightCode);
        if (tmp == nullptr) return 0;
        if (tmp->information.flightStatus == CANCEL) return 1;
        if (tmp->information.flightStatus == COMPLETE) return 2;
        return 0;
    });
    ui->global<functionAPP>().on_handleEditFlight_BYCPP([&] (slint::SharedString oldFLightCode, slint::SharedString newID, slint::SharedString day, slint::SharedString month, slint::SharedString year, slint::SharedString hour, slint::SharedString minute, slint::SharedString des, slint::SharedString idPlane) -> slint::SharedString {
        std::string std_oldFlightCode(oldFLightCode);
        std::string std_newFlightCode(newID);
        std::string std_day(day);
        std::string std_month(month);
        std::string std_year(year);
        std::string std_hour(hour);
        std::string std_minute(minute);
        std::string std_des(des);
        std::string std_idPlane(idPlane);
        std::string resultEditFlight = "";

        if (std_newFlightCode == "") return "The new flight code field cannot be left blank";
        if (std_day == "") return "The Day field cannot be left blank";
        if (std_month == "") return "The Month field cannot be left blank";
        if (std_year == "") return "The Year field cannot be left blank";
        if (std_hour == "") return  "The Hour field cannot be left blank";
        if (std_minute == "") return  "The Minute field cannot be left blank";
        if (std_des == "") return  "The Destination field cannot be left blank";
        if (std_idPlane == "") return  "The ID Plane field cannot be left blank";

        NS_dateTime::dateTime DATETIME_INPUT_FLIGHTSEARCH(std_day, std_month, std_year, std_hour, std_minute, "");

        if (std_day != "" && std_month != "" && std_year != "") {
            if (NS_dateTime::checkDate(DATETIME_INPUT_FLIGHTSEARCH) == false) return day + "/" + month + "/" + year + " do not exits";
        }
        if (std_day != "" && std_month != "" && std_year == "") {
            if (NS_dateTime::checkDate_Day_Month(DATETIME_INPUT_FLIGHTSEARCH) == false) return day + "/" + month + " do not exits";
        }
        if (std_year != "") {
            int year_num = NS_myLib::String_to_Number(std_year);
            if (year_num < 1980 || year_num > 2100) {
                return "1980 <= year <= 2100";
            }
        }
        if (NS_dateTime::pastFuture(DATETIME_INPUT_FLIGHTSEARCH) == false) {
            return "Do not initialize flights in the past";
        }
        if (NS_dateTime::checkTimeBefore(DATETIME_INPUT_FLIGHTSEARCH) < 180) {
            return "The flight must be initiated at \nleast 3 hours from the current date";
        }

        resultEditFlight = NS_synthetic::editflight_to_cpp(std_oldFlightCode, std_newFlightCode, std_day, std_month, std_year, std_hour, std_minute, std_des, std_idPlane);
        RenderListPlane(ui);
        RENDER_flightList(ui);
        renderListFlight_PassengerPage(ui);
        return slint::SharedString(resultEditFlight);
    }); 

    ui->global<functionAPP>().on_handleCancelFlight_BYCPP([&] (slint::SharedString flightCode) -> slint::SharedString {
        std::string std_flightCode(flightCode);
        string rsCancel = NS_synthetic::cancelFlight(std_flightCode);
        RENDER_flightList(ui);
        RenderListPlane(ui);
        return slint::SharedString(rsCancel);
    });

    ui->global<functionAPP>().on_handleBookFlight_BYCPP([&] (slint::SharedString flightCode) -> slint::SharedString {
        std::string std_flightCode(flightCode);
        NS_synthetic::ticket_takeData_flight(std_flightCode);
        NS_synthetic::ticket_takeData_airplane();
        ticket_Render_information(ui, NS_synthetic::ticket_flight, NS_synthetic::ticket_airplane, NS_synthetic::ticket_flight->numberOfTicket_booked, NS_synthetic::ticket_flight->ticket_list);
        ticket_render_rowcol(ui, NS_synthetic::ticket_flight, NS_synthetic::ticket_airplane, NS_synthetic::ticket_flight->numberOfTicket_booked, NS_synthetic::ticket_flight->ticket_list);
        NS_synthetic::passengerListFlight_takeData_list();
        ticket_render_passengerList(ui, NS_synthetic::SLINT_flightPassenger);
        cout << std_flightCode << "$$$" << endl;
        return "";
    });
    
    ui->global<ticket_global>().on_standardize([&] (slint::SharedString a) -> slint::SharedString {
        std::string str(a);
        for (int i = 0; i < str.length(); i++) {
            NS_myLib::toUppercase(str[i]);
        }
        return slint::SharedString(str);
    });
    ui->global<ticket_global>().on_getCPP_information([&] (slint::SharedString slint_str) -> slint::SharedString {
        std::string idcard(slint_str);
        std::string temp = idcard;
        std::cout << temp << "\n";
        Passenger information;
        int bought_ticket = -1;
        idcard = NS_myLib::checkInputIDCARD(idcard);
        if (idcard == "" && temp.length() == 13) {
            NS_synthetic::ticket_takeData_search_passenger(temp);
            if (NS_synthetic::ticket_passenger != nullptr) {
                for (int i = 0; i < NS_synthetic::ticket_flight->numberOfTicket_booked; i++) {
                    if (NS_synthetic::ticket_passenger->idCard == NS_synthetic::ticket_flight->ticket_list[i].IDCard) {
                        bought_ticket = NS_myLib::String_to_Number(NS_synthetic::ticket_flight->ticket_list[i].TICKET_CODE);
                        ui->global<ticket_global>().set_bought_ticket(bought_ticket);
                        return slint::SharedString(NS_myLib::to_shared_string("               Each person\nis only allowed to book one ticket"));
                    }
                }
                ui->global<ticket_global>().set_book_information_firstName(NS_myLib::to_shared_string(NS_synthetic::ticket_passenger->firstName));
                ui->global<ticket_global>().set_book_information_lastName(NS_myLib::to_shared_string(NS_synthetic::ticket_passenger->lastName));
                if (NS_synthetic::ticket_passenger->sex == 0) {ui->global<ticket_global>().set_book_information_sex(NS_myLib::to_shared_string("MALE"));}
                else {ui->global<ticket_global>().set_book_information_sex(NS_myLib::to_shared_string("FEMALE"));}
            }
            else {
                ui->global<ticket_global>().set_book_information_firstName(NS_myLib::to_shared_string("Enter the First name"));
                ui->global<ticket_global>().set_book_information_lastName(NS_myLib::to_shared_string("Enter the last name"));
                ui->global<ticket_global>().set_book_information_sex(NS_myLib::to_shared_string("Enter the Sex"));
                ui->global<ticket_global>().set_chose_sex(0);
                bought_ticket = -1;
                ui->global<ticket_global>().set_bought_ticket(bought_ticket);
            }
        }
        else if (idcard != "" && temp.length() == 14) {        }
        else {
                ui->global<ticket_global>().set_book_information_firstName(NS_myLib::to_shared_string("Enter the First name"));
                ui->global<ticket_global>().set_book_information_lastName(NS_myLib::to_shared_string("Enter the last name"));
                ui->global<ticket_global>().set_book_information_sex(NS_myLib::to_shared_string("Enter the Sex"));
                ui->global<ticket_global>().set_chose_sex(0);
                bought_ticket = -1;
                ui->global<ticket_global>().set_bought_ticket(bought_ticket);
            }
        return slint::SharedString(idcard);
    });
    ui->global<ticket_global>().on_getCPP_information_book_firstName([&] (slint::SharedString slint_str) -> slint::SharedString {
        std::string str(slint_str);
        str = NS_myLib::ticket_checkInputFirstName(str);
        return slint::SharedString(str);
    });
    ui->global<ticket_global>().on_getCPP_information_book_lastName([&] (slint::SharedString slint_str) -> slint::SharedString {
        std::string str(slint_str);
        str = NS_myLib::ticket_checkInputLastName(str);
        return slint::SharedString(str);
    });
    ui->global<ticket_global>().on_getCPP_information_cancel([&] (int index) {
        int ID(index);
        string TICKET_CODE = Number_to_String(ID);
        string idCard = "";
        string lastName = "";
        string firstName = "";
        int sex = 0;
        NS_synthetic::ticket_takeData_cancel_passenger(lastName, firstName, idCard, sex, TICKET_CODE);
        ui->global<ticket_global>().set_cancel_information_idCard(NS_myLib::to_shared_string(idCard));
        ui->global<ticket_global>().set_cancel_information_firstName(NS_myLib::to_shared_string(firstName));
        ui->global<ticket_global>().set_cancel_information_lastName(NS_myLib::to_shared_string(lastName));
        ui->global<ticket_global>().set_cancel_information_sex(sex);
    });
    ui->global<ticket_global>().on_buttonNext_book([&] (slint::SharedString a, slint::SharedString b, slint::SharedString c, int d, int e) {
        std::string idcard(a);
        std::string lastname(b);
        std::string firstname(c);
        int sex(d);
        int chose_seat(e);
        cout << endl << idcard << " " << firstname << " " << lastname; 
        NS_synthetic::ticket_addPassenger(idcard, NS_myLib::Number_to_String(chose_seat), firstname, lastname, sex);
        NS_synthetic::passengerListFlight_takeData_list(); 
        ticket_render_passengerList(ui, NS_synthetic::SLINT_flightPassenger);
        ticket_render_z(ui, NS_synthetic::ticket_airplane, NS_synthetic::ticket_flight->numberOfTicket_booked, NS_synthetic::ticket_flight->ticket_list);
    });
    ui->global<ticket_global>().on_buttonNext_book_checkIdCard([&] (slint::SharedString IDCARDSLINT) -> bool {
        std::string idcard(IDCARDSLINT);
        bool check = true;
        if (idcard.length() < 13) check = false; 
        return bool(check);
    });
    ui->global<ticket_global>().on_buttonNext_cancel([&] (slint::SharedString ID) {
        string IDCARD(ID);
        NS_synthetic::ticket_erasePassenger(IDCARD);
        ticket_render_z(ui, NS_synthetic::ticket_airplane, NS_synthetic::ticket_flight->numberOfTicket_booked, NS_synthetic::ticket_flight->ticket_list);
        cout << "Phan tu: " << NS_synthetic::ticket_flight->numberOfTicket_booked << endl;
        NS_synthetic::passengerListFlight_takeData_list();
        ticket_render_passengerList(ui, NS_synthetic::SLINT_flightPassenger);
    });
    ui->global<ticket_global>().on_passengerListFlight_getCPP_seat([&] (slint::SharedString IDCARD) -> int {
        string id(IDCARD);
        int ticket_code = 0;
        for (int i = 0; i < NS_synthetic::ticket_flight->numberOfTicket_booked; ++i) {
            if (NS_synthetic::ticket_flight->ticket_list[i].IDCard == id) ticket_code = NS_myLib::String_to_Number(NS_synthetic::ticket_flight->ticket_list[i].TICKET_CODE);
        }
        cout << id << " " << ticket_code << endl;
        return int(ticket_code);
    });
    ui->global<ticket_global>().on_passengerListFlight_sort([&] (int IDSORT){
        int chose_sort(IDSORT);
        NS_synthetic::ticket_sortPassengerList(chose_sort);
        ticket_render_passengerList(ui, NS_synthetic::SLINT_flightPassenger);
    });
    ui->global<ticket_global>().on_passengerListFlight_checkIdCard([&] (slint::SharedString s) ->slint::SharedString {
        std::string idcard(s);
        idcard = NS_myLib::checkInputIDCARD(idcard);
        return slint::SharedString(idcard);
    });
    ui->global<ticket_global>().on_passengerListFlight_search([&] (slint::SharedString searchIdCard) {
        std::string idCard(searchIdCard);
        NS_synthetic::passengerListFlight_search(idCard);
        ticket_render_passengerList(ui, NS_synthetic::SLINT_flightPassenger);
    });
    // -- //


    slint::Timer a;
    a.start(slint::cbindgen_private::TimerMode::Repeated, std::chrono::seconds(1), 
        [=]() {
            auto curr = slint::SharedString(currentTime);
            ui->global<functionAPP>().set_currentTime(curr);
        }
    );
    slint::Timer b;
    b.start(slint::cbindgen_private::TimerMode::Repeated, std::chrono::seconds(5), 
        [=]() {
            RenderListPlane(ui);
            RENDER_flightList(ui);
            statistical_RenderListPlane(ui);
        }
    );
    ui->run();
    cout << "_________________________________________________________________" << endl;
    NS_synthetic::airplaneListDATA.show();
    cout << NS_synthetic::airplaneListDATA.countIndexPlane();
    NS_synthetic::SaveDataAirPlaneOnFile();
    NS_synthetic::saveDataALLPASSENGERTOFILE();
    NS_synthetic::saveDATAListFlight();
    cout << "_________________________________________________________________" << endl;
    NS_synthetic::flightListDATA.pr();
    cout << "_________________________________________________________________" << endl;
    NS_synthetic::passengerListDATA.show();
    NS_synthetic::Release_memory();
    cout << 100 << endl;
    exit(0);
}
// ---------------------
void thread1() {
    while (true) {
        currentTime = NS_myLib::getStringClock(NS_myLib::getCurrClock());
        _sleep(1000);
    }
}
void thread3() {
    while (true) {
        NS_synthetic::updateFlightByTime();
        _sleep(5000);
    }
}
// ------------------------
int main() {
    std::thread t1(thread1); // luong cap nhat thoi gian, theo tung giay
    std::thread t2(thread2); // luong chinh
    std::thread t3(thread3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}