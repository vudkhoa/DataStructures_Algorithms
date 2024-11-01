#pragma once
#include <iostream>
#include <string>
using namespace std;
// Noi day chua cac ham doc lap voi cac thu vien
namespace NS_myLib {
    // tu so sang chuoi
    std::string Number_to_String(int number) {
        if (number == 0) return "0";
        string result = "";
        int n;
        while (number != 0) {
            n = number % 10;
            result = ((char)(n + 48)) + result;
            number = (number - n) / 10;
        }
        return result;
    }
    // tu chuoi sang so
    int String_to_Number(string str) {
        int result = 0; int index = 1;
        for (int i = ((int)str.length()) - 1; i >= 0; --i) {
            if (str[i] < '0' || str[i] > '9') {
                return -1;
            }
            result += ((int)str[i] - 48) * index;
            index = index * 10;
        }
        return result;
    }
    // Tu chuoi sang slint::SharedString
    slint::SharedString to_shared_string(const string& stdString){
        return slint::SharedString(stdString);
    }
    // xoa 1 ki tu, bat dau tu start, do dai la length
    string eraseString(string str, int s, int length) {
        if (s < 0 || length < 0) return "ERROR";
        string result = "";
        if (s + length > ((int)str.length())) return "ERROR";
        else {
            for (int i = 0; i <= s - 1; ++i) {
                result = result + str[i];
            }
            for (int i = s + length; i <= ((int)str.length()) - 1; ++i) {
                result = result + str[i];
            }
        }
        return result;
    }
    // bo khoang trang o dau string
    string TrimFirst(string str) {
        while (str.length() > 0 && str[0] == ' ') {
            str = eraseString(str, 0, 1);
        }
        return str;
    }
    // bo khoang trang o cuoi chuoi
    string TrimLast(string str) {
        while (((int)str.length()) > 0 && str[((int)str.length() - 1)] == ' ') {
            str = eraseString(str, ((int)str.length()) - 1, 1);
        }
        return str;
    }
    // xoa 2 khoang trang lien tiep ben trong chuoi
    string delSpace(string str) {
        string result = "";
        str = str + "r";
        for (int i = 0; i <= ((int)str.length()) - 2; ++i) {
            if (str[i] == ' ' && str[i + 1] == ' ') {
                continue;
            }
            else {
                result = result + str[i];
            }
        }
        return result;
    }

    string delAllSpace(string str) {
        string result = "";
        for (int i = 0; i <= ((int)str.length()) - 1; ++i) {
            if (str[i] != ' ') {
                result = result + str[i];
            }
        }
        return result;
    }

    // Kiem tra xem, 1 ki tu co la 1 chu cai, hay 1 so hay khong
    bool checkChar(char a) {
        if (
            ((a <= '9') && (a >= '0')) ||
            ((a <= 'z') && (a >= 'a')) ||
            ((a <= 'Z') && (a >= 'A')) ||
            (a == ' ')
            ) {
            return true;
        }
        return false;
    }
    void toUppercase(char& c) {
        if (c <= 'z' && c >= 'a') c = ((int)c) - 32;
    }
    void toLowerCase(char& c) {
        if (c <= 'Z' && c >= 'A') c = ((int)c) + 32;
    }

    // Phân giải 1 chuỗi thành dữ liệu
    void parseJSON_Plane(std::string& idPlane, std::string& typePlane, int& rowNumber, int& colNumber, int& flytimes, bool& isAvai,std::string JSON) {
        std::string strRowNumber = "";
        std::string strColNumber = "";
        std::string strFlyTimes = "";
        int length = ((int)JSON.length());
        int i = 0;
        for (; i <= length - 1; i++) {
            if (JSON[i] != '#') {
                idPlane = idPlane + JSON[i];
            }
            else break;
        }
        i++;
        for (; i <= length - 1; i++) {
            if (JSON[i] != '#') {
                typePlane = typePlane + JSON[i];
            }
            else break;
        }
        i++;
        for (; i <= length - 1; i++) {
            if (JSON[i] != '#') {
                strRowNumber = strRowNumber + JSON[i];
            }
            else break;
        }
        i++;
        for (; i <= length - 1; i++) {
            if (JSON[i] != '#') {
                strColNumber = strColNumber + JSON[i];
            }
            else break;
        }
        ++i;
        for (; i <= length - 1; ++i) {
            if (JSON[i] != '#') {
                strFlyTimes = strFlyTimes + JSON[i];
            }
            else break;
        }
        ++i;
        if (JSON[length - 1] == '0') {
            isAvai = false;
        }
        else isAvai = true;
        flytimes =  String_to_Number(strFlyTimes);
        rowNumber = String_to_Number(strRowNumber);
        colNumber = String_to_Number(strColNumber);
    }
    
