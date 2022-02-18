#include "ImageMarkWidget.h"
#include <QPainter>
#include <QMouseEvent>

#include <QListView>
#include <QStringListModel>

ImageMarkWidget::ImageMarkWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setMouseTracking(true);
}

void ImageMarkWidget::setDarknetHelper(DarknetHelper *helper)
{
    m_helper = helper;
    mObjPath = m_helper->objPath();
}

void ImageMarkWidget::setLabels(QListView *view)
{
    mLabels = view;
}

void ImageMarkWidget::currentFilename(const QString &filename)
{
    mFilename = filename;
    mPixmap = QPixmap(mObjPath + mFilename);
    mBoxes.clear();
    auto txt = mObjPath + filename.split(".").first() + ".txt";
    if(QFile::exists(txt)){
        QFile fs(txt);
        if(fs.open(QIODevice::ReadOnly)){
            QTextStream in(&fs);
            QString line;
            while (in.readLineInto(&line)) {
                auto list = line.split(" ");
                mBoxes.append({list.at(0).toInt(),
                               list.at(1).toDouble(),
                               list.at(2).toDouble(),
                               list.at(3).toDouble(),
                               list.at(4).toDouble()});
            }
        }
    }
    update();
}

void ImageMarkWidget::clearMark()
{
    for(auto it = mBoxes.begin();it != mBoxes.end();){
        auto [x,y,w,h] = (*it).calcRealRect();
                auto rectf = QRectF{width() * x,height() * y,width() * w,height() * h};
        if(rectf.contains(mapFromGlobal(QCursor::pos()))){
            it = mBoxes.erase(it);
        }else{
            ++it;
        }
    }
    //mBoxes.clear();
    //save
    save(mObjPath + mFilename.split(".").first() + ".txt",mBoxes);
    update();
}

void ImageMarkWidget::switchLabel()
{
    mSwitchLabel = !mSwitchLabel;
    update();
}

void ImageMarkWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.f,0.f,0.f,0.f);
}

void ImageMarkWidget::resizeGL(int w, int h)
{
    return QOpenGLWidget::resizeGL(w,h);
}

void ImageMarkWidget::paintGL()
{
    QPainter painter(this);

    QTransform tf = QTransform::fromScale((qreal)mPixmap.width() / (qreal)width(),(qreal)mPixmap.height() / (qreal)height()).inverted();
    painter.drawPixmap(0,0,mPixmap.transformed(tf),0,0,0,0);

    QString text = QString("%1 %2x%3 %4 %5")
            .arg(mFilename)
            .arg(mPixmap.width())
            .arg(mPixmap.height())
            .arg(tf.m11())
            .arg(tf.m22());
    painter.drawText(10,10,text);

    //<-prev next-> clear_mark hide_object_name show_coords esc-exit

    if(mMouseInWidget.first){
        const auto &pos = mMouseInWidget.second;
        painter.drawLine(0,pos.y(),width(),pos.y());
        painter.drawLine(pos.x(),0,pos.x(),height());
    }

    if(mDrawRect.first){
        if(mLabels->currentIndex().isValid()){
            auto number = mLabels->currentIndex().row();
            auto lable = mLabels->currentIndex().data().toString();
            auto text = QString("%1-%2").arg(number).arg(lable);
            auto pos = mDrawRect.second.topLeft();

            // 字符串哈希颜色
            int hash = qHash(text);
            int r = (hash & 0xFF0000) >> 16;
            int g = (hash & 0x00FF00) >> 8;
            int b = hash & 0x0000FF;
            QColor color(r,g,b);

            QFont font;
            font.setPixelSize(14);
            font.setBold(true);
            painter.setFont(font);

            QFontMetrics fm(font);
            auto textRect = QRect{(qint32)pos.x(),(qint32)pos.y() - fm.height(),fm.horizontalAdvance(text),fm.height()};

            QPen pen(color);
            pen.setWidthF(1.0f);
            painter.setPen(pen);
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(mDrawRect.second);

            QBrush brush(color,Qt::SolidPattern);
            painter.setBrush(brush);
            painter.drawRect(textRect);

            pen.setColor(Qt::black);
            painter.setPen(pen);
            painter.drawText(textRect,Qt::AlignVCenter,text);
        }
    }

    auto model = static_cast<QStringListModel*>(mLabels->model());
    for(auto &a : mBoxes){
        auto [x,y,w,h] = a.calcRealRect();
                auto rectf = QRectF{width() * x,height() * y,width() * w,height() * h};
        auto label = model->index(a.row).data().toString();
        auto text = QString("%1-%2").arg(a.row).arg(label);
        auto pos = rectf.topLeft();

        int hash = qHash(text);
        int r = (hash & 0xFF0000) >> 16;
        int g = (hash & 0x00FF00) >> 8;
        int b = hash & 0x0000FF;
        QColor color(r,g,b);

#if 0
        // 计算补色 强烈对比度
        auto complementary_color = [](QColor &color)->QColor{
            auto hsv = color.toHsv();
            auto h = (hsv.hsvHue() + 180) % 360;
            return QColor::fromHsv(h,hsv.saturation(),hsv.value());
        }(color);
#endif

        QFont font;
        font.setPixelSize(14);
        font.setBold(true);
        painter.setFont(font);

        QFontMetrics fm(font);
        auto textRect = QRect{(qint32)pos.x(),(qint32)pos.y() - fm.height(),fm.horizontalAdvance(text),fm.height()};

        QPen pen(color);
        pen.setWidthF(1.0f);

        if(rectf.contains(mapFromGlobal(QCursor::pos()))){
            pen.setWidthF(3.0f);
        }

        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(rectf);

        if(!mSwitchLabel){
            QBrush brush(color,Qt::SolidPattern);
            painter.setBrush(brush);
            painter.drawRect(textRect);

            pen.setColor(Qt::black);
            painter.setPen(pen);
            painter.drawText(textRect,Qt::AlignVCenter,text);
        }
    }
}

