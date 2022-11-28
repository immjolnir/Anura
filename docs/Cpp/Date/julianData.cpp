/**
 * 日期计算（上）：Julian Day 算法把日期转为连续整数
 * https://www.youtube.com/watch?v=0KYHRasgWaY
 * 
 * https://github.com/quickfix/quickfix/blob/d73d1e86a2099d1dd6eaa3ed8b7d78ed73888877/src/C%2B%2B/FieldTypes.h#L517
*/
#include <stdio.h>

/// Helper method to calculate a Julian day number.
/**
 * Given a day(year, month, day), Julian Day Number is sum of
 *  
 * * Days before the year： `y*365 + y/4 - y/100 + y/400`
 * * Days before the month: `(153 * m + 2) / 5`
 * * * March is the month 0 in shifted year
 * * * February is the last month(no. 11) of shifted year. 这样leap year也不会影响之前的月份天数
 * * * Leap day(if any) will be the last day of previous year
 * * * Length of first 11 months(m=0..10) are fixed now
 * * * * 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31
 * * Days in the month： `day`
 * * An offset to make day 0 is Nov 24, 4714 BC
 * After shifting, much easier to calculate
*/
static int julianDate(int year, int month, int day)
{
  int a = (14 - month) / 12;  // a = (month < 3) ? 1: 0
  int y = year + 4800 - a;    // when month >=3, y=year + 4800; else y= year + 4799
  int m = month + 12 * a - 3; // when month >=3, m=month -3; else m= month +9
  return (day + int((153 * m + 2) / 5) + y * 365 +
          int(y / 4) - int(y / 100) + int(y / 400) - 32045);
}

/// Convert a Julian day number to a year, month and day
/*
 * Moving leap day to the end of year, simplified a lot: "residual"
 * Integer arithmetic can be tricky and userful.
 * */
static void getYMD(int jday, int &year, int &month, int &day)
{
  int a = jday + 32044; // 0-th day is Mar 1, epoch year
  int b = (4 * a + 3) / 146097; // century(phase of outer cycle)
  int c = a - int((b * 146097) / 4); // days in the century
  int d = (4 * c + 3) / 1461; // year in the century(inner phase)
  int e = c - int((1461 * d) / 4); // days in the year
  int m = (5 * e + 2) / 153; // shifted month in the year

  day = e - int((153 * m + 2) / 5) + 1; // day of the month
  month = m + 3 - 12 * int(m / 10); // normal month
  year = b * 100 + d - 4800 + int(m / 10); // normal year
}

void testDate(int y, int m, int d)
{
  int days = julianDate(y, m, d);
  int year, month, day;
  getYMD(days, year, month, day);
  printf("Given %d-%d-%d => julianDate=%d, year=%d, month=%d, day=%d\n", y, m, d, days, year, month, day);
}

int main()
{
  // Calc JUlian day number
  // 2007
  testDate(2007, 2, 1);
  testDate(2007, 2, 28);
  testDate(2007, 2, 29); // Leap Year
  testDate(2007, 3, 1);

  // 2008
  testDate(2008, 2, 1);
  testDate(2008, 2, 29);
  testDate(2008, 3, 1);
  return 0;
}































