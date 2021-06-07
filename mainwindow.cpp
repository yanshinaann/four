#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowState(Qt::WindowMinimized);

    initLogDoc();
    initToolBar();
    initTheme();
    initApp();
}

MainWindow::~MainWindow()
{
    delete graphApp;
    delete logWindow;

    delete ui->graphicsView;
    delete ui;
}

void MainWindow::initToolBar()
{
    QToolBar *toolsBar = ui->toolBar;
    QAction *importGraph = ui->actionImport_graph;
    QAction *start = ui->actionStart;
    QAction *exportAction = ui->actionExport_result;

    QAction *openLog = ui->logWidget->toggleViewAction();
    toolsBar->addAction(importGraph);
    toolsBar->addAction(openLog);
    toolsBar->addAction(start);
    toolsBar->addAction(exportAction);
    toolsBar->addSeparator();
}

void MainWindow::initTheme()
{
    QPixmapCache::clear();
    qApp->setStyle(QStyleFactory::create("Fusion"));

    QPalette palette;

//    palette.setColor(QPalette::Midlight, Qt::white);

//    palette.setColor(QPalette::Window, Qt::black);
//    palette.setColor(QPalette::WindowText, Qt::black);
   palette.setColor(QPalette::Base, Qt::white);
//    palette.setColor(QPalette::AlternateBase, Qt::black);
//    palette.setColor(QPalette::ToolTipBase, Qt::black);
//    palette.setColor(QPalette::ToolTipText, Qt::black);
    palette.setColor(QPalette::Text, Qt::black);
//    palette.setColor(QPalette::Button, Qt::white);
//    palette.setColor(QPalette::ButtonText, Qt::white);
//    palette.setColor(QPalette::BrightText, Qt::red);
//    palette.setColor(QPalette::Link, Qt::white);

//    palette.setColor(QPalette::Highlight, Qt::black);
//    palette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(palette);
    qApp->setStyleSheet("QToolTip { color: #ffffff }");
}

void MainWindow::initApp()
{
    qDebug(logInfo()) << "Start app";
    graphApp = new Graph();
}

void MainWindow::initLogDoc()
{
    ui->logWidget->setVisible(false);

    QDockWidget *dockLog = ui->logWidget;
//    dockLog->setAllowedAreas(Qt::LeftDockWidgetArea);
    QAction *actionLog = dockLog->toggleViewAction();
    connect(actionLog, &QAction::toggled, this, &MainWindow::showLog);
//    actionLog->setText("log");
    const QIcon undoIcon = QIcon::fromTheme("log", QIcon(":/images/log.png"));
    actionLog->setIcon(undoIcon);
    ui->menuFile->addAction(actionLog);
}

void MainWindow::on_actionImport_graph_triggered()
{

    QString name = QFileDialog::getOpenFileName(this, "Select graph", "", "*.json");

    if (name.isEmpty())
        return;

    qDebug(logInfo()) << "Selected file name: " + name;

    try {
        graphApp->load(name);
        qDebug(logInfo()) << "Graph loaded";

        updateViewport(graphApp->getGraph());
        ui->actionStart->setEnabled(true);
        ui->actionExport_result->setEnabled(false);
    } catch (...) {
        qDebug(logCritical()) << "Graph can't load";
        QMessageBox::critical(this, "Load graph", "bad file");
    }
}

void MainWindow::updateViewport(const QVector<QVector<int> > &graph)
{
    ui->graphicsView->setGraph(graph);
}

void MainWindow::showLog(bool value)
{
    if (!value)
        return;

    QFile file("logFile.txt");
    file.open(QFile::ReadOnly);
    ui->textBrowser->setText(file.readAll());
    qDebug(logInfo()) << "Show Log";
}

void MainWindow::on_actionStart_triggered()
{
    qDebug(logInfo()) << "Start process";

    try {
        ui->graphicsView->updateColor(graphApp->searchComponents());
        ui->actionExport_result->setEnabled(true);
    } catch (...) {
        qDebug(logCritical()) << "Bad Graph: No graph to process";
       QMessageBox::critical(this, "Bad Graph", "No graph to process");
    }
}

void MainWindow::on_actionExport_result_triggered()
{

    QString name = QFileDialog::getSaveFileName(this, "Graph export", "", "*.json");
    qDebug(logInfo()) << "Filename to save: " + name;

    graphApp->save(name);

    qDebug(logInfo()) << "Result exported";
}
