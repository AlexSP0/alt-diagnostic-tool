#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    ClickableLabel(QWidget *parent = nullptr);

signals:
    void doubleClicked();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event)
    {
        QLabel::mouseDoubleClickEvent(event);
        emit this->doubleClicked();
    }
};

#endif // CLICKABLELABEL_H
