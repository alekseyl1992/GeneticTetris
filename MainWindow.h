#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QStandardItemModel>
#include "WorkerThread.h"
#include <QBrush>
#include <QColor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *tableModel;
    QStandardItemModel *statsModel;

    QBrush blockBrush = QColor(0, 0, 255);
    QBrush emptyBrush = QColor(255, 255, 255);

    WorkerThread *workerThread;

public slots:
    void renderField(const Field& field);
    void renderStats(int chromosomeId, int score, int gameStepsCount);
};

#endif // MAINWINDOW_H
