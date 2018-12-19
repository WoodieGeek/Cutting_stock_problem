#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    freopen("in", "r", stdin);
    size_t r, n;
    std::cin >> r >> n;
    std::vector<size_t> l(n), b(n);
    for (size_t  i = 0; i < n; i++) {
        std::cin >> l[i];
    }
    for (size_t i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    CuttingStockProblem problem(r, n, l, b);
    Answer ans = problem.GetAnswer(std::unique_ptr<Solver>(new Cutting_plane));
    for (const auto& plane : ans.planes) {
        for (const auto& elem : plane) {
            qDebug() << elem << " ";
        }
        qDebug() << "\n";
    }
    for (const auto& cnt : ans.counts) {
        qDebug() << cnt << " ";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
