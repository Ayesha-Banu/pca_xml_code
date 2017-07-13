#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QDebug>
#include <QtCore/QtCore>
#include <QtXml/QtXml>
#include <QSettings>

int createXml(QString &fileName, QMap<QString, QVariant> &map);
int readXml(QString &fileName, QHash< QString,QVariant> &hash);
int writeXmlElement(QString &fileName, QString &element, QString &value);
int readXmlElement(QString &fileName,  QString &element, QString &value);
bool readSettingsXml(QIODevice &device, QMap<QString, QVariant> &map);
bool writeSettingsXml(QIODevice &device, const QMap<QString, QVariant> &map);
static const QString rootName = "PCA";


class XmlNode : public QObject
{
public:
    QString tagName, subtext;

    XmlNode(const QString &name, const QString &text = QString(), QObject *parent = 0) :
        QObject(parent),
        tagName(name),
        subtext(text)
    {
    }

    QString fullPath() const
    {
        const XmlNode *cur = this;
        QString path = tagName;

        while((cur = (const XmlNode *) cur->parent()) != 0)
            path.prepend(cur->tagName + "//");

        return path.mid(rootName.size() + 1); // remove root node & trailing slash
    }
};
#endif // MAINWINDOW_H