    std::string stringtifyJSON_Plane(std::string idPlane, std::string typePlane, int rowNumber, int colNumber, int flyTimes, bool isAvai) {
        std::string strRowNumber = Number_to_String(rowNumber);
        std::string strColNumber = Number_to_String(colNumber);
        std::string strFlyTimes = Number_to_String(flyTimes);
        std::string strIsVai = "";
        if (isAvai == true) strIsVai =  "1";
        else strIsVai = "0";
        return idPlane + "#" + typePlane + "#" + strRowNumber + "#" + strColNumber + "#" + strFlyTimes + "#" + strIsVai;
    }
    // Kruth Morris Pratt
    bool ExistenceCheck(string a, string b) {
        int p[30] = {0};
        a = " " + a;
        b = " " + b;
        int k = 0;
        p[1] = 0;
    
        for(int i = 2; i < a.size(); i++){
            while(k > 0 && a[k+1] != a[i]) k = p[k];
            if(a[k+1] == a[i]) k++;
            p[i] = k;
        }
        
        k = 0;
        for(int i = 1; i<b.size(); i++){
            while(k>0 && a[k+1]!=b[i]) k = p[k];
            if(a[k+1]==b[i]) k++;

            if(k == (a.size()-1)){
                return true;
            }
        }
        return false;
    }
    
    struct clockDateTime {
        string day;
        string month;
        string year;
        string hour;
        string minute;
        string second;
        clockDateTime() {}
        clockDateTime(string day, string month, string year, string hour, string minute, string second) {
            this->day = day;
            this->month = month;
            this->year = year;
            this->hour = hour;
            this->minute = minute;
            this->second = second;
        }
        ~clockDateTime() {}
    };
    void mySTDFormat(clockDateTime& date_time) {
        if ((date_time.day).length() == 1) {
            date_time.day = "0" + date_time.day;
        }
        if ((date_time.month).length() == 1) {
            date_time.month = "0" + date_time.month;
        }
        if ((date_time.hour).length() == 1) {
            date_time.hour = "0" + date_time.hour;
        }
        if ((date_time.minute).length() == 1) {
            date_time.minute = "0" + date_time.minute;
        }
        if ((date_time.second).length() == 1) {
            date_time.second = "0" + date_time.second;
        }
    }
    clockDateTime getCurrClock() {
        // struct tm chua cac dinh dang thoi gian
        tm currentTime;

        // time_t tra lai thoi gian tihnh bang giay ke tu Epoch (01/01/1970)
        time_t now = time(0);

        // chuyen doi tu s sang doi tuong currentTime;
        localtime_s(&currentTime, &now);

        clockDateTime date_time;
        date_time.day = NS_myLib::Number_to_String(currentTime.tm_mday);
        date_time.month = NS_myLib::Number_to_String(currentTime.tm_mon + 1);
        date_time.year = NS_myLib::Number_to_String(currentTime.tm_year + 1900);
        date_time.hour = NS_myLib::Number_to_String(currentTime.tm_hour);
        date_time.minute = NS_myLib::Number_to_String(currentTime.tm_min);
        date_time.second = NS_myLib::Number_to_String(currentTime.tm_sec);
        mySTDFormat(date_time);

        return date_time;
    }
    std::string getStringClock(clockDateTime date_time) {
        string time_to_string = "";
        time_to_string = time_to_string + date_time.day + "/"
            + date_time.month + "/"
            + date_time.year + " "
            + date_time.hour + ":"
            + date_time.minute + ":"
            + date_time.second;
        return time_to_string;
    }

