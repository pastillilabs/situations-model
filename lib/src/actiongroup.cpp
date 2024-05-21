#include "situations-model/actiongroup.h"

#include <QJsonArray>

namespace Model {

ActionGroup::ActionGroup(QObject* parent)
    : Xylitol::ListModel(parent) {
    connect(this, &ActionGroup::rowsInserted, this, [this] { emit countChanged(count()); });
    connect(this, &ActionGroup::rowsRemoved, this, [this] { emit countChanged(count()); });
    connect(this, &ActionGroup::modelReset, this, [this] { emit countChanged(count()); });
}

QJsonObject ActionGroup::toJson(bool persistent) const {
    QJsonArray actionArray;
    for(const Model::ActionGroup::Item& item : container()) {
        const Model::Action* action = item.value(Model::ActionGroup::RoleAction).value<Model::Action*>();

        if(action->readyState() != Action::ReadyState::ReadyStateAdding) {
            actionArray.append(action->toJson(persistent));
        }
    }

    return {
        {QLatin1String("name"), mName},
        {QLatin1String("container"), actionArray}
    };
}

void ActionGroup::fromJson(const QJsonObject& jsonObject, bool persistent) {
    const QJsonArray container = jsonObject.value(QLatin1String("container")).toArray();

    for(const QJsonValue& actionValue : container) {
        if(persistent) {
            add([&](Model::Action& action) {
                action.fromJson(actionValue.toObject(), persistent);
            });
        }
        else {
            const QJsonValue uid = actionValue.toObject().value(QLatin1String("uid"));

            Model::Action* action = findByUid(uid.toString());
            if(action) {
                action->fromJson(actionValue.toObject(), persistent);
            }
        }
    }
}

const QString& ActionGroup::name() const {
    return mName;
}

void ActionGroup::setName(const QString& name) {
    if(name != mName) {
        mName = name;
        emit nameChanged(name);
    }
}

int ActionGroup::priority() const {
    return mPriority;
}

void ActionGroup::setPriority(int priority) {
    if(priority != mPriority) {
        mPriority = priority;
        emit priorityChanged(priority);
    }
}

int ActionGroup::count() const {
    return mContainer.count();
}

void ActionGroup::add(const std::function<void(Action& action)>& initializer) {
    Action* action = new Action(this);
    initializer(*action);

    const int index(mContainer.size());
    beginInsertRows(QModelIndex(), index, index);
    mContainer.append({{RoleAction, QVariant::fromValue(action)}});
    endInsertRows();
}

void ActionGroup::remove(const QString& uid) {
    const int index = indexOfUid(uid);
    if(index >= 0) {
        beginRemoveRows(QModelIndex(), index, index);
        mContainer.takeAt(index).value(RoleAction).value<Action*>()->deleteLater();
        endRemoveRows();
    }
}

Model::Action* ActionGroup::findByUid(const QString& uid) const {
    Action* action(nullptr);
    const int index = indexOfUid(uid);
    if(index >= 0) {
        action = mContainer.at(index).value(RoleAction).value<Action*>();
    }

    return action;
}

int ActionGroup::indexOfUid(const QString& uid) const {
    const auto it = std::find_if(std::cbegin(mContainer), std::cend(mContainer), [uid](const Item& item){
        return item.value(RoleAction).value<Action*>()->uid() == uid;
    });
    if(it != std::cend(mContainer)) {
        return (it - std::cbegin(mContainer));
    }

    return -1;
}

int ActionGroup::readyCount() const {
    int count = 0;
    for(const Item& item : mContainer) {
        if(item.value(RoleAction).value<Action*>()->readyState() != Model::Action::ReadyState::ReadyStateAdding) {
            ++count;
        }
    }

    return count;
}

QHash<int, QByteArray> ActionGroup::roleNames() const {
    static const QHash<int, QByteArray> names{
        {RoleAction, "action"}
    };
    return names;
}

QHash<int, int> ActionGroup::roleTypes() const {
    static const QHash<int, int> types{
        {RoleAction, qMetaTypeId<Action*>()}
    };
    return types;
}

} // namespace Model
