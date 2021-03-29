#include "GraduationDesign.h"
#include <QtWidgets/QApplication>
#include "BorrowInterface.h"
#include "DDialog.h"
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    GraduationDesign w;
    //w.show();
    //DDialog w(300,200);
    //w.exec();
    return a.exec();
}
