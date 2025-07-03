#include "SituationsModel/settings.h"

#include <QJsonObject>

namespace Model {

Settings::Settings(QObject* parent)
    : QObject(parent) {}

QJsonObject Settings::toJson(bool persistent) const {
    if(persistent) {
        return {
            {QLatin1String("enabled"), mEnabled},
            {QLatin1String("logging"), mLogging},
            {QLatin1String("notifications"), mNotifications},
            {QLatin1String("theme"), mTheme},
            {QLatin1String("locale"), mLocale}
        };
    }
    else {
        return {};
    }
}

void Settings::fromJson(const QJsonObject& jsonObject, bool persistent) {
    if(persistent) {
        const QJsonValue enabled = jsonObject.value(QLatin1String("enabled"));
        const QJsonValue logging = jsonObject.value(QLatin1String("logging"));
        const QJsonValue notifications = jsonObject.value(QLatin1String("notifications"));
        const QJsonValue theme = jsonObject.value(QLatin1String("theme"));
        const QJsonValue locale = jsonObject.value(QLatin1String("locale"));

        if(!enabled.isUndefined()) {
            setEnabled(enabled.toBool());
        }
        if(!logging.isUndefined()) {
            setLogging(logging.toBool());
        }
        if(!notifications.isUndefined()) {
            setNotifications(notifications.toBool());
        }
        if(!theme.isUndefined()) {
            setTheme(theme.toInt());
        }
        if(!locale.isUndefined()) {
            setLocale(locale.toString());
        }
    }
}

bool Settings::isEnabled() const {
    return mEnabled;
}

void Settings::setEnabled(bool enabled) {
    if(enabled != mEnabled) {
        mEnabled = enabled;
        emit enabledChanged(enabled);
    }
}

bool Settings::isLogging() const {
    return mLogging;
}

void Settings::setLogging(bool logging) {
    if(logging != mLogging) {
        mLogging = logging;
        emit loggingChanged(logging);
    }
}

bool Settings::isNotifications() const {
    return mNotifications;
}

void Settings::setNotifications(bool notifications) {
    if(notifications != mNotifications) {
        mNotifications = notifications;
        emit notificationsChanged(notifications);
    }
}

int Settings::theme() const {
    return mTheme;
}

void Settings::setTheme(int theme) {
    if(theme != mTheme) {
        mTheme = theme;
        emit themeChanged(theme);
    }
}

const QString& Settings::locale() const {
    return mLocale;
}

void Settings::setLocale(const QString& locale) {
    if(locale != mLocale) {
        mLocale = locale;
        emit localeChanged(locale);
    }
}

} // namespace Model
