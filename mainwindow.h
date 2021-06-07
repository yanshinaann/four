#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QPixmapCache>
#include <QStyleFactory>
#include <QFileDialog>
#include <QDateTime>
#include <QDockWidget>
#include <QMessageBox>

#include "elasticnodes/graphwidget.h"

#include "loggingcategories.h"
#include "graph.h"

#include <QRandomGenerator>
#include <QInputDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void initToolBar();
    void initTheme();
    void initApp();
    void initLogDoc();

    void on_actionImport_graph_triggered();
    void updateViewport(const QVector<QVector<int>> &graph);
    void showLog(bool value);
    void on_actionStart_triggered();
    void on_actionExport_result_triggered();
private:
    Graph* graphApp;

    Ui::MainWindow *ui;
    QDockWidget *logWindow = nullptr;
};

#endif // MAINWINDOW_H
