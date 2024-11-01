#pragma once
#include <string>
#include <ctime>
#include <math.h>
#include "myLib.h"

namespace NS_dateTime {
    const int MONTH[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    struct dateTime {
        std::string day;
        std::string month;
        std::string year;
        std::string hour;
        std::string minute;
        std::string second;
        dateTime() {};
        dateTime(std::string day, std::string month, std::string year, std::string hour, std::string minute, std::string second) {
            this->day = day;
            this->month = month;
            this->year = year;
            this->hour = hour;
            this->minute = minute;
            this->second = second;
        }
        ~dateTime() {};
    };

    // Chuyển đổi thời gian về dạng string
    std::string getStringDateTime(dateTime time) {
        string timeToString = "";
        timeToString = timeToString +
        time.day + "/" + time.month + "/" + time.year + " " + time.hour + ":" + time.minute;
        if (time.second != "") {
            timeToString = timeToString + ":" + time.second;
        }
        return timeToString;
    }
    // Convert -> --/--/---- --:--:--
    void Format(dateTime &time) {
        if ((time.day).length() == 1) {
            time.day = "0" + time.day;
        }
        if ((time.month).length() == 1) {
            time.month = "0" + time.month;
        }
        if ((time.year).length() == 1) {
            time.year = "0" + time.year;
        }

        if ((time.hour).length() == 1) {
            time.hour = "0" + time.hour;
        }
        if ((time.minute).length() == 1) {
            time.minute = "0" + time.minute;
        }
        if ((time.second).length() == 1) {
            time.second = "0" + time.second;
        }
    }
    // "dd/mm/yyyy hh:mm"
    dateTime getTimeFormUnFormat(string str) {
        int leng = ((int) str.length());
        string day = "", month = "", year = "", hour = "", minute = "";
        int i = 0;
        for (; i <= leng - 1; ++i) {
            if (str[i] != '/') {
                day = day + str[i];
            }
            else {
                break;
            }
        }
        ++i;
        for (; i <= leng - 1; ++i) {
            if (str[i] != '/') {
                month = month + str[i];
            }
            else break;
        }
        ++i;
        for (; i <= leng - 1; ++i) {
            if (str[i] != ' ') {
                year = year + str[i];
            }
            else break;
        }
        ++i;
        for (; i <= leng - 1; ++i) {
            if (str[i] != ':') {
                hour = hour + str[i];
            }
            else break;
        }
        ++i;
        for (; i <= leng - 1; ++i) {
            if (str[i] != ':') {
                minute = minute + str[i];
            }
            else break;
        }
        dateTime rs;
        rs.day = day;
        rs.month = month;
        rs.year = year;
        rs.hour = hour;
        rs.minute = minute;
        Format(rs);
        return rs;
    }
    
    dateTime stringToDateTime(string str){
		dateTime time;
		time.day = str[0];
		time.day += str[1];
		time.month = str[3];
		time.month += str[4];
		time.year = str[6];
		for(int i = 7; i <= 9; i++){
		time.year += str[i];
		}
		time.hour = str[11];
		time.hour += str[12];
		time.minute = str[14];
		time.minute += str[15];
		return time;
	}
    
    // Lấy thời gian hiện tại
    dateTime getCurrentTime() {
        
        // struct tm lưu trữ các thông tin về thời gian ở hiện (ngày, tháng, năm, giờ, phút, giây, v.v)
        tm currentTime;

        // time_t lưu trữ thời gian tính bằng giây kể từ 01.01.1970 (Epoch Time)
        time_t now = time(0);

        // Chuyển đổi từ giây sang định dạng thời gian
        localtime_s(&currentTime, &now);

        dateTime time;
        time.day = NS_myLib::Number_to_String(currentTime.tm_mday);
        time.month = NS_myLib::Number_to_String(currentTime.tm_mon + 1);
        time.year = NS_myLib::Number_to_String(currentTime.tm_year + 1900);
        time.hour = NS_myLib::Number_to_String(currentTime.tm_hour);
        time.minute = NS_myLib::Number_to_String(currentTime.tm_min);
        time.second = NS_myLib::Number_to_String(currentTime.tm_sec);

        Format(time);
        return time;
    }

    // Kiểm tra năm nhuận
    bool isLeapYear(int year) {
        if (year % 400 == 0) return true;
        if (year % 4 == 0 && year % 100 != 0) return true;
        return false;
    }

    // Kiểm tra ngày có tồn tại
    bool checkDate(dateTime time) {
        int day = NS_myLib::String_to_Number(time.day);
        int month = NS_myLib::String_to_Number(time.month);
        int year = NS_myLib::String_to_Number(time.year);

        if (year <= 0) return false;
        switch (month) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12: {
                // sai    
                if (day <= 31 && day > 0) { return true;}
                else { return false;}
            }
            // sửa case hai lại cho hay và dễ hiểu
            case 2: {
                if (day <= 28 && day > 0) { return true;}
                else if (day == 29 && isLeapYear(year) == true) { return true;}
                else return false;
            }
            case 4: case 6: case 9: case 11: {
                if (day <= 30 && day > 0) {return true;}
                else {return false;}
            }
            default: {
                return false;
            }
        }
    }
    bool checkDate_Day_Month(dateTime time) {
        int day = NS_myLib::String_to_Number(time.day);
        int month = NS_myLib::String_to_Number(time.month);
        switch (month) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12: {
                // sai    
                if (day <= 31 && day > 0) { return true;}
                else { return false;}
            }
            // sửa case hai lại cho hay và dễ hiểu
            case 2: {
                if (day <= 29 && day > 0) { return true;}
                else return false;
            }
            case 4: case 6: case 9: case 11: {
                if (day <= 30 && day > 0) {return true;}
                else {return false;}
            }
            default: {
                return false;
            }
        }
    }
    // Kiểm tra từng thàn phần của thời gian
    bool checkHour (dateTime time) {
        int hour = NS_myLib::String_to_Number(time.hour);
        if (hour <= 24 && hour >= 0) return true;
        return false;
    }
    bool checkMinute(dateTime time) {
        int minute = NS_myLib::String_to_Number(time.minute);
        if (minute <=59 && minute >= 0) return true;
        return false;
    }
    bool checkSecond(dateTime time) {
        int second = NS_myLib::String_to_Number(time.second);
        if (second <= 59 && second >= 0) return true;
        return false;
    }
    // Kiểm trả cả giờ, phút, giây
    bool checkTime(dateTime time) {
        if (checkHour(time) && checkMinute(time) && checkSecond(time)) return true;
        return false;
    }

    // Tính số ngày kể từ 0/0/0
    int callDate(dateTime time) {
        if (checkDate(time) == true && checkTime(time) == true) {
            Format(time);    
            int year = NS_myLib::String_to_Number(time.year);
            int month = NS_myLib::String_to_Number(time.month);
            int day = NS_myLib::String_to_Number(time.day);

            int dayOfYear = (year - 1) * 365 + (year - 1) / 4;
            int dayOfMonth = 0;

            // Tính số ngày trong tháng trước đó
            for (int i = 1; i <= month - 1; i++) {
                dayOfMonth += MONTH[i];
            }
            if (isLeapYear(year) == true && month > 2) {
                dayOfMonth++;
            }
            return dayOfMonth + dayOfYear + day - 1;
        }
        return -1;
    }

    // Tính số phút giữa 2 thời điểm
    long long calSpaceTime(dateTime before, dateTime after) {
        if (checkDate(before) == true &&
            checkDate(after) == true &&
            checkTime(before) == true &&
            checkTime(after) == true) {
            Format(before);
            Format(after);
            long long hour = NS_myLib::String_to_Number(before.hour);
            long long minute = NS_myLib::String_to_Number(before.minute);

            long long minuteBefore = callDate(before) * 24 * 60 + hour * 60 + minute;

            hour = NS_myLib::String_to_Number(after.hour);
            minute = NS_myLib::String_to_Number(after.minute);

            long long minuteAfter = callDate(after) * 24 * 60 + hour * 60 + minute;

            return minuteAfter - minuteBefore;
        }
        return -1;
    }

    // K.Tra thời gian nhập vào và hiện tại cách nhau bao nhiêu phút.
    long long checkTimeBefore(dateTime time) {
        Format(time);
        dateTime now = getCurrentTime();
        long long rs = calSpaceTime(time, now);
        if (rs >= 0) return rs;
        else return 0 - rs;
    }

    std::string plusThreeHour(std::string day, std::string month, std::string year, std::string hour, std::string minute) { 
        int intHour = NS_myLib::String_to_Number(hour);
        if (intHour >= 21) {
            if (intHour == 21) hour = "00";
            if (intHour == 22) hour = "01";
            if (intHour == 23) hour = "02";
            if ((month == "01" || month == "03" || month == "05" || month == "07" || month == "08" || month == "10" ||  month == "12") && day == "31") {
                if (month == "12") {
                    day = "01";
                    month = "01";
                    year = NS_myLib::Number_to_String(NS_myLib::String_to_Number(year) + 1);
                }    
                else {
                    day = "01";
                    month = NS_myLib::Number_to_String(NS_myLib::String_to_Number(month) + 1);
                }            
            }
            else if ((month == "02" && isLeapYear(NS_myLib::String_to_Number(year)) && day == "29") || (month == "02" && !isLeapYear(NS_myLib::String_to_Number(year)) && day == "28")) {
                day = "01";
                month = "03";
            }
            else if ((month == "04" || month == "06" || month == "09" || month == "11") && day == "30") {
                day = "01";
                month = NS_myLib::Number_to_String(NS_myLib::String_to_Number(month) + 1);
            }
            else {
                day = NS_myLib::Number_to_String(NS_myLib::String_to_Number(day) + 1);
            }
        }
        else {
            intHour = intHour + 3;
            hour = NS_myLib::Number_to_String(intHour);
        }
        std::string plus = "";
        dateTime dt; 
        dt.day = day;
        dt.month = month;
        dt.year = year;
        dt.hour = hour;
        dt.minute = minute;
        Format(dt);
        plus = plus + dt.hour + ":" + dt.minute + " (" + dt.day + "/" + dt.month + "/" + dt.year + ")" ;
        return plus;
        // return hour;
    }
    // true => ở tương lai
    // false => ở quá khứ
    bool beforeAfter(dateTime before, dateTime after) {
        Format(before);
        Format(after);
        dateTime time = after;
        dateTime now = before;
        
        if (checkDate(time) == false || checkTime(time) == false) return false;

        int hourNow = NS_myLib::String_to_Number(now.hour);
		int minuteNow = NS_myLib::String_to_Number(now.minute);
		int dayNow = NS_myLib::String_to_Number(now.day);
		int monthNow = NS_myLib::String_to_Number(now.month);
		int yearNow = NS_myLib::String_to_Number(now.year);

        int hourDt = NS_myLib::String_to_Number(time.hour);
		int minuteDt = NS_myLib::String_to_Number(time.minute);
		int dayDt = NS_myLib::String_to_Number(time.day);
		int monthDt = NS_myLib::String_to_Number(time.month);
		int yearDt = NS_myLib::String_to_Number(time.year);

        // dựa trên số năm
        if (yearDt > yearNow) return true;
        else if (yearDt < yearNow) return false;
        else {
            // Dựa trên số tháng
            if (monthDt > monthNow) return true;
            else if (monthDt < monthNow) return false;
            else {
                // Dựa trên số ngày 
                if (dayDt > dayNow) return true;
                else if (dayDt < dayNow) return false;
                else {
                    // Dựa trên số giờ
                    if (hourDt > hourNow) return true;
                    else if (hourDt < hourNow) return false;
                    else {
                        // Dựa trên số phút
                        if (minuteDt > minuteNow) return true;
                        else if (minuteDt < minuteNow) return false;
                    }
                }
            }
        }
        return false;
    }
    // true => ở tương lai
    // false => ở quá khứ
    bool pastFuture(dateTime time) {
        Format(time);
        if (checkDate(time) == false || checkTime(time) == false) return false;

        dateTime now = getCurrentTime();

        int hourNow = NS_myLib::String_to_Number(now.hour);
		int minuteNow = NS_myLib::String_to_Number(now.minute);
		int dayNow = NS_myLib::String_to_Number(now.day);
		int monthNow = NS_myLib::String_to_Number(now.month);
		int yearNow = NS_myLib::String_to_Number(now.year);

        int hourDt = NS_myLib::String_to_Number(time.hour);
		int minuteDt = NS_myLib::String_to_Number(time.minute);
		int dayDt = NS_myLib::String_to_Number(time.day);
		int monthDt = NS_myLib::String_to_Number(time.month);
		int yearDt = NS_myLib::String_to_Number(time.year);

        // dựa trên số năm
        if (yearDt > yearNow) return true;
        else if (yearDt < yearNow) return false;
        else {
            // Dựa trên số tháng
            if (monthDt > monthNow) return true;
            else if (monthDt < monthNow) return false;
            else {
                // Dựa trên số ngày 
                if (dayDt > dayNow) return true;
                else if (dayDt < dayNow) return false;
                else {
                    // Dựa trên số giờ
                    if (hourDt > hourNow) return true;
                    else if (hourDt < hourNow) return false;
                    else {
                        // Dựa trên số phút
                        if (minuteDt > minuteNow) return true;
                        else if (minuteDt < minuteNow) return false;
                    }
                }
            }
        }
        return false;
    }

    bool centerTimeA_B(dateTime A, dateTime B, dateTime x) {
        // A <= x  && x <= B => true
        // else false
        if (beforeAfter(A, x) == true && beforeAfter(x, B) == true) {
            return true;
        }
        return false;
    }

    bool inThreeHours(dateTime before, dateTime after) {
		long long spaceTime = calSpaceTime(before, after);
		if (spaceTime <= 180) return true;
		return false;
	}

	bool inThirtyMinute(dateTime before, dateTime after) {
		long long spaceTime = calSpaceTime(before, after);
		if (spaceTime <= 30) return true;
		return false;
	}
}