#include "plane.h"

Plane::Plane (int x, int y, size_t count, size_t length, std::vector<size_t>& plane, QWidget* parent)
    : X_(x)
    , Y_(y)
    , Painter_(new QPainter(parent))
    , CountLabel_(new QLabel(parent))
    , Parent_(parent)
    , Count_(count)
    , Length_(length)
    , Plane_(plane) {
}

void Plane::DrawRect(double& x, size_t cut, QColor color) {
    double w = static_cast<double>(cut) / static_cast<double>(Length_) * static_cast<double>(W_);
    QRectF rect(x, Y_, w, H_);
    Painter_->setBrush(color);
    Painter_->drawRect(rect);
    rect.setX(x + w / 2.0);
    rect.setY(Y_ + H_ / 6);
    Painter_->drawText(rect, QString::number(cut));
    x += w;
}

void Plane::Drow() {
    CountLabel_->setText(QString::number(Count_));
    CountLabel_->setGeometry(X_, Y_, 50, 25);
    CountLabel_->show();
    Painter_ = new QPainter(Parent_);
    Painter_->setBrush(QBrush(Qt::green));
    double curX = X_ + 50;
    size_t sum = 0;
    for (const auto& cut : Plane_) {
        DrawRect(curX, cut, Qt::green);
        sum += cut;
    }
    if (sum != Length_) {
        DrawRect(curX, Length_ - sum, Qt::red);
    }

}
