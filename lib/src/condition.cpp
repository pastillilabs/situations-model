#include "situations-model/condition.h"

namespace Model {

Condition::Condition(QObject* parent)
    : QObject(parent) {}

QJsonObject Condition::toJson(bool persistent) const {
    if(persistent) {
        return {
            {QLatin1String("uid"), mUid},
            {QLatin1String("payload"), mPayload},
            {QLatin1String("delay"), mDelay}
        };
    }
    else {
        return {};
    }
}

void Condition::fromJson(const QJsonObject& jsonObject, bool persistent) {
    if(persistent) {
        const QJsonValue uid = jsonObject.value(QLatin1String("uid"));
        const QJsonValue payload = jsonObject.value(QLatin1String("payload"));
        const QJsonValue delay = jsonObject.value(QLatin1String("delay"));

        if(!uid.isUndefined()) setUid(uid.toString());
        if(!payload.isUndefined()) setPayload(payload.toObject());
        if(!delay.isUndefined()) setDelay(delay.toInt());
    }
}

const QString& Condition::uid() const {
    return mUid;
}

void Condition::setUid(const QString& uid) {
    if(uid != mUid) {
        mUid = uid;
        emit uidChanged(uid);
    }
}

const QJsonObject& Condition::payload() const {
    return mPayload;
}

void Condition::setPayload(const QJsonObject& payload) {
    if(mPayload != payload) {
        mPayload = payload;
        emit payloadChanged(payload);
    }
}

int Condition::delay() const {
    return mDelay;
}

void Condition::setDelay(int delay) {
    if(delay != mDelay) {
        mDelay = delay;
        emit delayChanged(delay);
    }
}

Condition::ReadyState Condition::readyState() const {
    return mReadyState;
}

void Condition::setReadyState(ReadyState readyState) {
    if(readyState != mReadyState) {
        mReadyState = readyState;
        emit readyStateChanged(readyState);
    }
}

bool Condition::isRunning() const {
    return mRunning;
}

void Condition::setRunning(bool running) {
    if(running != mRunning) {
        mRunning = running;
        emit runningChanged(running);
    }
}

bool Condition::isActive() const {
    return mActive;
}

void Condition::setActive(bool active) {
    if(active != mActive) {
        mActive = active;
        emit activeChanged(active);
    }
}

} // namespace Model
