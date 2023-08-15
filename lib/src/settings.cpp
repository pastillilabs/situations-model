#include "model/settings.h"

#include <QJsonObject>

namespace Model {

Settings::Settings(QObject* parent)
    : QObject(parent) {}

QJsonObject Settings::toJson(bool persistent) const {
    if(persistent) {
        return {
            {QLatin1String("enabled"), mEnabled},
            {QLatin1String("notifications"), mNotifications},
            {QLatin1String("systemBackground"), mSystemBackground},
            {QLatin1String("theme"), mTheme}
        };
    }
    else {
        return {};
    }
}

void Settings::fromJson(const QJsonObject& jsonObject, bool persistent) {
    if(persistent) {
        const QJsonValue enabled = jsonObject.value(QLatin1String("enabled"));
        const QJsonValue notifications = jsonObject.value(QLatin1String("notifications"));
        const QJsonValue systemBackground = jsonObject.value(QLatin1String("systemBackground"));
        const QJsonValue theme = jsonObject.value(QLatin1String("theme"));

        if(!enabled.isUndefined()) setEnabled(enabled.toBool());
        if(!notifications.isUndefined()) setNotifications(notifications.toBool());
        if(!systemBackground.isUndefined()) setSystemBackground(systemBackground.toBool());
        if(!theme.isUndefined()) setTheme(theme.toInt());
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

bool Settings::isNotifications() const {
    return mNotifications;
}

void Settings::setNotifications(bool notifications) {
    if(notifications != mNotifications) {
        mNotifications = notifications;
        emit notificationsChanged(notifications);
    }
}

bool Settings::isSystemBackground() const {
    return mSystemBackground;
}

void Settings::setSystemBackground(bool systemBackground) {
    if(systemBackground != mSystemBackground) {
        mSystemBackground = systemBackground;
        emit systemBackgroundChanged(systemBackground);
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

} // namespace Model
