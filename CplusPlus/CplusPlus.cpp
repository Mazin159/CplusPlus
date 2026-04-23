
#pragma warning(disable : 4996)
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
short DayOfWeekOrder(sDate Date)
{
    short a, y, m;
    a = (14 - Date.Month) / 12;
    y = Date.Year - a;
    m = Date.Month + (12 * a) - 2;
    // Gregorian:
    //0:sun, 1:Mon, 2:Tue...etc
    return (Date.Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
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

bool IsLastDayInMonth(sDate date) {
    return (NumberOfDaysInAMonth(date.Month, date.Year) == date.Day);
}
bool IsLastMonthInAYear(sDate date) {
    return date.Month == 12;
}

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
void SwapDate(sDate &Date1, sDate &Date2) {
    sDate TempDate;
    TempDate = Date1;
    Date1 = Date2;
    Date2 = TempDate;

}

short GetDifferenceInDays(sDate date1,sDate date2,bool isLastDayIncluded = false) {
    short Days = 0;
    short SwapFlagValue = 1;

    if (!isDate1BeforDate2(date1, date2)) {
        SwapDate(date1, date2);
        SwapFlagValue = -1;
    }
    
    while (isDate1BeforDate2(date1, date2)) {
        Days++;
        date1 =IncreaseDateByOneDay(date1);
    }

    return SwapFlagValue*( (isLastDayIncluded) ? ++Days:Days);

}
sDate GetSystemDate() {
    sDate Date;

    time_t t = time(0);
    tm* now = localtime(&t);
    Date.Year = now->tm_year + 1900;
    Date.Month = now->tm_mon + 1;
    Date.Day = now->tm_mday;

    return Date;
}
sDate IncreaseDateByXDays(short Days,sDate &Date) {
   
    for (int i = 0;i < Days;i++) {
        Date = IncreaseDateByOneDay(Date);
    }
    return Date;
}
sDate IncreaseDateBy1Week(sDate& Date) {
    Date = IncreaseDateByXDays(7, Date);
    return Date;
}
sDate IncreaseDateByXWeeks(short NumOfWeeks, sDate& Date) {

    for (int i = 0;i < NumOfWeeks;i++) {
        Date = IncreaseDateBy1Week(Date);
    }
    return Date;
}
sDate IncreaseDateByOneMonth(sDate Date) {
    if (Date.Month == 12) {
        Date.Month = 1;
        Date.Year++;
    }
    else
    {
        Date.Month++;
    }
    short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

    if (Date.Day > NumberOfDaysInCurrentMonth) {
        Date.Day = NumberOfDaysInCurrentMonth;
    }
    return Date;

}
sDate IncreaseDateByXMonths(short Months, sDate Date)
{
    for (short i = 1; i <= Months; i++)
    {
        Date = IncreaseDateByOneMonth(Date);
    }
    return Date;
}
sDate IncreaseDateByOneYear(sDate Date)
{
    Date.Year++;
    return Date;
}
sDate IncreaseDateByXYears(short Years, sDate Date)
{
    for (short i = 1; i <= Years; i++)
    {
        Date = IncreaseDateByOneYear(Date);
    }
    return Date;
}
sDate IncreaseDateByXYearsFaster(short Years, sDate Date)
{
    Date.Year += Years;
    return Date;
}
sDate IncreaseDateByOneDecade(sDate Date)
{
    //Period of 10 years
    Date.Year += 10;
    return Date;
}
sDate IncreaseDateByXDecades(short Decade, sDate Date)
{
    for (short i = 1; i <= Decade * 10; i++)
    {
        Date = IncreaseDateByOneYear(Date);
    }
    return Date;
}
sDate IncreaseDateByXDecadesFaster(short Decade, sDate Date)
{
    Date.Year += Decade * 10;
    return Date;
}
sDate IncreaseDateByOneCentury(sDate Date)
{
    //Period of 100 years
    Date.Year += 100;
    return Date;
}
sDate IncreaseDateByOneMillennium(sDate Date)
{
    //Period of 1000 years
    Date.Year += 1000;
    return Date;
}
sDate DecreaseDateByOneDay(sDate &Date) {
   
    if (Date.Day == 1) {

        if (Date.Month == 1) {
            Date.Day = 31;
            Date.Month = 12;
            Date.Year--;
        }
        else {
            Date.Month--;
            Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
        }
    }
    else {
        Date.Day--;
    }
    return Date;
}
sDate DecreaseDateByXDays(short Days, sDate& Date) {
    for (short i = 0;i < Days;i++) {
        Date = DecreaseDateByOneDay(Date);
    }
    return Date;
}
sDate DecreaseDateByOneWeek(sDate& Date) {
    Date = DecreaseDateByXDays(7, Date);
    return Date;
}
sDate DecreaseDateByXWeeks(short Weeks, sDate& Date) {
    for (short i = 0;i < Weeks;i++) {
        Date = DecreaseDateByOneWeek(Date);
    }
    return Date;
}
sDate DecreaseDateByOneMonth(sDate& Date) {
    if (Date.Month > 1) {
        Date.Month--;
    }
    else
    {
        Date.Month = 12;
        Date.Year--;
    }

    if (Date.Day > NumberOfDaysInAMonth(Date.Month, Date.Year)) {
        Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
    }
    return Date;
}
sDate DecreaseDateByXMonths(short Months, sDate& Date) {
    for (short i = 0;i < Months;i++) {
        Date = DecreaseDateByOneMonth(Date);
    }
    return Date;
}

short IsEndOfWeek(sDate Date)
{
    return DayOfWeekOrder(Date) == 6;
}
bool IsWeekEnd(sDate Date)
{
    // Weekends are Fri and Sat
    short DayIndex = DayOfWeekOrder(Date);
    return (DayIndex == 5 || DayIndex == 6);
}
short DaysUntilTheEndOfWeek(sDate Date)
{
    return 6 - DayOfWeekOrder(Date);
}
short DaysUntilTheEndOfMonth(sDate Date1)
{
    sDate EndOfMontDate;
    EndOfMontDate.Day = NumberOfDaysInAMonth(Date1.Month, Date1.Year);
    EndOfMontDate.Month = Date1.Month;
    EndOfMontDate.Year = Date1.Year;

    return GetDifferenceInDays(Date1, EndOfMontDate, true);
}
short DaysUntilTheEndOfYear(sDate Date1)
{
    sDate EndOfYearDate;
    EndOfYearDate.Day = 31;
    EndOfYearDate.Month = 12;
    EndOfYearDate.Year = Date1.Year;

    return GetDifferenceInDays(Date1, EndOfYearDate, true);
}

bool IsBusinessDay(sDate Date)
{
    //Weekends are Sun,Mon,Tue,Wed and Thur
    /* short DayIndex = DayOfWeekOrder(Date);
    return (DayIndex >= 5 && DayIndex <= 4);
    */
    //shorter method is to invert the IsWeekEnd: this will save
    //updating code.
        return !IsWeekEnd(Date);
}


short CalculateVacationDays(sDate DateFrom, sDate DateTo)
{
    short DaysCount = 0;
    while (isDate1BeforDate2(DateFrom, DateTo))
    {
        if (IsBusinessDay(DateFrom))
            DaysCount++;
        DateFrom = IncreaseDateByOneDay(DateFrom);
    }
    return DaysCount;
}

int main()
{
    
    sDate From = ReadFullDate();
    sDate To = ReadFullDate();

    cout << "Vacation Days : " << CalculateVacationDays(From, To);
   
    system("pause>0");
   

    return 0;
    
}

