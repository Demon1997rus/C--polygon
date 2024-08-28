#pragma once

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>

class Path : public QStringList {
public:
    template <class... Args>
    Path(Args &&... args) : QStringList({std::forward<Args>(args)...})
    {
    }

public:
    static Path fromString(const QString &str, char separator = '.')
    {
        return str.split(separator);
    }

    inline friend QDebug operator<<(QDebug debug, const Path &path)
    {
        return QtPrivate::printSequentialContainer(debug, "Path", path);
    }
};

class JsonWrapper : public QJsonObject {
public:
    template <class... Args>
    JsonWrapper(Args &&... args) : QJsonObject({std::forward<Args>(args)...})
    {
    }

    QJsonValue findByPath(const Path &path) const;
    QJsonValue findByPath(const Path &path, int indexPath) const;

private:
    QJsonValue findByPath(const Path &path, int indexPath, const QJsonValue &value) const;
};
