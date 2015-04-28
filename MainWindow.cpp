#include <iostream>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "main/GeneticMain.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    constexpr int w = Field::fieldWidth;
    constexpr int h = Field::fieldHeight;

    tableModel = new QStandardItemModel(h, w, this);

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            QStandardItem *item = new QStandardItem("");
            tableModel->setItem(j, i, item);
        }
    }

    ui->fieldView->setModel(tableModel);
    ui->fieldView->resizeColumnsToContents();

    constexpr int chromosomesCount = 20;
    constexpr int colsCount = 2;
    statsModel = new QStandardItemModel(chromosomesCount, colsCount, this);

    for (int i = 0; i < chromosomesCount; ++i) {
        for (int j = 0; j < colsCount; ++j) {
            QStandardItem *item = new QStandardItem("0");
            statsModel->setItem(i, j, item);
        }
    }
    ui->statsView->setModel(statsModel);

    qRegisterMetaType<Field>("Field");

    workerThread = new WorkerThread(chromosomesCount, this);
    workerThread->start();

    QObject::connect(workerThread,
                    &WorkerThread::fieldChanged,
                    this,
                    &MainWindow::renderField);

    QObject::connect(workerThread,
                &WorkerThread::statsChanged,
                this,
                &MainWindow::renderStats);
}

void MainWindow::renderField(const Field& field) {

    for(int j = 0; j < Field::fieldHeight; ++j) {
        for(int i = 0; i < Field::fieldWidth; ++i) {
            auto item = tableModel->item(j, i);

            if(field.at(i, j))
                item->setBackground(blockBrush);
            else
                item->setBackground(emptyBrush);
        }
    }

    ui->fieldView->repaint();
}

void MainWindow::renderStats(int chromosomeId, int score, int gameStepsCount) {
    auto scoreItem = statsModel->item(chromosomeId, 0);
    scoreItem->setText(QString::number(score));

    auto gameStepsCountItem = statsModel->item(chromosomeId, 1);
    gameStepsCountItem->setText(QString::number(gameStepsCount));

    ui->statsView->repaint();
}

MainWindow::~MainWindow()
{
    workerThread->stop();
    workerThread->wait();
    delete ui;
}