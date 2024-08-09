#pragma once

#include <situations-model/model_global.h>

#include <QJsonObject>
#include <QObject>
#include <QtQml/qqmlregistration.h>

namespace Model {

/**
 * @brief The Settings class
 */
class MODEL_SHARED_EXPORT Settings : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(bool notifications READ isNotifications WRITE setNotifications NOTIFY notificationsChanged)
    Q_PROPERTY(int theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(QString locale READ locale WRITE setLocale NOTIFY localeChanged)

public:
    explicit Settings(QObject* parent = nullptr);
    virtual ~Settings() = default;

    QJsonObject toJson(bool persistent) const;
    void fromJson(const QJsonObject& jsonObject, bool persistent);

    bool isEnabled() const;
    void setEnabled(bool enabled);

    bool isNotifications() const;
    void setNotifications(bool notifications);

    int theme() const;
    void setTheme(int theme);

    const QString& locale() const;
    void setLocale(const QString& locale);

signals:
    void enabledChanged(bool enabled);
    void notificationsChanged(bool notifications);
    void themeChanged(int theme);
    void localeChanged(const QString& locale);

    // Methods
    void reqSetEnabled(bool enabled);
    void reqSetNotifications(bool notifications);
    void reqSetTheme(int theme);
    void reqSetLocale(const QString& locale);

private:
    bool mEnabled{false};
    bool mNotifications{false};
    int mTheme{0};
    QString mLocale;
};

} // namespace Model
