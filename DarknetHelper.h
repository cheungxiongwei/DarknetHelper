#ifndef DARKNETHELPER_H
#define DARKNETHELPER_H

#include <QObject>
#include <QtCore>
#include <QColor>

class DarknetHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(quint32 batch READ batch WRITE setBatch NOTIFY batchChanged)
    Q_PROPERTY(quint32 subdivision READ subdivision WRITE setSubdivision NOTIFY subdivisionChanged)
    Q_PROPERTY(quint32 classes READ classes WRITE setClasses NOTIFY classesChanged)
    Q_PROPERTY(quint32 type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(quint32 width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(quint32 height READ height WRITE setHeight NOTIFY heightChanged)

    Q_PROPERTY(bool init READ init WRITE setInit NOTIFY initChanged)
public:
    explicit DarknetHelper(QObject *parent = nullptr);
    ~DarknetHelper();
    void run();

    QString objPath() const {
        return path() + R"(/data/obj/)";
    }
    QString objNamesFilename() const {
        return path() + R"(/data/obj.names)";
    }

    const QString &path() const;
    void setPath(const QString &newPath);

    quint32 batch() const;
    void setBatch(quint32 newBatch);

    quint32 subdivision() const;
    void setSubdivision(quint32 newSubdivision);

    quint32 classes() const;
    void setClasses(quint32 newClasses);

    quint32 type() const;
    void setType(quint32 newType);

    quint32 width() const;
    void setWidth(quint32 newWidth);

    quint32 height() const;
    void setHeight(quint32 newHeight);

    bool init() const;
    void setInit(bool newInit);

signals:

    void pathChanged();

    void batchChanged();

    void subdivisionChanged();

    void classesChanged();

    void typeChanged();

    void widthChanged();

    void heightChanged();

    void initChanged();

private:
    QString m_path;
    quint32 m_batch;
    quint32 m_subdivision;
    quint32 m_classes;
    quint32 m_type;
    quint32 m_width;
    quint32 m_height;
    bool m_init = false;
};

#endif // DARKNETHELPER_H
