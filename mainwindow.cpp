
#include <qt/QtWidgets/QMenuBar>
#include <qt/QtWidgets/QAction>
#include <qt/QtGui/QCloseEvent>

#include <algorithm>
#include <iostream>

#include "mainwindow.hpp"

MainWindow::MainWindow():
    QMainWindow()
{
    cal = new Calendar(this);
    file = new QFile("dates", this);

    setCentralWidget(cal);

    initCalendar();
    createMenus();
};

MainWindow::~MainWindow() {};

//=================
//  Public Method
//=================

void MainWindow::saveMarkedDates() noexcept
{
    file->open(QIODevice::WriteOnly);
    QDataStream out(file);
    out << cal->markedDates();
    file->close();
};

//=====================
//  Protected Methods
//=====================

void MainWindow::closeEvent(QCloseEvent *event) noexcept
{
    saveMarkedDates();
    event->accept();
};

//====================
//  Privates Methods
//====================

void MainWindow::createMenus() noexcept
{
    QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));
    QAction* markAct = new QAction(tr("&Mark Selected Date"), this);
    markAct->setShortcut(QKeySequence(Qt::Key_M));
    connect(markAct, &QAction::triggered, cal, &Calendar::toggleMarkSelectedDate);
    editMenu->addAction(markAct); 
};

void MainWindow::initCalendar() noexcept
{
    if (file->exists()) {
        QSet<QDate> marked_dates;

        file->open(QIODevice::ReadOnly);
        QDataStream in(file);
        in >> marked_dates;
        file->close();

        cal->setMarkedDates(marked_dates);
    }
};
