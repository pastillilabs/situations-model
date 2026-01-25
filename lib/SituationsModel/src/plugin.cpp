#include "SituationsModel/plugin.h"

namespace Model {

Plugin::Plugin(QObject* parent)
    : QObject(parent) {}

Plugin::Plugin(const QString& name, Category category, QObject* parent)
    : QObject(parent)
    , mName(name)
    , mCategory(category) {}

const QString& Plugin::name() const {
    return mName;
}

QObject* Plugin::model() const {
    return nullptr;
}

bool Plugin::isActionRunning() const {
    return mActionRunning;
}

void Plugin::setActionRunning(bool actionRunning) {
    if(actionRunning != mActionRunning) {
        mActionRunning = actionRunning;
        emit actionRunningChanged(actionRunning);
    }
}

bool Plugin::isConditionRunning() const {
    return mConditionRunning;
}

void Plugin::setConditionRunning(bool conditionRunning) {
    if(conditionRunning != mConditionRunning) {
        mConditionRunning = conditionRunning;
        emit conditionRunningChanged(conditionRunning);
    }
}

const QJsonObject& Plugin::stash() const {
    return mStash;
}

void Plugin::setStash(const QJsonObject& stash) {
    if(stash != mStash) {
        mStash = stash;
        emit stashChanged(stash);
    }
}

Plugin::Category Plugin::category() const {
    return mCategory;
}

const ActionProperties& Plugin::actionProperties() const {
    return mActionProperties;
}

const ConditionProperties& Plugin::conditionProperties() const {
    return mConditionProperties;
}

ActionProperties& Plugin::actionProperties() {
    return mActionProperties;
}

ConditionProperties& Plugin::conditionProperties() {
    return mConditionProperties;
}

bool Plugin::isController() const {
    return mController;
}

void Plugin::setController(bool controller) {
    if(controller != mController) {
        mController = controller;
        emit controllerChanged(controller);
    }
}

void Plugin::qmlRegisterTypes() const {}

QJsonObject Plugin::toJson(bool persistent) const {
    if(persistent) {
        return {};
    }
    else {
        return {
            {QLatin1String("actionStash"), mStash}
        };
    }
}

void Plugin::fromJson(const QJsonObject& jsonObject, [[maybe_unused]] bool persistent) {
    if(!persistent) {
        const QJsonValue stash = jsonObject.value(QLatin1String("stash"));

        if(!stash.isUndefined()) {
            setStash(stash.toObject());
        }
    }
}

QJsonArray Plugin::defaults(const QJsonArray& /*metaData*/) const {
    return {};
}

QJsonObject Plugin::systemPayload() const {
    return {};
}

void Plugin::starting(const Action& /*action*/) {}

void Plugin::started(const Action& /*action*/) {}

void Plugin::stopping(const Action& /*action*/) {}

void Plugin::stopped(const Action& /*action*/) {}

void Plugin::execute(const QJsonObject& /*payload*/) {}

void Plugin::evaluate(const QVector<Condition*>& /*conditions*/) {}

} // namespace Model
