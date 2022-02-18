#ifndef IMAGEMARKLISTVIEW_H
#define IMAGEMARKLISTVIEW_H

#include <QWidget>
#include <QListView>

class ImageMarkListView : public QListView
{
    Q_OBJECT
public:
    explicit ImageMarkListView(QWidget *parent = nullptr);

signals:
    void currentFilename(const QString &filename);
protected:
    virtual void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
private:

};

#endif // IMAGEMARKLISTVIEW_H
