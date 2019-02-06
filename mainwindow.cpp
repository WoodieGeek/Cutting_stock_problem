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
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::Test() {
    CuttingStockProblem problem(Generator::GetProblem());
    Answer solve(problem.GetAnswer(std::unique_ptr<Cutting_plane>(new Cutting_plane())));
    Answer ez_solve(problem.GetAnswer(std::unique_ptr<SlowSolver>(new SlowSolver())));
    size_t ans_solve = std::accumulate(solve.counts.begin(), solve.counts.end(), (size_t)0);
    size_t ans_ez_solve = std::accumulate(ez_solve.counts.begin(), ez_solve.counts.end(), (size_t)0);
    if (ans_solve == ans_ez_solve) {
        qDebug() << "OK";
        return true;
    }
    else {
        qDebug() << "Solve " << ans_solve;
        qDebug() << "Ez Solve " << ans_ez_solve;
        return true;
    }
}
