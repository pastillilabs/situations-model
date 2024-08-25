#include "situations-model/platform.h"

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

const QString& Platform::suPath() const {
    return mSuPath;
}

void Platform::setSuPath(const QString& suPath) {
    if(suPath != mSuPath) {
        mSuPath = suPath;
        emit suPathChanged(suPath);
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
