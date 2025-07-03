#include "SituationsModel/actionproperties.h"

#include <Xylitol/util.h>

namespace Model {

ActionProperties::ActionProperties() {}

bool ActionProperties::operator==(const ActionProperties& other) const {
    return Xylitol::equals(this, reinterpret_cast<const void*>(&other), staticMetaObject);
}

bool ActionProperties::operator!=(const ActionProperties& other) const {
    return !Xylitol::equals(this, reinterpret_cast<const void*>(&other), staticMetaObject);
}

bool ActionProperties::operator<([[maybe_unused]] const ActionProperties& other) const {
    return false;
}

const QStringList& ActionProperties::permissions() const {
    return mPermissions;
}

void ActionProperties::setPermissions(const QStringList& permissions) {
    mPermissions = permissions;
}

const QStringList& ActionProperties::extraPermissions() const {
    return mExtraPermissions;
}

void ActionProperties::setExtraPermissions(const QStringList& extraPermissions) {
    mExtraPermissions = extraPermissions;
}

bool ActionProperties::isCallBlocker() const {
    return mCallBlocker;
}

void ActionProperties::setCallBlocker(bool callBlocker) {
    mCallBlocker = callBlocker;
}

bool ActionProperties::isEnabler() const {
    return mEnabler;
}

void ActionProperties::setEnabler(bool enabler) {
    mEnabler = enabler;
}

bool ActionProperties::isSequenceable() const {
    return mSequenceable;
}

void ActionProperties::setSequenceable(bool sequenceable) {
    mSequenceable = sequenceable;
}

int ActionProperties::delay() const {
    return mDelay;
}

void ActionProperties::setDelay(int delay) {
    mDelay = delay;
}

int ActionProperties::maxCount() const {
    return mMaxCount;
}

void ActionProperties::setMaxCount(int maxCount) {
    mMaxCount = maxCount;
}

int ActionProperties::priority() const {
    return mPriority;
}

void ActionProperties::setPriority(int priority) {
    mPriority = priority;
}

} // namespace Model
