#include "situations-model/situation.h"

namespace Model {

Situation::Situation(QObject* parent)
    : QObject(parent)
    , mActionGroups(new ActionGroupList(this))
    , mConditionGroups(new ConditionGroupList(this)) {}

QJsonObject Situation::toJson(bool persistent) const {
    if(persistent) {
        return {
            {QLatin1String("uid"), mUid},
            {QLatin1String("name"), mName},
            {QLatin1String("icon"), mIcon},
            {QLatin1String("metaData"), mMetaData},
            {QLatin1String("manual"), mManual},
            {QLatin1String("timingStart"), mTimingStart.toString(Qt::DateFormat::ISODate)},
            {QLatin1String("timingDuration"), mTimingDuration.toString(Qt::DateFormat::ISODate)},
            {QLatin1String("actionGroups"), mActionGroups->toJson(persistent)},
            {QLatin1String("conditionGroups"), mConditionGroups->toJson(persistent)}
        };
    }
    else {
        return {
            {QLatin1String("uid"), mUid},
            {QLatin1String("proposal"), isProposal()},
            {QLatin1String("active"), isActive()}
        };
    }
}

void Situation::fromJson(const QJsonObject& jsonObject, bool persistent) {
    const QJsonValue actionGroups = jsonObject.value(QLatin1String("actionGroups"));
    const QJsonValue conditionGroups = jsonObject.value(QLatin1String("conditionGroups"));

    if(!actionGroups.isUndefined()) {
        this->actionGroups()->fromJson(actionGroups.toObject(), persistent);
    }
    if(!conditionGroups.isUndefined()) {
        this->conditionGroups()->fromJson(conditionGroups.toObject(), persistent);
    }

    if(persistent) {
        const QJsonValue uid = jsonObject.value(QLatin1String("uid"));
        const QJsonValue name = jsonObject.value(QLatin1String("name"));
        const QJsonValue icon = jsonObject.value(QLatin1String("icon"));
        const QJsonValue metaData = jsonObject.value(QLatin1String("metaData"));
        const QJsonValue manual = jsonObject.value(QLatin1String("manual"));
        const QJsonValue timingStart = jsonObject.value(QLatin1String("timingStart"));
        const QJsonValue timingDuration = jsonObject.value(QLatin1String("timingDuration"));

        if(!uid.isUndefined()) {
            setUid(uid.toString());
        }
        if(!name.isUndefined()) {
            setName(name.toString());
        }
        if(!icon.isUndefined()) {
            setIcon(icon.toString());
        }
        if(!metaData.isUndefined()) {
            setMetaData(metaData.toObject());
        }
        if(!manual.isUndefined()) {
            setManual(manual.toBool());
        }
        if(!timingStart.isUndefined()) {
            setTimingStart(QDateTime::fromString(timingStart.toString(), Qt::DateFormat::ISODate));
        }
        if(!timingDuration.isUndefined()) {
            setTimingDuration(QTime::fromString(timingDuration.toString(), Qt::DateFormat::ISODate));
        }
    }
    else {
        const QJsonValue proposal = jsonObject.value(QLatin1String("proposal"));
        const QJsonValue active = jsonObject.value(QLatin1String("active"));

        if(!proposal.isUndefined()) {
            setProposal(proposal.toBool());
        }
        if(!active.isUndefined()) {
            setActive(active.toBool());
        }
    }
}

void Situation::clone(const Situation& source, const QString& uid, const QString& name) {
    setUid(uid);
    setName(name);
    setIcon(source.icon());
    setMetaData(source.metaData());
    setManual(source.isManual());
    setTimingStart(source.timingStart());
    setTimingDuration(source.timingDuration());

    // Clone conditions & actions from source
    actionGroups()->clone(*source.actionGroups());
    conditionGroups()->clone(*source.conditionGroups());
}

ActionGroupList* Situation::actionGroups() const {
    return mActionGroups;
}

ConditionGroupList* Situation::conditionGroups() const {
    return mConditionGroups;
}

const QString& Situation::uid() const {
    return mUid;
}

void Situation::setUid(const QString& uid) {
    if(uid != mUid) {
        mUid = uid;
        emit uidChanged(uid);
    }
}

const QString& Situation::name() const {
    return mName;
}

void Situation::setName(const QString& name) {
    if(name != mName) {
        mName = name;
        emit nameChanged(name);
    }
}

const QString& Situation::icon() const {
    return mIcon;
}

void Situation::setIcon(const QString& icon) {
    if(icon != mIcon) {
        mIcon = icon;
        emit iconChanged(icon);
    }
}

const QJsonObject& Situation::metaData() const {
    return mMetaData;
}

void Situation::setMetaData(const QJsonObject& metaData) {
    if(metaData != mMetaData) {
        mMetaData = metaData;
        emit metaDataChanged(metaData);
    }
}

bool Situation::isManual() const {
    return mManual;
}

void Situation::setManual(bool manual) {
    if(manual != mManual) {
        mManual = manual;
        emit manualChanged(manual);
    }
}

const QDateTime& Situation::timingStart() const {
    return mTimingStart;
}

void Situation::setTimingStart(const QDateTime& timingStart) {
    if(timingStart != mTimingStart) {
        mTimingStart = timingStart;
        emit timingStartChanged(timingStart);
    }
}

const QTime& Situation::timingDuration() const {
    return mTimingDuration;
}

void Situation::setTimingDuration(const QTime& duration) {
    if(duration != mTimingDuration) {
        mTimingDuration = duration;
        emit timingDurationChanged(duration);
    }
}

bool Situation::isProposal() const {
    return mProposal;
}

void Situation::setProposal(bool proposal) {
    if(proposal != mProposal) {
        mProposal = proposal;
        emit proposalChanged(proposal);
    }
}

bool Situation::isActive() const {
    return mActive;
}

void Situation::setActive(bool active) {
    if(active != mActive) {
        mActive = active;
        emit activeChanged(active);
    }
}

} // namespace Model
