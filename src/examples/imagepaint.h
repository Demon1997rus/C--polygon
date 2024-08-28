#ifndef IMAGEPAINT_H
#define IMAGEPAINT_H

#include <QImage>
#include <QWidget>

class ImagePaint : public QWidget {
    Q_OBJECT
public:
    explicit ImagePaint(QWidget *parent = nullptr);

public:
    void setImage(QImage &&image) Q_DECL_NOEXCEPT;
    void setImage(const QImage &image);

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QImage image;
};

#endif // IMAGEPAINT_H
