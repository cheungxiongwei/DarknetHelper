#include "ImageMarkListView.h"
#include <QDebug>

ImageMarkListView::ImageMarkListView(QWidget *parent) : QListView(parent)
{

}

void ImageMarkListView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if(current.row() > -1){
        emit currentFilename(current.data(Qt::DisplayRole).toString());
    }
    QListView::currentChanged(current,previous);
}
