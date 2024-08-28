#include "imagepaint.h"

#include <QPainter>

ImagePaint::ImagePaint(QWidget *parent) : QWidget(parent) {}

void ImagePaint::setImage(QImage &&image) Q_DECL_NOEXCEPT
{
    this->image = qMove(image);
}

void ImagePaint::setImage(const QImage &image)
{
    this->image = image;
}

void ImagePaint::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, this->image);
}
