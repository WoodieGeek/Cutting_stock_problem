#ifndef PLANE_H
#define PLANE_H

#include <QLabel>
#include <QPainter>
#include "matrix.h"

class Plane {
public:
    Plane(int x, int y, size_t count, size_t length, std::vector<size_t>& plane, QWidget* parent = nullptr);
    Plane() = default;
    void Drow();
private:
    void DrawRect(double& x, size_t cut, QColor color);
private:
    const int H_ = 25;
    const int W_ = 500;
    int X_, Y_;
    QPainter* Painter_;
    QLabel* CountLabel_;
    QWidget* Parent_;
    size_t Count_;
    size_t Length_;
    std::vector<size_t> Plane_;
};

#endif // PLANE_H
