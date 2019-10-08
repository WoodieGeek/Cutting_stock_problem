#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bits/stdc++.h>
#include <QtDebug>
#include <QPainter>
#include <QLabel>

#include "cutting_plane.h"
#include "cuttingstockproblem.h"
#include "generator.h"
#include "slow_solver.h"
#include "matrix.h"
#include "glpk_solution.h"
#include "plane.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
public:
    void paintEvent(QPaintEvent* e) override;
private:
    Ui::MainWindow *ui;
    std::vector<Plane> Planes_;
};

#endif // MAINWINDOW_H
