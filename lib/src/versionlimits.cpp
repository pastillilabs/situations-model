#include "situations-model/versionlimits.h"

#include <xylitol/util.h>

namespace Model {

VersionLimits::VersionLimits(int min, int max)
    : mMin(min)
    , mMax(max) {}

VersionLimits::VersionLimits(int min, int max, int rootMin, int rootMax)
    : mMin(min)
    , mMax(max)
    , mRootMin(rootMin)
    , mRootMax(rootMax) {}

bool VersionLimits::operator==(const VersionLimits& other) const {
    return Xylitol::equals(this, reinterpret_cast<const void*>(&other), staticMetaObject);
}

bool VersionLimits::operator!=(const VersionLimits& other) const {
    return !Xylitol::equals(this, reinterpret_cast<const void*>(&other), staticMetaObject);
}

bool VersionLimits::operator<([[maybe_unused]] const VersionLimits& other) const {
    return false;
}

int VersionLimits::min() const {
    return mMin;
}

void VersionLimits::setMin(int min) {
    mMin = min;
}

int VersionLimits::max() const {
    return mMax;
}

void VersionLimits::setMax(int max) {
    mMax = max;
}

int VersionLimits::rootMin() const {
    return mRootMin;
}

void VersionLimits::setRootMin(int rootMin) {
    mRootMin = rootMin;
}

int VersionLimits::rootMax() const {
    return mRootMax;
}

void VersionLimits::setRootMax(int rootMax) {
    mRootMax = rootMax;
}

} // namespace Model
