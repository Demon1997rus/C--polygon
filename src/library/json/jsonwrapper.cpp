#include "jsonwrapper.h"

QJsonValue JsonWrapper::findByPath(const Path &path) const
{
    return findByPath(path, 0);
}

QJsonValue JsonWrapper::findByPath(const Path &path, int indexPath) const
{
    return findByPath(path, indexPath, *this);
}

QJsonValue JsonWrapper::findByPath(const Path &path, int indexPath,
                                   const QJsonValue &value) const
{
    if (indexPath >= path.size()) {
        return QJsonValue();
    }

    const QString &key = path.at(indexPath);
    if (value.isObject()) {
        QJsonObject object = value.toObject();
        auto it = object.find(key);
        if (it == object.end()) {
            return QJsonValue();
        }
        if (indexPath == path.size() - 1) {
            return *it;
        }
        return findByPath(path, indexPath + 1, *it);
    } else if (value.isArray()) {
        bool ok;
        int index = key.toInt(&ok);
        if (ok) {
            QJsonArray array = value.toArray();
            if (index >= array.size()) {
                return QJsonValue();
            }

            if (indexPath == path.size() - 1) {
                return array.at(index);
            }
            return findByPath(path, indexPath + 1, array.at(index));
        } else {
            return QJsonValue();
        }
    } else {
        return QJsonValue();
    }
}
