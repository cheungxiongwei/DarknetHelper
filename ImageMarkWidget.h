#ifndef IMAGEMARKWIDGET_H
#define IMAGEMARKWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QtCore>

#include "DarknetHelper.h"

struct Boxes
{
    int row;
    qreal realXC;
    qreal realYC;
    qreal realW;
    qreal realH;
    std::tuple<qreal,qreal,qreal,qreal> calcRealRect(){
        return {realXC - realW / 2.0,realYC - realH / 2.0,realW,realH};
    }
};

class QListView;
class ImageMarkWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit ImageMarkWidget(QWidget *parent = nullptr);
    void setDarknetHelper(DarknetHelper *helper);
    void setLabels(QListView *view);
signals:
public slots:
    void currentFilename(const QString &filename);

    void clearMark();
    void switchLabel();
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

    virtual void enterEvent(QEvent *e) override;
    virtual void leaveEvent(QEvent *e) override;

    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseReleaseEvent(QMouseEvent *e) override;

    virtual void resizeEvent(QResizeEvent *e) override;
private:
    void save(QString filename,QVector<Boxes> boxes);
private:
    DarknetHelper *m_helper = nullptr;
    QString mObjPath;
    QPixmap mPixmap;
    QString mFilename;

    //
    QListView *mLabels = nullptr;
    QStringList mLables;

    QPair<bool,QPoint> mMouseInWidget{false,QPoint()};

    //
    enum State{None,Draw};
    State mState = State::None;
    QPair<bool,QRect> mDrawRect{false,QRect()};
    QVector<Boxes> mBoxes;

    //
    bool mSwitchLabel = false;
};

#endif // IMAGEMARKWIDGET_H
