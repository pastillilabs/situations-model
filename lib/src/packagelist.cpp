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

void PackageList::reset(const Container& container) {
    // Find items to be removed from mContainer
    Container remove;
    for(const Item& item : std::as_const(mContainer)) {
        const QString id = item.value(RoleId).toString();

        // Is id in new container?
        const auto it = std::find_if(std::cbegin(container), std::cend(container), [id](const Item& item) {
            return item.value(RoleId).toString() == id;
        });
        // Id not found -> to be removed
        if(it == std::cend(container)) {
            remove.append(item);
        }
    }

    // Remove items
    while(remove.size()) {
        const Item item = remove.takeFirst();
        const int index = indexOf(item.value(RoleId).toString());

        beginRemoveRows(QModelIndex(), index, index);
        mContainer.removeAt(index);
        endRemoveRows();
    }

    // Update rest
    for(const Item& item : std::as_const(container)) {
        update(item);
    }
}

void PackageList::update(const Item& item) {
    const int currentIndex = indexOf(item.value(RoleId).toString());
    if(currentIndex >= 0) {
        QVector<int> roles;

        const Item& old = mContainer.at(currentIndex);
        if(old.value(RoleId).toString() != item.value(RoleId).toString()) {
            roles.append(Role::RoleId);
        }
        if(old.value(RoleName).toString() != item.value(RoleName).toString()) {
            roles.append(Role::RoleName);
        }

        if(!roles.isEmpty()) {
            mContainer.replace(currentIndex, item);

            const QModelIndex modelIndex = this->index(currentIndex);
            emit dataChanged(modelIndex, modelIndex, roles);
        }
    }
    else {
        const int index = mContainer.count();

        beginInsertRows(QModelIndex(), index, index);
        mContainer.append(item);
        endInsertRows();
    }
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
