#include "situations-model/packagelist.h"

#include <QJsonObject>

namespace Model {

PackageList::PackageList(QObject* parent)
    : Xylitol::ListModel(parent) {}

bool PackageList::isUpdating() const {
    return mUpdating;
}

void PackageList::setUpdating(bool updating) {
    if(updating != mUpdating) {
        mUpdating = updating;
        emit updatingChanged(updating);
    }
}

void PackageList::reset(const QVector<Item>& packages) {
    beginResetModel();
    mContainer = packages;
    endResetModel();
}

int PackageList::indexOf(const QString& id) const {
    for(int i = 0; i < mContainer.count(); ++i) {
        if(mContainer.at(i).value(RoleId).toString() == id) {
            return i;
        }
    }

    return -1;
}

QString PackageList::idByIndex(int index) const {
    if(index >= 0 && index < mContainer.count()) {
        return mContainer.at(index).value(RoleId).toString();
    }

    return QString();
}

QString PackageList::nameByIndex(int index) const {
    if(index >= 0 && index < mContainer.count()) {
        return mContainer.at(index).value(RoleName).toString();
    }

    return QString();
}

QHash<int, QByteArray> PackageList::roleNames() const {
    static const QHash<int, QByteArray> names{
        {RoleId, "id"},
        {RoleName, "name"}
    };
    return names;
}

QHash<int, int> PackageList::roleTypes() const {
    static const QHash<int, int> types{
        {RoleId, qMetaTypeId<QString>()},
        {RoleName, qMetaTypeId<QString>()}
    };
    return types;
}

} // namespace Model
