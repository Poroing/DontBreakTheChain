#ifndef _H_DBTC_MAINWINDOW_H_
#define _H_DBTC_MAINWINDOW_H_

#include <qt/QtWidgets/QMainWindow>
#include <qt/QtCore/QSet>
#include <qt/QtCore/QFile>

#include "calendar.hpp"

#define FILENAME "$HOME/.dbtc/dates"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    virtual ~MainWindow();

protected:
    virtual void closeEvent(QCloseEvent *event) noexcept override;

public slots:
    void saveMarkedDates() noexcept;

private:
    void createMenus() noexcept;
    void initCalendar() noexcept;

    Calendar* cal;
    QFile* file;
};

#endif
