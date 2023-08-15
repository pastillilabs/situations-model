#include "model/situationlist.h"

#include <xylitol/util.h>

#include <QJsonArray>

namespace Model {

SituationList::SituationList(QObject* parent)
    : Xylitol::ListModel(parent) {
    connect(this, &SituationList::rowsInserted, this, [this] { emit countChanged(count()); });
    connect(this, &SituationList::rowsRemoved, this, [this] { emit countChanged(count()); });
    connect(this, &SituationList::modelReset, this, [this] { emit countChanged(count()); });
}

QJsonObject SituationList::toJson(bool persistent) const {
    QJsonArray situationArray;
    for(const Model::SituationList::Item& item : container()) {
        const Model::Situation* situation = item.value(Model::SituationList::RoleSituation).value<Model::Situation*>();
        situationArray.append(situation->toJson(persistent));
    }

    return {
        {QLatin1String("container"), situationArray}
    };
}

void SituationList::fromJson(const QJsonObject& jsonObject, bool persistent, const Initializer& initializer) {
    const QJsonArray container = jsonObject.value(QLatin1String("container")).toArray();

    for(const QJsonValue& situationValue : container) {
        if(persistent) {
            add([&](Model::Situation& situation) {
                initializer(situation);

                situation.fromJson(situationValue.toObject(), persistent);
            });
        }
        else {
            const QJsonValue uid = situationValue.toObject().value(QLatin1String("uid"));

            Model::Situation* situation = findByUid(uid.toString());
            if(situation) {
                situation->fromJson(situationValue.toObject(), persistent);
            }
        }
    }
}

void SituationList::add(const Initializer& initializer) {
    Situation* situation = new Situation(this);
    initializer(*situation);

    const int index(mContainer.size());
    beginInsertRows(QModelIndex(), index, index);
    mContainer.append({{RoleSituation, QVariant::fromValue(situation)}});
    endInsertRows();
}

void SituationList::remove(const QString& uid) {
    const int index = indexOfUid(uid);
    if(index >= 0) {
        beginRemoveRows(QModelIndex(), index, index);
        mContainer.takeAt(index).value(RoleSituation).value<Situation*>()->deleteLater();
        endRemoveRows();
    }
}

void SituationList::move(const QString& uid, int target) {
    const int index = indexOfUid(uid);
    if((index >= 0) && (index != target)) {
        xylitolMove(index, index, (index > target) ? target : (target + 1));
    }
}

void SituationList::reset() {
    beginResetModel();
    while(mContainer.count()) {
        mContainer.takeAt(0).value(RoleSituation).value<Situation*>()->deleteLater();
    }
    endResetModel();
}

int SituationList::count() const {
    return mContainer.count();
}

Model::Situation* SituationList::findByUid(const QString& uid) const {
    Situation* situation(nullptr);
    const int index = indexOfUid(uid);
    if(index >= 0) {
        situation = mContainer.at(index).value(RoleSituation).value<Situation*>();
    }

    return situation;
}

int SituationList::indexOfUid(const QString& uid) const {
    const auto it = std::find_if(std::cbegin(mContainer), std::cend(mContainer), [uid](const Item& item){
        return item.value(RoleSituation).value<Situation*>()->uid() == uid;
    });
    if(it != std::cend(mContainer)) {
        return (it - std::cbegin(mContainer));
    }

    return -1;
}

QString SituationList::uidByIndex(int index) const {
    if(index >= 0 && index < mContainer.count()) {
        return mContainer.at(index).value(RoleSituation).value<Situation*>()->uid();
    }

    return QString();
}

QHash<int, QByteArray> SituationList::roleNames() const {
    static const QHash<int, QByteArray> names{
        {RoleSituation, "situation"}
    };
    return names;
}

QHash<int, int> SituationList::roleTypes() const {
    static const QHash<int, int> types{
        {RoleSituation, qMetaTypeId<Situation*>()}
    };
    return types;
}

} // namespace Model
