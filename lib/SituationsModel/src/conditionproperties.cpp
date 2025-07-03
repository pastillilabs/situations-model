#include "SituationsModel/conditionproperties.h"

#include <Xylitol/util.h>

namespace Model {

ConditionProperties::ConditionProperties() {}

bool ConditionProperties::operator==(const ConditionProperties& other) const {
    return Xylitol::equals(this, reinterpret_cast<const void*>(&other), staticMetaObject);
}

bool ConditionProperties::operator!=(const ConditionProperties& other) const {
    return !Xylitol::equals(this, reinterpret_cast<const void*>(&other), staticMetaObject);
}

bool ConditionProperties::operator<([[maybe_unused]] const ConditionProperties& other) const {
    return false;
}

const QStringList& ConditionProperties::permissions() const {
    return mPermissions;
}

void ConditionProperties::setPermissions(const QStringList& permissions) {
    mPermissions = permissions;
}

const QStringList& ConditionProperties::extraPermissions() const {
    return mExtraPermissions;
}

void ConditionProperties::setExtraPermissions(const QStringList& extraPermissions) {
    mExtraPermissions = extraPermissions;
}

int ConditionProperties::maxCount() const {
    return mMaxCount;
}

void ConditionProperties::setMaxCount(int maxCount) {
    mMaxCount = maxCount;
}

int ConditionProperties::priority() const {
    return mPriority;
}

void ConditionProperties::setPriority(int priority) {
    mPriority = priority;
}

} // namespace Model
