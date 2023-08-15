#include "model/conditiongroup.h"

#include <QJsonArray>

namespace Model {

ConditionGroup::ConditionGroup(QObject* parent)
    : Xylitol::ListModel(parent) {
    connect(this, &ConditionGroup::rowsInserted, this, [this] { emit countChanged(count()); });
    connect(this, &ConditionGroup::rowsRemoved, this, [this] { emit countChanged(count()); });
    connect(this, &ConditionGroup::modelReset, this, [this] { emit countChanged(count()); });
}

QJsonObject ConditionGroup::toJson(bool persistent) const {
    QJsonArray conditionArray;
    for(const Model::ConditionGroup::Item& item : container()) {
        const Model::Condition* condition = item.value(Model::ConditionGroup::RoleCondition).value<Model::Condition*>();

        if(condition->readyState() != Condition::ReadyState::ReadyStateAdding) {
            conditionArray.append(condition->toJson(persistent));
        }
    }

    if(persistent) {
        return {
            {QLatin1String("name"), mName},
            {QLatin1String("negative"), mNegative},
            {QLatin1String("container"), conditionArray}
        };
    }
    else {
        return {
            {QLatin1String("name"), mName},
            {QLatin1String("container"), conditionArray}
        };
    }
}

void ConditionGroup::fromJson(const QJsonObject& jsonObject, bool persistent) {
    const QJsonArray container = jsonObject.value(QLatin1String("container")).toArray();

    for(const QJsonValue& conditionValue : container) {
        if(persistent) {
            add([&](Model::Condition& condition) {
                condition.fromJson(conditionValue.toObject(), persistent);
            });
        }
        else {
            const QJsonValue uid = conditionValue.toObject().value(QLatin1String("uid"));

            Model::Condition* condition = findByUid(uid.toString());
            if(condition) {
                condition->fromJson(conditionValue.toObject(), persistent);
            }
        }
    }

    if(persistent) {
        const QJsonValue negative = jsonObject.value(QLatin1String("negative"));

        if(!negative.isUndefined()) setNegative(negative.toBool());
    }
}

const QString& ConditionGroup::name() const {
    return mName;
}

void ConditionGroup::setName(const QString& name) {
    if(name != mName) {
        mName = name;
        emit nameChanged(name);
    }
}

int ConditionGroup::priority() const {
    return mPriority;
}

void ConditionGroup::setPriority(int priority) {
    if(priority != mPriority) {
        mPriority = priority;
        emit priorityChanged(priority);
    }
}

bool ConditionGroup::isActive() const {
    return mActive;
}

void ConditionGroup::setActive(bool active) {
    if(active != mActive) {
        mActive = active;
        emit activeChanged(active);
    }
}

bool ConditionGroup::isNegative() const {
    return mNegative;
}

void ConditionGroup::setNegative(bool negative) {
    if(negative != mNegative) {
        mNegative = negative;
        emit negativeChanged(negative);
    }
}

int ConditionGroup::count() const {
    return mContainer.count();
}

void ConditionGroup::add(const std::function<void(Condition& condition)>& initializer) {
    Condition* condition = new Condition(this);
    initializer(*condition);

    const int index(mContainer.size());
    beginInsertRows(QModelIndex(), index, index);
    mContainer.append({{RoleCondition, QVariant::fromValue(condition)}});
    endInsertRows();
}

void ConditionGroup::remove(const QString& uid) {
    const int index = indexOfUid(uid);
    if(index >= 0) {
        beginRemoveRows(QModelIndex(), index, index);
        mContainer.takeAt(index).value(RoleCondition).value<Condition*>()->deleteLater();
        endRemoveRows();
    }
}

Model::Condition* ConditionGroup::findByUid(const QString& uid) const {
    Condition* condition(nullptr);
    const int index = indexOfUid(uid);
    if(index >= 0) {
        condition = mContainer.at(index).value(RoleCondition).value<Condition*>();
    }

    return condition;
}

int ConditionGroup::indexOfUid(const QString& uid) const {
    const auto it = std::find_if(std::cbegin(mContainer), std::cend(mContainer), [uid](const Item& item){
        return item.value(RoleCondition).value<Condition*>()->uid() == uid;
    });
    if(it != std::cend(mContainer)) {
        return (it - std::cbegin(mContainer));
    }

    return -1;
}

int ConditionGroup::readyCount() const {
    int count = 0;
    for(const Item& item : mContainer) {
        if(item.value(RoleCondition).value<Condition*>()->readyState() != Model::Condition::ReadyState::ReadyStateAdding) {
            ++count;
        }
    }

    return count;
}

QHash<int, QByteArray> ConditionGroup::roleNames() const {
    static const QHash<int, QByteArray> names{
        {RoleCondition, "condition"}
    };
    return names;
}

QHash<int, int> ConditionGroup::roleTypes() const {
    static const QHash<int, int> types{
        {RoleCondition, qMetaTypeId<Condition*>()}
    };
    return types;
}

} // namespace Model
