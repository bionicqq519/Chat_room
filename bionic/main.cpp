#include <QtWidgets/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
/*
    1.search.cpp 255行 hw3的bug要在這fix . 下次再改
      search_u->delspace(&parameter);   //這邊裡面有順便檢查格式

    2.沒有考慮連線失敗的狀況

*/