void ImageMarkWidget::enterEvent(QEvent *e)
{
    mMouseInWidget.first = true;
    QOpenGLWidget::enterEvent(e);
    update();
}

void ImageMarkWidget::leaveEvent(QEvent *e)
{
    mMouseInWidget.first = false;
    QOpenGLWidget::leaveEvent(e);
    update();
}

void ImageMarkWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(mMouseInWidget.first){
        mMouseInWidget.second = e->pos();
    }
    if(mState == State::Draw){
        mDrawRect.second.setBottomRight(e->pos());
        mDrawRect.first = true;
    }
    QOpenGLWidget::mouseMoveEvent(e);
    update();
}

void ImageMarkWidget::mousePressEvent(QMouseEvent *e)
{
    if(mLabels->currentIndex().isValid()){
        mState = State::Draw;
        mDrawRect.second.setTopLeft(e->pos());
        mDrawRect.first = false;
    }
    QOpenGLWidget::mousePressEvent(e);
    update();
}

void ImageMarkWidget::mouseReleaseEvent(QMouseEvent *e)
{
    mState = State::None;
    if(mDrawRect.first){
        mDrawRect.second = mDrawRect.second.normalized();
        auto rect = mDrawRect.second;
        Boxes box;
        box.row = mLabels->currentIndex().row();
        auto center = rect.center();
        box.realXC = center.x() / (qreal)width();
        box.realYC = center.y() / (qreal)height();
        box.realW = rect.width() / (qreal)width();
        box.realH = rect.height() / (qreal)height();
        mBoxes.push_back(box);

        //save
        save(mObjPath + mFilename.split(".").first() + ".txt",mBoxes);

        mDrawRect.first = false;
    }
    QOpenGLWidget::mouseReleaseEvent(e);
    update();
}

void ImageMarkWidget::resizeEvent(QResizeEvent *e)
{
    QOpenGLWidget::resizeEvent(e);
    update();
}

void ImageMarkWidget::save(QString filename,QVector<Boxes> boxes)
{
    QThread::create([](QString filename,QVector<Boxes> boxes){
        QFile fs(filename);
        if(fs.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
            for(auto &a:boxes){
                fs.write(QString("%1 %2 %3 %4 %5\n")
                         .arg(a.row)
                         .arg(a.realXC)
                         .arg(a.realYC)
                         .arg(a.realW)
                         .arg(a.realH).toUtf8());
            }
        }
    },filename,boxes)->start();
}
