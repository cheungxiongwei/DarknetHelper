#include "DarknetHelper.h"
#include <QString>

DarknetHelper::DarknetHelper(QObject *parent) : QObject(parent)
{
    QSettings s;
    m_path = s.value("darknethelper_path","./").toString();
    m_batch = s.value("darknethelper_batch",64).toInt();
    m_subdivision = s.value("darknethelper_subdivision",3).toInt();
    m_classes = s.value("darknethelper_classes",3).toInt();
    m_type = s.value("darknethelper_type",0).toInt();
    m_width = s.value("darknethelper_width",608).toInt();
    m_height = s.value("darknethelper_height",608).toInt();
    m_init = s.value("darknethelper_init",false).toBool();
}

DarknetHelper::~DarknetHelper()
{
    QSettings s;
    s.setValue("darknethelper_path",path());
    s.setValue("darknethelper_batch",batch());
    s.setValue("darknethelper_subdivision",subdivision());
    s.setValue("darknethelper_classes",classes());
    s.setValue("darknethelper_type",type());
    s.setValue("darknethelper_width",width());
    s.setValue("darknethelper_height",height());
    s.setValue("darknethelper_init",init());
}

void DarknetHelper::run()
{
    QString program = QSettings().value("DarknetConfig","./DarknetConfig.exe").toString();
    QStringList arguments;
    arguments << "-path" << m_path;
    arguments << "-batch" << QString::number(m_batch);
    arguments << "-subdivision" << QString::number(m_subdivision);
    arguments << "-classes" << QString::number(m_classes);
    arguments << "-type" << QString::number(m_type);
    arguments << "-width" << QString::number(m_width);
    arguments << "-height" << QString::number(m_height);
    QProcess process;
    process.execute(program, arguments);
}

const QString &DarknetHelper::path() const
{
    return m_path;
}

void DarknetHelper::setPath(const QString &newPath)
{
    if (m_path == newPath)
        return;
    m_path = newPath;
    emit pathChanged();
}

quint32 DarknetHelper::batch() const
{
    return m_batch;
}

void DarknetHelper::setBatch(quint32 newBatch)
{
    if (m_batch == newBatch)
        return;
    m_batch = newBatch;
    emit batchChanged();
}

quint32 DarknetHelper::subdivision() const
{
    return m_subdivision;
}

void DarknetHelper::setSubdivision(quint32 newSubdivision)
{
    if (m_subdivision == newSubdivision)
        return;
    m_subdivision = newSubdivision;
    emit subdivisionChanged();
}

quint32 DarknetHelper::classes() const
{
    return m_classes;
}

void DarknetHelper::setClasses(quint32 newClasses)
{
    if (m_classes == newClasses)
        return;
    m_classes = newClasses;
    emit classesChanged();
}

quint32 DarknetHelper::type() const
{
    return m_type;
}

void DarknetHelper::setType(quint32 newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

quint32 DarknetHelper::width() const
{
    return m_width;
}

void DarknetHelper::setWidth(quint32 newWidth)
{
    if (m_width == newWidth)
        return;
    m_width = newWidth;
    emit widthChanged();
}

quint32 DarknetHelper::height() const
{
    return m_height;
}

void DarknetHelper::setHeight(quint32 newHeight)
{
    if (m_height == newHeight)
        return;
    m_height = newHeight;
    emit heightChanged();
}

bool DarknetHelper::init() const
{
    return m_init;
}

void DarknetHelper::setInit(bool newInit)
{
    if (m_init == newInit)
        return;
    m_init = newInit;
    emit initChanged();
}
