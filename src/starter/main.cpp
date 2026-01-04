//
// Created by soup on 30/12/2025.
//

#include <QApplication>
#include "../QT/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}