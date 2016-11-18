#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
//Incluimos librerias necesarias
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QFontDialog>
#include <QClipboard>
#include <QKeySequence>
#include <QApplication>
#include <QMessageBox>
#include <QIcon>
#include <QToolBar>
#include <QPixmap>
#include <QTextCursor>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

private slots:
    void alAbrir();
    void alGuardar();
    void alFuente();
    void alSalir();
    void alSobre();


private:
    QMenuBar*       mainMenu_;
    QMenu*          mnuArchivo_;
    QAction*        actArchivoAbrir_;
    QAction*        actArchivoGuardar_;
    QAction*        actArchivoSalir_;
    QMenu*          mnuFormato_;
    QAction*        actFormatoFuente_;
    QMenu*          mnuEditar_;
    QAction*        actEditarCopiar_;
    QAction*        actEditarPegar_;
    QAction*        actEditarCortar_;
    QAction*        actEditarUndo_;
    QAction*        actEditarRedo_;
    QMenu*          mnuAyuda_;
    QAction*        actAyudaSobre_;
    QTextEdit*      txtEditor_;
    QClipboard *    portapapeles_;
    QToolBar*       toolBar_;
    QString        path_;
    QAction*        actToolCopiar_;
    QAction*        actToolCortar_;
    QAction*        actToolPegar_;

};

#endif // NOTEPADWINDOW_H
