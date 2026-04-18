
#include <iostream>
#include <cmath>

using namespace std;

int ReadNumber() {

    int number;
    cout << "Enter a Number :";
    cin >> number;
    return number;

}

string NumberToText(int Number) {

    if (Number == 0)
    {
        return "";
    }
    if (Number >= 1 && Number <= 19)
    {
        string arr[] = { "",
        "One","Two","Three","Four","Five","Six","Seven",
        "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
        "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
        return arr[Number] + " ";
    }
    if (Number >= 20 && Number <= 99) {
        string arr[] = { "","","Twenty","Thirty","Forty"
            ,"Fifty","Sixty","Seventy","Eighty", "Ninety" };

        return arr[Number / 10] + " " + NumberToText(Number % 10);

    }
    if (Number >= 100 && Number <= 199) {

        return "One Hundred " +  NumberToText(Number % 100);
    }
    if (Number >= 200 && Number <= 999) {

        return NumberToText(Number / 100) + "" + "Hundreds " + NumberToText(Number % 100);
    }


}

bool IsLeapYear(int Year) {

    return (Year % 400 == 0)||(Year % 4 == 0 && Year % 100 != 0);
}
int NumberOfDaysInYear(int Year) {
   return (IsLeapYear(Year)) ? 366 : 365;
}
int NumberOfHours(int Year) {
    return NumberOfDaysInYear(Year) * 24;
}
int NumberOfMinutesInYear(int Year) {
    return NumberOfHours(Year) * 60;
}
int NumberOfSecondsInYear(int Year) {
    return NumberOfMinutesInYear(Year) * 60;
}
//string DayShortName(short DayOfWeekOrder)
struct sDate {
    short Day;
    short Month;
    short Year;
};

short ReadDay()
{
    short Day;
    cout << "\nPlease enter a Day? ";
    cin >> Day;
    return Day;
}
short ReadMonth()
{
    short Month;
    cout << "\nPlease enter a Month? ";
    cin >> Month;
    return Month;
}
short ReadYear()
{
    short Year;
    cout << "\nPlease enter a year? ";
    cin >> Year;
    return Year;
}

short DayOfWeekOrder(short Day, short Month, short Year)
{
    short a, y, m;
    a = (14 - Month) / 12;
    y = Year - a;
    m = Month + (12 * a) - 2;
    // Gregorian:
    //0:sun, 1:Mon, 2:Tue...etc
    return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m)/ 12)) % 7;
}

string DayShortName(short DayOfWeekOrder)
{
    string arrDayNames[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

    return arrDayNames[DayOfWeekOrder];
}
short NumberOfDaysInAMonth(short Month, short Year)
{
    if (Month < 1 || Month>12)
        return 0;
    int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) :
        days[Month - 1];
}

string MonthShortName(short MonthNumber){

    string Months[12] = { "Jan", "Feb", "Mar",
    "Apr", "May", "Jun",
    "Jul", "Aug", "Sep",
    "Oct", "Nov", "Dec"
    };
    return (Months[MonthNumber - 1]);
}

void PrintCalendar(short month, short year) {

    int current = DayOfWeekOrder(1, month, year);
    int NumberOfDays = NumberOfDaysInAMonth(month, year);

    // Print the current month name
    printf("\n _______________%s_______________\n\n",
        MonthShortName(month).c_str());
    // Print the columns
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
    // Print appropriate spaces
    
    for (int i = 0;i < current;i++) {
        cout << "     ";
    }
    for (int j = 1; j <= NumberOfDays;j++) {

        printf("%5d", j);
        if (++current == 7) {
            cout << endl;
            current = 0;
        }
    }
    
    printf("\n _________________________________\n");
}
void YearCalendar(short year) {
    printf("\n _________________________________\n");
    printf("\n           Calendar %d          \n",year);
    printf("\n ---------------------------------\n");
    for (int i = 1;i <= 12;i++) {
        PrintCalendar(i, year);
    }

}

int NumberOfDaysFromTheBeginingOfTheYear(short day, short month, short year) {
    int NumberOfDays = day;

    for (int i = 1; i < month; i++) {
        NumberOfDays += NumberOfDaysInAMonth(i, year);
    }
    return NumberOfDays;

}
sDate GetDateFromDaysOrder(short DaysOrder, short year) {

    sDate Date;
    Date.Month = 1;
    int MonthDays ;

    while (true) {

        MonthDays = NumberOfDaysInAMonth(Date.Month, year);

        if (DaysOrder > MonthDays) {

            DaysOrder -= MonthDays;
            Date.Month++;
        }
        else {
            Date.Day = DaysOrder;
            Date.Year = year;
            return Date;

        }
    }

}
sDate ReadFullDate() {
    sDate Date;
     Date.Day = ReadDay();
     Date.Month = ReadMonth();
     Date.Year = ReadYear();
    return Date;
}
short ReadDaysToAdd()
{
    short Days;
    cout << "\nHow many days to add? ";
    cin >> Days;
    return Days;
}
sDate DateAddDays(short AddDays, sDate Date) {

    short RemainingDays = AddDays + NumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date.Year);
     Date.Month = 1;
     int DaysOfMonth=0;
     
     while (true) {
         DaysOfMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

         if (RemainingDays > DaysOfMonth) {
             RemainingDays -= DaysOfMonth;
             Date.Month++;

             if (Date.Month > 12) {
                 Date.Month = 1;
                 Date.Year++;
             }

         }
         else {
             Date.Day = RemainingDays;
             return Date;
         }

     }



}


bool isDate1BeforDate2(sDate Date1, sDate Date2) {

    return (Date1.Year < Date2.Year) ||
        (Date1.Year == Date2.Year && Date1.Month < Date2.Month) ||
        (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);
}
//bool IsDate1EqualDate2(sDate Date1, sDate Date2) {
//
//}
bool IsLastDayInMonth(sDate date) {
    return (NumberOfDaysInAMonth(date.Month, date.Year) == date.Day);
}
bool IsLastMonthInAYear(sDate date) {
    return date.Month == 12;
}
//sDate IncreaseDateByOneDay1(sDate Date) {
//    short DaysInMonth = NumberOfDaysInAMonth(Date.Month,Date.Year);
//    if (Date.Day < DaysInMonth) {
//        Date.Day++;
//        return Date;
//    }
//    if (Date.Month < 12) {
//        Date.Month++;
//        Date.Day = 1;
//        return Date;
//    }
//    Date.Day = 1;
//    Date.Month = 1;
//    Date.Year++;
//    return Date;
//    
//}

sDate IncreaseDateByOneDay(sDate Date) {

    if (IsLastDayInMonth(Date)) {

        if (IsLastMonthInAYear(Date)) {
            Date.Day = 1;
            Date.Month = 1;
            Date.Year++;

        }
        else {
            Date.Month++;
            Date.Day = 1;
        }

    }
    else {
        Date.Day++;
    }
    return Date;
}
short GetDifferanceBetween2Dates(sDate date1,sDate date2,bool isLastDayIncluded = false) {
    short Days;

    while (isDate1BeforDate2(date1, date2)) {
        Days++;
        IncreaseDateByOneDay(date1);
    }
    return (isLastDayIncluded) ? Days++:Days;

}


int main()
{
    
    
    sDate Date1 = ReadFullDate();
    Date1 = IncreaseDateByOneDay(Date1);
    cout << "\nDate after adding one day is:"
        << Date1.Day << "/" << Date1.Month << "/" << Date1.Year;
    return 0;
    
}

