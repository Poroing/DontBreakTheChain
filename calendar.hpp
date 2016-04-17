#ifndef _H_DBTC_CALENDAR_H_
#define _H_DBTC_CALENDAR_H_

#include <qt/QtWidgets/QCalendarWidget>
#include <qt/QtCore/QSet>
#include <qt/QtGui/QTextCharFormat>


class Calendar : public QCalendarWidget
{
    Q_OBJECT

public:

    explicit Calendar(QWidget* parent = Q_NULLPTR);
    
    void setDefaultTextFormat(const QTextCharFormat& default_tcf) noexcept;
    void setMarkedDates(const QSet<QDate>& dates) noexcept;
    void clearMarkedDates() noexcept;
    
    const QSet<QDate>& markedDates() noexcept;

    virtual ~Calendar();

public slots:
    void toggleMarkSelectedDate() noexcept;
    void toggleMarkDate(const QDate& date) noexcept;

    void markDate(const QDate& date) noexcept;
    void unmarkDate(QSet<QDate>::iterator& date_pos) noexcept;

signals:
    void dateMarked(const QDate& date);
    void dateUnMarked(const QDate& date);

private:
    void initTextFormat() noexcept;
    void enhance() noexcept;

    QTextCharFormat mark_tcf;
    QTextCharFormat default_tcf;
    QSet<QDate> marked_dates;
};

#endif
