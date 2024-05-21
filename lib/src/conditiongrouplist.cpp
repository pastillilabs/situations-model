#include "situations-model/conditiongrouplist.h"

#include <xylitol/util.h>

#include <QJsonArray>

namespace Model {

ConditionGroupList::ConditionGroupList(QObject* parent)
    : Xylitol::ListModel(parent) {}

QJsonObject ConditionGroupList::toJson(bool persistent) const {
    QJsonArray conditionGroupArray;
    for(const Model::ConditionGroupList::Item& item : container()) {
        const Model::ConditionGroup* conditionGroup = item.value(Model::ConditionGroupList::RoleGroup).value<Model::ConditionGroup*>();
        conditionGroupArray.append(conditionGroup->toJson(persistent));
    }

    return {
        {QLatin1String("container"), conditionGroupArray}
    };
}

void ConditionGroupList::fromJson(const QJsonObject& jsonObject, bool persistent) {
    const QJsonArray container = jsonObject.value(QLatin1String("container")).toArray();

    for(const QJsonValue& conditionGroupValue : container) {
        const QJsonValue name = conditionGroupValue.toObject().value(QLatin1String("name"));

        Model::ConditionGroup* conditionGroup = findByName(name.toString());
        if(conditionGroup) {
            conditionGroup->fromJson(conditionGroupValue.toObject(), persistent);
        }
    }
}

void ConditionGroupList::add(const QString& name, int priority) {
    const int currentIndex = indexOfName(name);
    if(currentIndex < 0) {
        ConditionGroup* conditionGroup = new ConditionGroup(this);
        conditionGroup->setName(name);
        conditionGroup->setPriority(priority);

        // Find index based on priority
        int index = 0;
        const ConditionGroupList::Container& container = mContainer;
        for(const ConditionGroupList::Item& item : container) {
            const ConditionGroup* group = item.value(ConditionGroupList::RoleGroup).value<ConditionGroup*>();
            if(priority < group->priority()) {
                break;
            }
            ++index;
        }

        beginInsertRows(QModelIndex(), index, index);
        mContainer.insert(index, {{RoleGroup, QVariant::fromValue(conditionGroup)}});
        endInsertRows();
    }
}

void ConditionGroupList::remove(const QString& name) {
    const int index = indexOfName(name);
    if(index >= 0) {
        beginRemoveRows(QModelIndex(), index, index);
        mContainer.takeAt(index).value(RoleGroup).value<ConditionGroup*>()->deleteLater();
        endRemoveRows();
    }
}

int ConditionGroupList::indexOfName(const QString& name) const {
    const auto it = std::find_if(std::cbegin(mContainer), std::cend(mContainer), [name](const Item& item){
        return item.value(RoleGroup).value<ConditionGroup*>()->name() == name;
    });
    if(it != std::cend(mContainer)) {
        return (it - std::cbegin(mContainer));
    }

    return -1;
}

ConditionGroup* ConditionGroupList::findByName(const QString& name) const {
    ConditionGroup* conditionGroup(nullptr);
    const int index = indexOfName(name);
    if(index >= 0) {
        conditionGroup = mContainer.at(index).value(RoleGroup).value<ConditionGroup*>();
    }

    return conditionGroup;
}

QHash<int, QByteArray> ConditionGroupList::roleNames() const {
    static const QHash<int, QByteArray> names{
        {RoleGroup, "group"}
    };
    return names;
}

QHash<int, int> ConditionGroupList::roleTypes() const {
    static const QHash<int, int> types{
        {RoleGroup, qMetaTypeId<ConditionGroup*>()}
    };
    return types;
}

} // namespace Model
