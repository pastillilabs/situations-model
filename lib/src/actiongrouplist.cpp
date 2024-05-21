#include "situations-model/actiongrouplist.h"

#include <xylitol/util.h>

#include <QJsonArray>

namespace Model {

ActionGroupList::ActionGroupList(QObject* parent)
    : Xylitol::ListModel(parent) {}

QJsonObject ActionGroupList::toJson(bool persistent) const {
    QJsonArray actionGroupArray;
    for(const Model::ActionGroupList::Item& item : container()) {
        const Model::ActionGroup* actionGroup = item.value(Model::ActionGroupList::RoleGroup).value<Model::ActionGroup*>();
        actionGroupArray.append(actionGroup->toJson(persistent));
    }

    return {
        {QLatin1String("container"), actionGroupArray}
    };
}

void ActionGroupList::fromJson(const QJsonObject& jsonObject, bool persistent) {
    const QJsonArray container = jsonObject.value(QLatin1String("container")).toArray();

    for(const QJsonValue& actionGroupValue : container) {
        const QJsonValue name = actionGroupValue.toObject().value(QLatin1String("name"));

        Model::ActionGroup* actionGroup = findByName(name.toString());
        if(actionGroup) {
            actionGroup->fromJson(actionGroupValue.toObject(), persistent);
        }
    }
}

void ActionGroupList::add(const QString& name, int priority) {
    const int currentIndex = indexOfName(name);
    if(currentIndex < 0) {
        ActionGroup* actionGroup = new ActionGroup(this);
        actionGroup->setName(name);
        actionGroup->setPriority(priority);

        // Find index based on priority
        int index = 0;
        const ActionGroupList::Container& container = mContainer;
        for(const ActionGroupList::Item& item : container) {
            const ActionGroup* group = item.value(ActionGroupList::RoleGroup).value<ActionGroup*>();
            if(priority < group->priority()) {
                break;
            }
            ++index;
        }

        beginInsertRows(QModelIndex(), index, index);
        mContainer.insert(index, {{RoleGroup, QVariant::fromValue(actionGroup)}});
        endInsertRows();
    }
}

void ActionGroupList::remove(const QString& name) {
    const int index = indexOfName(name);
    if(index >= 0) {
        beginRemoveRows(QModelIndex(), index, index);
        mContainer.takeAt(index).value(RoleGroup).value<ActionGroup*>()->deleteLater();
        endRemoveRows();
    }
}

int ActionGroupList::indexOfName(const QString& name) const {
    const auto it = std::find_if(std::cbegin(mContainer), std::cend(mContainer), [name](const Item& item){
        return item.value(RoleGroup).value<ActionGroup*>()->name() == name;
    });
    if(it != std::cend(mContainer)) {
        return (it - std::cbegin(mContainer));
    }

    return -1;
}

ActionGroup* ActionGroupList::findByName(const QString& name) const {
    ActionGroup* actionGroup(nullptr);
    const int index = indexOfName(name);
    if(index >= 0) {
        actionGroup = mContainer.at(index).value(RoleGroup).value<ActionGroup*>();
    }

    return actionGroup;
}

QHash<int, QByteArray> ActionGroupList::roleNames() const {
    static const QHash<int, QByteArray> names{
        {RoleGroup, "group"}
    };
    return names;
}

QHash<int, int> ActionGroupList::roleTypes() const {
    static const QHash<int, int> types{
        {RoleGroup, qMetaTypeId<ActionGroup*>()}
    };
    return types;
}

} // namespace Model
