#include "notepadwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NotepadWindow w;
    w.show();

    return a.exec();
}
