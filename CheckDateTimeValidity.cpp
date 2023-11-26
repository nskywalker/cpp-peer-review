void CheckYearValidaty(Year year) {
    if (year < 1) {
        throw domain_error("year is too small"s);
    }
    if (year > 9999) {
        throw domain_error("year is too big"s);
    }
}

void CheckMonthValidaty(Month month) {
    if (month < 1) {
        throw domain_error("month is too small"s);
    }
    if (month > 12) {
        throw domain_error("month is too big"s);
    }
}

void CheckDayVallidaty(Day day, Month month, Year year) {
    const bool is_leap_year = (year % 4 == 0) && !(year % 100 == 0 && year % 400 != 0);
    const array month_lengths = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (day < 1) {
        throw domain_error("day is too small"s);
    }
    if (day > month_lengths[month - 1]) {
        throw domain_error("day is too big"s);
    }    
}

void CheckHourValidaty(Hour hour) {
    if (hour < 0) {
        throw domain_error("hour is too small"s);
    }
    if (hour > 23) {
        throw domain_error("hour is too big"s);
    }
}

void CheckMinuteValidaty(Minute minute) {
    if (minute < 0) {
        throw domain_error("minute is too small"s);
    }
    if (minute > 59) {
        throw domain_error("minute is too big"s);
    }
}

void CheckSecondValidaty(Second second) {
    if (second < 0) {
        throw domain_error("second is too small");
    }
    if (second > 59) {
        throw domain_error("second is too big"s);
    }
}

void CheckDateTimeValidity(const DateTime& dt) {
    CheckYearValidaty(dt.year);
    CheckMonthValidaty(dt.month);
    CheckDayVallidaty(dt.day, dt.month, dt.year);
    CheckHourValidaty(dt.hour);
    CheckMinuteValidaty(dt.minute);
    CheckSecondValidaty(dt.second);
}