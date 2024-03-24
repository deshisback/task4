#include <iostream>
#include <string>

using namespace std;

class Date
{
private:

	short int dayInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	short int year;
	short int month;
	short int day;
	short int hour;
	short int minute;
	short int second;
	bool isOurEra;

	//не имеет значение поля isOurEra в этом методе, так как они лишь приводит
	//поля к нормальным значениям. За этим показателем нужно следить лишь при
	//сложении и разности
	void SetNormalTime1()
	{
		int n = 0;

		if (this->isOurEra == true) {

			if (this->second < 0)
			{
				n = abs(this->second / 60) + 1;
				this->minute -= n;
				this->second += n * 60;
			}

			else
			{
				n = this->second / 60;
				this->second -= n * 60;
				this->minute += n;
			}

			if (this->minute < 0)
			{
				n = abs(this->minute / 60) + 1;
				this->hour -= n;
				this->minute += n * 60;
			}

			else
			{
				n = this->minute / 60;
				this->minute -= n * 60;
				this->hour += n;
			}

			if (this->hour < 0)
			{
				n = abs(this->hour / 24) + 1;
				this->day -= n;
				this->hour += n * 24;
			}

			else
			{
				n = this->hour / 24;
				this->hour -= n * 24;
				this->day += n;
			}

			while (this->day <= 0)
			{
				if (isVis(this->year))
				{
					this->dayInMonth[1] += 1;
				}
				if (month == 1)
				{
					this->day += this->dayInMonth[11];
					this->month = 12;
					this->year--;
				}
				else if (this->month == 0)
				{
					this->day += this->dayInMonth[10];
					this->month = 11;
					this->year--;
				}
				else
				{
					this->day += this->dayInMonth[month - 2];
					this->month--;
				}
				this->dayInMonth[1] -= 1;
			}

			while (this->day > this->dayInMonth[month - 1])
			{
				if (isVis(year))
				{
					this->dayInMonth[1] += 1;
				}
				this->day -= this->dayInMonth[month - 1];
				this->month++;
				if (this->month == 12)
				{
					this->month = 1;
					this->year++;
				}
				this->dayInMonth[1] -= 1;
			}
		}
	}

	void SetNormalTime2()
	{
		while (this->month > 13)
		{
			this->month -= 13;
			this->year += 1;
		}
		if (this->year >= 0) this->isOurEra = true;
		else this->isOurEra = false;
	}

	bool isVis(int year)
	{
		if (year % 4 == 0) return true;
		else return false;
	}
public:

	Date()
	{
		year = 1960;
		month = 1;
		day = 1;
		hour = 0;
		minute = 0;
		second = 0;
		isOurEra = true;
	}

	Date(short int _year, short int _month, short int _day, short int _hour,
		short int _minute, short int _second, bool _isOurEra)
	{
		year = _year;
		month = _month;
		day = _day;
		hour = _hour;
		minute = _minute;
		second = _second;
		isOurEra = _isOurEra;
	}

	Date add(short int _year, short int _month, short int _day,
		short int _hour, short int _minute, short int _second)
	{
		day += _day;
		hour += _hour;
		minute += _minute;
		second += _second;

		SetNormalTime1();

		year += _year;
		month += _month;

		SetNormalTime2();

		Date NewDate(year, month, day, hour, minute, second, isOurEra);
		return NewDate;
	}
	Date subtract(short int _year, short int _month, short int _day,
		short int _hour, short int _minute, short int _second)
	{
		day -= _day;
		hour -= _hour;
		minute -= _minute;
		second -= _second;

		SetNormalTime1();

		year -= _year;
		month -= _month;

		SetNormalTime2();

		Date NewDate(year, month, day, hour, minute, second, isOurEra);
		return NewDate;
	}

	friend ostream& operator<<(ostream& os, const Date& data)
	{
		os << "Date: [" << data.year << " year, " << data.month << " month, " << data.day << " day, ";
		os << data.hour << " hours, " << data.minute << " minutes, " << data.second << " sec., ";
		if (data.isOurEra) os << "Our Era]";
		else os << "Previous Era";
		return os;
	}

	Date& operator = (const Date& d2)
	{
		this->year = d2.year;
		this->month = d2.month;
		this->day = d2.day;
		this->hour = d2.hour;
		this->minute = d2.minute;
		this->second = d2.second;
		this->isOurEra = d2.isOurEra;
		return *this;
	}

