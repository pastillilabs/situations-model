#include "model/platform.h"

namespace Model {

Platform::Platform(QObject* parent)
    : QObject(parent)
    , mContacts(new ContactList(this))
    , mPackages(new PackageList(this)) {}

ContactList* Platform::contacts() const {
    return mContacts;
}

PackageList* Platform::packages() const {
    return mPackages;
}

bool Platform::isRooted() const {
    return mRooted;
}

void Platform::setRooted(bool rooted) {
    if(rooted != mRooted) {
        mRooted = rooted;
        emit rootedChanged(rooted);
    }
}

int Platform::version() const {
    return mVersion;
}

void Platform::setVersion(int version) {
    if(version != mVersion) {
        mVersion = version;
        emit versionChanged(version);
    }
}

} // namespace Model
