#ifndef IMAGEMARKWINDOW_H
#define IMAGEMARKWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QDebug>
#include <QPixmapCache>
#include <QKeyEvent>
#include "DarknetHelper.h"

class ItemDelegate : public QStyledItemDelegate
{
public:
    explicit ItemDelegate(DarknetHelper *helper,QObject *parent = 0) : QStyledItemDelegate(parent),m_helper(helper) {
        // 设置 1GB 图像内存缓存
        QPixmapCache::setCacheLimit(1024 * 1000);
        mObjPath = m_helper->objPath();
    }
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override{
        // Set the background color
        //QBrush background = ( option.state & QStyle::State_Selected ) ? option.palette.highlight() : option.palette.base();
        //painter->fillRect(option.rect, background);

        if (option.state & QStyle::State_Selected){
            QPen pen(Qt::green, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
            painter->setPen(pen);
            painter->drawRect(option.rect.adjusted(0,0,-1,-1));
            painter->setPen(option.palette.highlightedText().color());
        }else{
            painter->setPen(option.palette.text().color());
        }

        painter->drawText(option.rect,Qt::AlignCenter,QString::number(index.row()));

        QPixmap pixmap;
        if(!QPixmapCache::find(index.data(Qt::DisplayRole).toString(),&pixmap)){
            pixmap = QPixmap(mObjPath + index.data(Qt::DisplayRole).toString());
            pixmap = pixmap.scaled(114,64);
            QPixmapCache::insert(index.data(Qt::DisplayRole).toString(),pixmap);
        }
        painter->drawPixmap(option.rect.adjusted(1,1,-1,-1),pixmap,pixmap.rect());

        //
        static QPixmap ok(":/resource/ok.png");
        auto txt = mObjPath + index.data(Qt::DisplayRole).toString().split(".").first() + ".txt";
        if(QFile::exists(txt)){
            painter->drawPixmap(option.rect.x() - 64 + option.rect.width(),option.rect.y() - 64 + option.rect.height(),ok);
        }
    }

    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override{
        Q_UNUSED(option)
        Q_UNUSED(index)
        return {114 + 4,64 + 4 + 22};
    }
private:
    DarknetHelper *m_helper;
    QString mObjPath;
};

namespace Ui {
class ImageMarkWindow;
}

class ImageMarkWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageMarkWindow(DarknetHelper *helper,QWidget *parent = nullptr);
    ~ImageMarkWindow();
protected:
    virtual void keyPressEvent(QKeyEvent *e) override {
        switch (e->key()) {
        case Qt::Key_C:{
            emit clearMark();
            break;
        }
        case Qt::Key_H:{
            emit switchLabel();
            break;
        }
        default:
            break;
        }
        QMainWindow::keyPressEvent(e);
    }
signals:
    void clearMark();
    void switchLabel();
private:
    Ui::ImageMarkWindow *ui;
    DarknetHelper *m_helper;
    QFileSystemModel *m_model;
};

#endif // IMAGEMARKWINDOW_H