	bool operator < (const Date& d2)
	{
		if ((isOurEra == false) and (d2.isOurEra == true))
		{
			return true;
		}

		else if ((isOurEra == true) and (d2.isOurEra == false))
		{
			return false;
		}

		else if (isOurEra)
		{
			if (year < d2.year) return true;
			else if (year > d2.year) return false;
			if (month < d2.month) return true;
			else if (month > d2.month) return false;
			if (day < d2.day) return true;
			else if (day > d2.day) return false;
			if (hour < d2.hour) return true;
			else if (hour > d2.hour) return false;
			if (minute < d2.minute) return true;
			else if (minute > d2.minute) return false;
			if (second < d2.second) return true;
			else return false;
		}

		else
		{
			if (year < d2.year) return false;
			else if (year > d2.year) return true;
			if (month < d2.month) return false;
			else if (month > d2.month) return true;
			if (day < d2.day) return false;
			else if (day > d2.day) return true;
			if (hour < d2.hour) return false;
			else if (hour > d2.hour) return true;
			if (minute < d2.minute) return false;
			else if (minute > d2.minute) return true;
			if (second < d2.second) return false;
			else return true;
		}
	}

	bool operator > (const Date& d2)
	{
		return !(*this < d2);
	}

	bool operator == (const Date& d2)
	{
		if (this->isOurEra == d2.isOurEra && this->year == d2.year &&
			this->month == d2.month && this->day == d2.day &&
			this->hour == d2.hour && this->minute == d2.minute &&
			this->second == d2.second)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Date operator + (const Date& d2)
	{
		Date newDate;

		if (this->isOurEra == d2.isOurEra)
		{
			newDate.second = this->second + d2.second;
			newDate.minute = this->minute + d2.minute;
			newDate.hour = this->hour + d2.hour;
			newDate.day = this->day + d2.day;
			newDate.SetNormalTime1();
			newDate.month = this->month + d2.month;
			newDate.year = this->year + d2.year;
			newDate.SetNormalTime2();
		}

		else if (this->isOurEra == true && d2.isOurEra == false)
		{
			newDate.second = this->second - d2.second;
			newDate.minute = this->minute - d2.minute;
			newDate.hour = this->hour - d2.hour;
			newDate.day = this->day - d2.day;
			newDate.SetNormalTime1();
			newDate.month = this->month - d2.month;
			newDate.year = this->year - d2.year;
			newDate.SetNormalTime2();
		}

		else
		{
			newDate.second = d2.second - this->second;
			newDate.minute = d2.minute - this->minute;
			newDate.hour = d2.hour - this->hour;
			newDate.day = d2.day - this->day;
			newDate.SetNormalTime1();
			newDate.month = d2.month - this->month;
			newDate.year = d2.year - this->year;
			newDate.SetNormalTime2();
		}
		return newDate;
	}

	void operator += (const Date& d2)
	{
		*this = *this + d2;
	}

	Date operator - (const Date& d2)
	{
		Date newDate;

		if (isOurEra == d2.isOurEra)
		{
			newDate.second = this->second - d2.second;
			newDate.minute = this->minute - d2.minute;
			newDate.hour = this->hour - d2.hour;
			newDate.day = this->day - d2.day;
			newDate.SetNormalTime1();
			newDate.month = this->month - d2.month;
			newDate.year = this->year - d2.year;
			newDate.SetNormalTime2();
		}

		else if (isOurEra == true && d2.isOurEra == false)
		{
			newDate.second = this->second + d2.second;
			newDate.minute = this->minute + d2.minute;
			newDate.hour = this->hour + d2.hour;
			newDate.day = this->day + d2.day;
			newDate.SetNormalTime1();
			newDate.month = this->month + d2.month;
			newDate.year = this->year + d2.year;
			newDate.SetNormalTime2();
		}

		else
		{
			newDate.isOurEra = false;
			newDate.second = this->second + d2.second;
			newDate.minute = this->minute + d2.minute;
			newDate.hour = this->hour + d2.hour;
			newDate.day = this->day + d2.day;
			newDate.SetNormalTime1();
			newDate.month = this->month + d2.month;
			newDate.year = this->year + d2.year;
			newDate.SetNormalTime2();
		}
		return newDate;
	}

	void operator -=(const Date& d2)
	{
		*this = *this - d2;
	}


};

int main()
{
	Date date1;
	date1 = date1.add(50, 5, 28, 4, 3, 2);
	cout << date1;

}