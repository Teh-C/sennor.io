#ifndef STOPRIGHT_H
#define STOPRIGHT_H

#include <QWidget>
#include <QPainter>
namespace Ui {
class STopRight;
}

class STopRight : public QWidget
{
    Q_OBJECT

public:
    explicit STopRight(QWidget *parent = 0);
    ~STopRight();
protected:

    void paintEvent(QPaintEvent *event);

private:
    Ui::STopRight *ui;
    QPixmap m_localPix;
    void SetPixmap(const QPixmap &pix);
};

#endif // STOPRIGHT_H
