#include "SituationsModel/action.h"

namespace Model {

Action::Action(QObject* parent)
    : QObject(parent) {}

QJsonObject Action::toJson(bool persistent) const {
    if(persistent) {
        return {
            {QLatin1String("uid"), mUid},
            {QLatin1String("payload"), mPayload},
            {QLatin1String("settings"), mSettings}
        };
    }
    else {
        return {};
    }
}

void Action::fromJson(const QJsonObject& jsonObject, bool persistent) {
    if(persistent) {
        const QJsonValue uid = jsonObject.value(QLatin1String("uid"));
        const QJsonValue payload = jsonObject.value(QLatin1String("payload"));
        const QJsonValue settings = jsonObject.value(QLatin1String("settings"));

        if(!uid.isUndefined()) {
            setUid(uid.toString());
        }
        if(!payload.isUndefined()) {
            setPayload(payload.toObject());
        }
        if(!settings.isUndefined()) {
            setSettings(settings.toObject());
        }
    }
}

void Action::clone(const Action& source) {
    setUid(source.uid());
    setPayload(source.payload());
    setSettings(source.settings());
}

const QString& Action::uid() const {
    return mUid;
}

void Action::setUid(const QString& uid) {
    if(uid != mUid) {
        mUid = uid;
        emit uidChanged(uid);
    }
}

const QJsonObject& Action::payload() const {
    return mPayload;
}

void Action::setPayload(const QJsonObject& payload) {
    if(mPayload != payload) {
        mPayload = payload;
        emit payloadChanged(payload);
    }
}

const QJsonObject& Action::settings() const {
    return mSettings;
}

void Action::setSettings(const QJsonObject& settings) {
    if(mSettings != settings) {
        mSettings = settings;
        emit settingsChanged(settings);
    }
}

Action::ReadyState Action::readyState() const {
    return mReadyState;
}

void Action::setReadyState(ReadyState readyState) {
    if(readyState != mReadyState) {
        mReadyState = readyState;
        emit readyStateChanged(readyState);
    }
}

Action::RunningState Action::runningState() const {
    return mRunningState;
}

void Action::setRunningState(RunningState runningState) {
    if(runningState != mRunningState) {
        mRunningState = runningState;
        emit runningStateChanged(runningState);
    }
}

Action::ActiveState Action::activeState() const {
    return mActiveState;
}

void Action::setActiveState(ActiveState activeState) {
    if(activeState != mActiveState) {
        mActiveState = activeState;
        emit activeStateChanged(activeState);
    }
}

} // namespace Model
