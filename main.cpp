// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include "stick.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Stick w;
    w.show();

    return a.exec();
}
