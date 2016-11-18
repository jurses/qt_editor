#include "notepadwindow.h"

NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Establecemos el tamaño inicial de la ventana
    this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Super editor de texto"));

    // Cursor
    QTextCursor    textCursor_ = txtEditor_->textCursor();
    textCursor_.setPosition(QTextCursor::StartOfWord);
    textCursor_.setPosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this);

    toolBar_ = addToolBar("main toolbar");
    path_="/home/jurses/Programas/curso/Qt_CodigoBase_Editor/curso-qt-osl-notepad/";
    QPixmap pCopiar(path_+"copy-icon.png");
    QPixmap pCortar(path_+"cut-icon.png");
    QPixmap pPegar(path_+"clipboard_paste.png");

    actToolCopiar_ = new QAction(tr("&Copiar"),this);
    actToolCortar_ = new QAction(tr("&Cortar"),this);
    actToolPegar_ = new QAction(tr("&Pegar"),this);

    actToolCopiar_ = toolBar_->addAction(QIcon(pCopiar),"Copiar");

    actToolCortar_ = toolBar_->addAction(QIcon(pCortar),"Cortar");

    actToolPegar_ = toolBar_->addAction(QIcon(pPegar),"Pegar");


    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);


    actArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnuArchivo_->addAction(actArchivoGuardar_);
    actArchivoSalir_ = new QAction("Salir", this) ;
    mnuArchivo_->addAction(actArchivoSalir_);   // salir

    mnuEditar_ = new QMenu(tr("&Editar"), this);
    mainMenu_->addMenu(mnuEditar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    mnuEditar_->addAction(actEditarPegar_);

    actEditarCortar_ = new QAction(tr("&Cortar"), this);
    actEditarCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    mnuEditar_->addAction(actEditarCortar_);

    actEditarUndo_ = new QAction(tr("&Deshacer"), this);
    actEditarUndo_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    mnuEditar_->addAction(actEditarUndo_);

    actEditarRedo_ = new QAction(tr("&Rehacer"), this);
    actEditarRedo_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    mnuEditar_->addAction(actEditarRedo_);

    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    mnuFormato_->addAction(actFormatoFuente_);

    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaSobre_ = new QAction(tr("&Acerca de"), this);
    mnuAyuda_->addAction(actAyudaSobre_);

    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_);

    //Inicializamos el editor de texto
    txtEditor_ = new QTextEdit(this);

    //Conectamos las acciones de los menús con nuestros slots
    connect(actArchivoAbrir_,   SIGNAL(triggered()), this,          SLOT(alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()), this,          SLOT(alGuardar()));
    connect(actEditarCopiar_,   SIGNAL(triggered()), txtEditor_,    SLOT(copy()));
    connect(actEditarPegar_,    SIGNAL(triggered()), txtEditor_,    SLOT(paste()));
    connect(actFormatoFuente_,  SIGNAL(triggered()),this,          SLOT(alFuente()));
    connect(actArchivoSalir_,   SIGNAL(triggered()),    this,       SLOT(alSalir()));
    connect(actEditarCortar_,   SIGNAL(triggered()),    txtEditor_, SLOT(cut()));
    connect(actEditarUndo_,     SIGNAL(triggered()), txtEditor_,     SLOT(undo()));
    connect(actEditarRedo_,     SIGNAL(triggered()), txtEditor_,     SLOT(redo()));
    connect(actAyudaSobre_,     SIGNAL(triggered()), this,     SLOT(alSobre()));
    connect(actToolCopiar_,   SIGNAL(triggered()), txtEditor_,     SLOT(copy()));
    connect(actToolCortar_,   SIGNAL(triggered()), txtEditor_,     SLOT(cut()));
    connect(actToolPegar_,   SIGNAL(triggered()), txtEditor_,     SLOT(paste()));

    //Agregamos el editor de texto a la ventana
    this->setCentralWidget(txtEditor_);
}

NotepadWindow::~NotepadWindow()
{
    //Liberamos los recursos
    mainMenu_->deleteLater();
    actArchivoAbrir_->deleteLater();
    actArchivoGuardar_->deleteLater();
    mnuArchivo_->deleteLater();
    actEditarCopiar_->deleteLater();
    actEditarPegar_->deleteLater();
    mnuEditar_->deleteLater();
    actFormatoFuente_->deleteLater();
    mnuFormato_->deleteLater();
    txtEditor_->deleteLater();
}

void NotepadWindow::alAbrir()
{
    //Mostramos un dialogo de apertura de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this,
                                                 tr("Abrir archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)"));
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::ReadOnly)) {
            //Si se pudo abrir el archivo, lo leemos y colocamos su contenido en nuestro editor
            txtEditor_->setHtml(archivo.readAll());
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alSalir(){
    QApplication::quit();
}

void NotepadWindow::alSobre(){
    QMessageBox::about(this,"Acerca de ...", "Bla bla bla");
}

void NotepadWindow::alGuardar()
{
    //Mostramos un dialogo de guardado de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getSaveFileName(this,
                                                 tr("Guardar archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)"));
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo + ".txt");
        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
            //Si se pudo abrir el archivo, escribimos el contenido del editor
            archivo.write(txtEditor_->toHtml().toUtf8());
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alFuente()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this);
    if (ok) {
        // Si el usuario hizo click en OK, se establece la fuente seleccionada
        txtEditor_->setFont(font);
    }
}
