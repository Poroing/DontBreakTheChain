#include "calendar.hpp"

#include <algorithm>
#include <functional>

#include <iostream>


Calendar::Calendar(QWidget *parent):
    QCalendarWidget(parent)
{
    initTextFormat();
    enhance();
};

//==================
//  Public Methods
//==================

void Calendar::setDefaultTextFormat(const QTextCharFormat& new_default_tcf) noexcept
{
    for (Qt::DayOfWeek day = Qt::Monday; day <= Qt::Sunday;
        day = static_cast<Qt::DayOfWeek>(static_cast<int>(day) + 1))
        setWeekdayTextFormat(day, new_default_tcf);
};

void Calendar::setMarkedDates(const QSet<QDate>& dates) noexcept
{
    clearMarkedDates();
    for (const QDate date : dates)
        setDateTextFormat(date, mark_tcf);
    marked_dates = dates;
};

void Calendar::clearMarkedDates() noexcept
{
    for (const QDate date: marked_dates)
        setDateTextFormat(date, mark_tcf);
    marked_dates.clear();
}

const QSet<QDate>& Calendar::markedDates() noexcept
{
    return marked_dates;
};

//========
//  SLOTS
//=========

void Calendar::toggleMarkSelectedDate() noexcept
{
    toggleMarkDate(selectedDate());
};

void Calendar::toggleMarkDate(const QDate& date) noexcept
{
    QSet<QDate>::iterator pos = marked_dates.find(date);
    if (pos == marked_dates.end()) markDate(date);
    else unmarkDate(pos);
};

void Calendar::markDate(const QDate& date) noexcept
{
    setDateTextFormat(date, mark_tcf);
    marked_dates.insert(date);
    emit dateMarked(date);
};

void Calendar::unmarkDate(QSet<QDate>::iterator& date_pos) noexcept
{
    setDateTextFormat(*date_pos, default_tcf);
    marked_dates.erase(date_pos);
    emit dateUnMarked(*date_pos);
};

//===================
//  Private Methods
//===================

void Calendar::initTextFormat() noexcept
{
    mark_tcf.setBackground(QBrush(Qt::blue));
    mark_tcf.setForeground(QBrush(Qt::yellow));

    default_tcf.setBackground(QBrush(Qt::white));
    default_tcf.setForeground(QBrush(Qt::black));

    setDefaultTextFormat(default_tcf);
};

void Calendar::enhance() noexcept
{
    QTextCharFormat tcf;
    tcf.setForeground(QBrush(Qt::red));
    setDateTextFormat(QDate::currentDate(), tcf);
};

Calendar::~Calendar() {};
