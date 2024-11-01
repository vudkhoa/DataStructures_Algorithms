#pragma once
#include <string>
#include "MyLib.h"
using namespace std;
using namespace NS_myLib;
namespace NS_Ticket {
    struct ticket {
		string IDCard;
		string TICKET_CODE{};
		ticket() {};
        void prTicket() {
            cout << "CCCD: " << IDCard << " TICKETCODE: " << TICKET_CODE << "; ";
        }
		ticket(string IDCard, string TICKET_CODE) {
			this->IDCard = IDCard;
			this->TICKET_CODE = TICKET_CODE;
		}
        ~ticket() {}
	};

    void ParseDataTicket(int &ticket_list_size, NS_Ticket::ticket *&ticket_list, std::string JSON) {
        std::string strTicket_list_size = "";
        int length = ((int)JSON.length());
        int j = 0;
        for (; j <= length - 1; ++j) {
            if (JSON[j] != '#') {
                strTicket_list_size = strTicket_list_size + JSON[j];
            }
            else break;
        }
        ticket_list_size = NS_myLib::String_to_Number(strTicket_list_size);
        ticket_list = new NS_Ticket::ticket [ticket_list_size + 1];
        for (int i = 1; i <= ticket_list_size; ++i) {
            std::string strTICKET_CODE = "";
            j++;
            for (; j <= length - 1; ++j) {
                if (JSON[j] != '#') {
                    ticket_list[i-1].IDCard = ticket_list[i-1].IDCard + JSON[j];
                }
                else break;
            }
            j++;
            for (; j <= length - 1; ++j) {
                if (JSON[j] != '#') {
                    strTICKET_CODE = strTICKET_CODE + JSON[j];
                }
                else break;
            }
            ticket_list[i-1].TICKET_CODE = NS_myLib::String_to_Number(strTICKET_CODE);
        }
    }
	

	string handleLineCode(int iDong, int numberOfCharDONG) {
		string line_code = Number_to_String(iDong);
		for (int i = 1; i <= numberOfCharDONG - line_code.length(); ++i) {
			line_code = "0" + line_code;
		}
		return line_code;
	}

    void push(ticket* &ticket_list, int &numberOfTicket_booked, std::string IDCARD, string TICKET_CODE) {
        ticket* newTicket_List = new ticket[numberOfTicket_booked + 1];

        for (int i = 0; i < numberOfTicket_booked; ++i) {
            newTicket_List[i].IDCard = ticket_list[i].IDCard;
            newTicket_List[i].TICKET_CODE = ticket_list[i].TICKET_CODE;
        }
        newTicket_List[numberOfTicket_booked].IDCard = IDCARD;
        newTicket_List[numberOfTicket_booked].TICKET_CODE = TICKET_CODE;

        // Giải phóng bộ nhớ của mảng cũ
        delete[] ticket_list;

        // Cập nhật con trỏ và kích thước
        ticket_list = newTicket_List;
        ++numberOfTicket_booked;
    }

    void pull(ticket* &ticket_list, int &numberOfTicket_booked, string IDCARD) {
        ticket* newTicket_List = new ticket[numberOfTicket_booked - 1];
        ticket* tmp;
        int dem = -1; 
        for (int i = 0; i < numberOfTicket_booked; ++i) {
            if (ticket_list[i].IDCard != IDCARD) {
                dem ++;
                newTicket_List[dem].IDCard = ticket_list[i].IDCard;
                newTicket_List[dem].TICKET_CODE = ticket_list[i].TICKET_CODE;
            }
        }

        // Giải phóng bộ nhớ của mảng cũ
        delete[] ticket_list;

        // Cập nhật con trỏ và kích thước
        ticket_list = newTicket_List;
        --numberOfTicket_booked;
    }
}