    string checkInputFlightCode(string str) {
        if (str == "") return "";
        if (str.length() > 8) return "Flight codes cannot contain \nmore than 8 characters";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] == ' ') return "Flight codes do not contain spaces";
            if (NS_myLib::checkChar(str[i]) == false) {
                return "Flight codes only contain \ncharacters from A to Z and from 0 to 9";
            }
        }
        if (str.length() >= 1) {
            if ( (str[0] <= '9' && str[0] >= '0'))  {
                return "The first character must be a letter";
            }
        }
        return "";
    }
    string standardInputFlightCode(string str, string lastValue) {
        if (checkInputFlightCode(str) != "") return lastValue;
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                toUppercase(str[i]);
            }
        }
        return str;
    }

    string checkInputFlightCodeSearch(string str) {
        if (str == "") return "";
        if (str.length() > 8) return "Flight codes cannot contain \nmore than 8 characters";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] == ' ') return "Flight codes do not contain spaces";
            if (NS_myLib::checkChar(str[i]) == false) {
                return "Flight codes only contain \ncharacters from A to Z and from 0 to 9";
            }
        }
        return "";
    }
    string standardInputFlightCodeSearch(string str, string lastValue) {
        if (checkInputFlightCodeSearch(str) != "") return lastValue;
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                toUppercase(str[i]);
            }
        }
        return str;
    }
    
    string checkInputDay(string str) {
        if (str == "") return "";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] < '0' || str[i] > '9') return "The date input field \nonly accepts characters from 0 to 9";
        }
        int day = NS_myLib::String_to_Number(str);
        if (day <= 0 || day > 31) return "Day " + NS_myLib::Number_to_String(day) + " doesn't exist";
        return "";
    }
    string standardInputDay(string str, string lastValue) {
        if (checkInputDay(str) != "") return lastValue;
        return str;
    }
    
    string checkInputMonth(string str) {
        if (str == "") return "";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] == ' ') return "The month input field does not contain spaces";
            if (str[i] < '0' || str[i] > '9') return "The month input field \nonly accepts characters from 0 to 9";
        }
        int month = NS_myLib::String_to_Number(str);
        if (month <= 0 || month > 12) return "Month "+ NS_myLib::Number_to_String(month) + " doesn't exist";
        return "";
    }
    string standardInputMonth(string str, string lastValue) {
        if (checkInputMonth(str) != "") return lastValue;
        return str;
    }

    string checkInputYear(string str) {
        if (str == "") return "";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] < '0' || str[i] > '9' || str[i] == ' ') return "The year input field \nonly accepts characters from 0 to 9";
        }
        int year = NS_myLib::String_to_Number(str);
        if (year <= 0) return "Year doesn't exits year";
        if (year > 2100) return "This year is too far away";
        return "";
    }
    string standardInputYear(string str, string lastValue) {
        if (checkInputYear(str) != "") return lastValue;
        return str;
    }

    string checkInputDes(string str) {
        if (str == "") return "";
        if (str[0] == ' ') return "Place names do not begin with a space";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (checkChar(str[i]) == false) return "The destination input field only accepts characters \nfrom 0 to 9, from a to z, from A to Z";
        }
        return "";
    }
    string standardInputDes(string str, string lastValue) {
        if (checkInputDes(str) != "") {
            lastValue = TrimLast(lastValue);
            lastValue = TrimFirst(lastValue);
            return lastValue;
        }
        str = delSpace(str);
        toUppercase(str[0]);
        for (int i = 0; i <= ((int) str.length()) - 2; ++i) {
            if (str[i] == ' ') toUppercase(str[i + 1]);
        }
        return str;
    }

    string checkInputIDPlaneSearch(string str) {
        if (str == "") return "";
        if (str.length() > 8) return "ID Plane cannot contain \nmore than 8 characters";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] == ' ') return "ID Planes do not contain spaces";
            if (NS_myLib::checkChar(str[i]) == false) {
                return "ID Plane only contain \ncharacters from A to Z and from 0 to 9";
            }
        }
        return "";
    }
    string standardInputIDPlaneSearch(string str, string lastValue) {
        if (checkInputIDPlaneSearch(str) != "") return lastValue;
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                toUppercase(str[i]);
            }
        }
        return str;
    }

    string checkInputIDPlane(string str) {
        if (str == "") return "";
        if (str.length() > 8) return "ID Plane cannot contain \nmore than 8 characters";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] == ' ') return "ID Planes do not contain spaces";
            if (NS_myLib::checkChar(str[i]) == false) {
                return "ID Plane only contain \ncharacters from A to Z and from 0 to 9";
            }
        }
        if (str.length() >= 1) {
            if ( (str[0] <= '9' && str[0] >= '0'))  {
                return "The first character must be a letter";
            }
        }
        return "";
    }
    string standardInputIDPlane(string str, string lastValue) {
        if (checkInputIDPlane(str) != "") return lastValue;
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                toUppercase(str[i]);
            }
        }
        return str;
    }

    string checkInputNumber(string str) {
        if (str == "") return "";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] < '0' || str[i] > '9') return "The number input field \nonly accepts characters from 0 to 9";
        }
        return "";
    }
    string standardInputNumber(string str, string lastValue) {
        if (checkInputNumber(str) != "") return lastValue;
        return str;
    }

    string checkInputNumberIDCard(string str) {
        if (str == "") return "";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] < '0' || str[i] > '9') return "The number input field \nonly accepts characters from 0 to 9";
        }
        if (str.length() > 13) return "Limit 13 numbers";
        return "";
    }
    string standardInputNumberIDCard(string str, string lastValue) {
        if (checkInputNumberIDCard(str) != "") return lastValue;
        return str;
    }

    string checkInputFirstName(string str) {
        if (str == "") return "";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (checkChar(str[i]) == false) return "The First Name input field only accepts \ncharacters from a to z, from A to Z";
            if (str[i] <= '9' && str[i] >= '0') return "The First Name input field only accepts \ncharacters from a to z, from A to Z";
        }
        return "";
    }
    string standardInputFirstName( string str, string lastValue) {
        if (checkInputFirstName(str) != "") {
            lastValue = TrimLast(lastValue);
            lastValue = TrimFirst(lastValue);
            return lastValue;
        }
        str = delSpace(str);
        toUppercase(str[0]);
        for (int i = 0; i <= ((int) str.length()) - 2; ++i) {
            if (str[i] == ' ') toUppercase(str[i + 1]);
        }
        return str;
    }
    
    string checkInputLastName(string str) {
        if (str == "") return "";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (checkChar(str[i]) == false) return "The Last Name input field only accepts \ncharacters from a to z, from A to Z";
            if (str[i] <= '9' && str[i] >= '0') return "The Last Name input field only accepts \ncharacters from a to z, from A to Z";
            if (str[i] == ' ') return "The name consists of only 1 word at most";
        }
        return "";
    }
    string standardInputLastName( string str, string lastValue) {
        if (checkInputLastName(str) != "") {
            lastValue = TrimLast(lastValue);
            lastValue = TrimFirst(lastValue);
            return lastValue;
        }
        str = delSpace(str);
        toUppercase(str[0]);
        return str;
    }
    
    string checkInputHour(string str) {
        if (str == "") return "";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] < '0' || str[i] > '9') return "The hour input field \nonly accepts characters from 0 to 9";
        }
        int hour = NS_myLib::String_to_Number(str);
        if (hour < 0 || hour > 23) return str + " - Hour doesn't exits";
        return "";
    }
    string standardInputHour(string str, string lastValue) {
        if (checkInputHour(str) != "") return lastValue;
        else return str;
    }
    
    string checkInputMinute(string str) {
        if (str == "") return "";
        for (int i = 0; i <= ((int) str.length()) - 1; ++i) {
            if (str[i] < '0' || str[i] > '9') return "The Minute input field \nonly accepts characters from 0 to 9";
        }
        int minute = NS_myLib::String_to_Number(str);
        if (minute < 0 || minute > 59) return str + " - Minute doesn't exits";
        return "";
    }
    string standardInputMinute(string str, string lastValue) {
        if (checkInputMinute(str) != "") return lastValue;
        else return str;
    }
    
    // ===========================================================================================================
    
    bool check_character_number(char number) {
        return (number >= '0' && number <= '9');
    }

    // check chữ cái in hoa
    bool check_character_uppercaseLetter (char uppercaseLetter) {
        return (uppercaseLetter >= 'A' && uppercaseLetter <= 'Z'); 
    }

    //check chữ cái in thường
    bool check_character_lowercaseLetter (char lowercaseLetter) {
        return (lowercaseLetter >= 'a' && lowercaseLetter <= 'z'); 
    }

    //check ký tự đặc biệt
    bool check_character(char a) {
        if (!check_character_number(a) && !check_character_lowercaseLetter(a) && !check_character_uppercaseLetter(a)) return false;
        return true;
    }

    std::string check_planeCode (std::string planeCode) {
        // Không vượt quá 8 ký tự
        if (planeCode.length() > 8) return "The aircraft code must not exceed 8 characters";
        // kiểm tra chữ đầu
        if (planeCode.length() != 0)
            if (!check_character_lowercaseLetter(planeCode[0]) && !check_character_uppercaseLetter(planeCode[0])) return "The first character must not be a number";
        // kiểm tra ký tự đặc biệt
        for (int i = 0; i < planeCode.length(); i++) {
            if (!check_character(planeCode[i])) return "The aircraft code must not contain special characters";
        }
        return "True";
    }
    // -- //
    string checkInputIDCARD(string str) {
        if (str == "") return "";
        if (str.length() > 13) return "Citizen identification numbers are\n    consistently thirteen digits";
        for (int i = 0; i < str.length(); ++i) {
            if (str[i] > '9' || str[i] < '0') return "Personal identification numbers are\n    exclusively composed of digits";
        }
        return "";
    }
    string ticket_checkInputFirstName(string str) {
        if (str == "") return "";
        if (str.length() != 0) {
            if (str[0] == ' ') {
                return "The first character cannot be a space";
            }
        }
        for (int i = 0; i < str.length(); ++i) {
            if ((str[i] < 'A' || str[i] > 'Z') && str[i] != ' ') return "The lastname consists only of the characters:\n                     a to z, A to Z, and spaces";
        }
        return "";
    }
    string ticket_checkInputLastName(string str) {
        if (str == "") return "";
        if (str.length() != 0) {
            if (str[0] == ' ') {
                return "The lastname consists only of the characters:\n                            a to z, A to Z";
            }
        }
        for (int i = 0; i < str.length(); ++i) {
            if ((str[i] < 'A' || str[i] > 'Z')) return "The lastname consists only of the characters:\n                            a to z, A to Z";
        }
        return "";
    }
    // -- //
}