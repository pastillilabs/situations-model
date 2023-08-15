#include "model/contactlist.h"

#include <QJsonObject>

namespace Model {

ContactList::ContactList(QObject* parent)
    : Xylitol::ListModel(parent) {}

bool ContactList::isUpdating() const {
    return mUpdating;
}

void ContactList::setUpdating(bool updating) {
    if(updating != mUpdating) {
        mUpdating = updating;
        emit updatingChanged(updating);
    }
}

void ContactList::reset(const QVector<Item>& contacts) {
    beginResetModel();
    mContainer = contacts;
    endResetModel();
}

int ContactList::indexOf(const QString& id) const {
    for(int i = 0; i < mContainer.count(); ++i) {
        if(mContainer.at(i).value(RoleId).toString() == id) {
            return i;
        }
    }

    return -1;
}

QString ContactList::idByIndex(int index) const {
    if(index >= 0 && index < mContainer.count()) {
        return mContainer.at(index).value(RoleId).toString();
    }

    return QString();
}

QString ContactList::nameByIndex(int index) const {
    if(index >= 0 && index < mContainer.count()) {
        return mContainer.at(index).value(RoleName).toString();
    }

    return QString();
}

QStringList ContactList::numbersByIndex(int index) const {
    if(index >= 0 && index < mContainer.count()) {
        return mContainer.at(index).value(RoleNumbers).value<QStringList>();
    }

    return QStringList();
}

QHash<int, QByteArray> ContactList::roleNames() const {
    static const QHash<int, QByteArray> names{
        {RoleId, "id"},
        {RoleName, "name"},
        {RoleNumbers, "numbers"}
    };
    return names;
}

QHash<int, int> ContactList::roleTypes() const {
    static const QHash<int, int> types{
        {RoleId, qMetaTypeId<QString>()},
        {RoleName, qMetaTypeId<QString>()},
        {RoleNumbers, qMetaTypeId<QStringList>()}
    };
    return types;
}

} // namespace Model
