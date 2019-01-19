#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bits/stdc++.h>
#include <QtDebug>

#include "cutting_plane.h"
#include "cuttingstockproblem.h"
#include "generator.h"
#include "slow_solver.h"
#include "matrix.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    bool Test();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
