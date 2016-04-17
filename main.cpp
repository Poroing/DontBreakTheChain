
#include <qt/QtWidgets/QApplication>
#include <qt/QtCore/QDir>

#include "mainwindow.hpp"

void goToMainDirectory() noexcept
{
    QDir dir(::qgetenv("HOME") + "/.dbtc");
    dir.mkpath(dir.path());
    dir.setCurrent(dir.path());
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    goToMainDirectory();
    MainWindow win;
    win.show();

    return app.exec();
};
