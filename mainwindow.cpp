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
//    Answer ans = problem.GetAnswer(std::unique_ptr<Solver>(new Cutting_plane()));
//    Answer ans = problem.GetAnswer(std::unique_ptr<Solver>(new SlowSolver()));
    Answer ans = problem.GetAnswer(std::unique_ptr<Solver>(new Glpk_solution()));
    freopen("out", "w", stdout);
    std::cout << "\n";
    for (const auto& cnt : ans.counts) {
        std::cout << cnt << " ";
    }
    Planes_.reserve(ans.counts.size());
    int x = 25;
    int y = 100;
    for (size_t i = 0; i < ans.counts.size(); i++) {
        const auto& plane = ans.planes.GetColumn(i);
        std::vector<size_t> cuts;
        for (size_t j = 0; j < plane.size(); j++)
            for (size_t l = 0; l < plane[j]; l++)
                cuts.push_back(problem.Get_Ls()[j]);
        Planes_.emplace_back(x, y, ans.counts[i], problem.Get_L(), cuts, this);
        y += 25;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* e) {
    for (auto& plane : Planes_)
        plane.Drow();

}
