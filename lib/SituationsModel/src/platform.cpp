#include "SituationsModel/platform.h"

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

Platform::CallState Platform::callState() const {
    return mCallState;
}

void Platform::setCallState(CallState callState) {
    if(callState != mCallState) {
        mCallState = callState;
        emit callStateChanged(callState);
    }
}

const QString& Platform::locale() const {
    return mLocale;
}

void Platform::setLocale(const QString& locale) {
    if(locale != mLocale) {
        mLocale = locale;
        emit localeChanged(locale);
    }
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
