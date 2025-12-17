#pragma once

#include <SituationsModel/model_global.h>
#include <SituationsModel/contactlist.h>
#include <SituationsModel/packagelist.h>

#include <QString>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtQml/qqmlregistration.h>
#else
#define QML_ELEMENT
#endif

namespace Model {

/**
 * @brief The Platform class
 */
class MODEL_SHARED_EXPORT Platform : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(ContactList* contacts READ contacts CONSTANT)
    Q_PROPERTY(PackageList* packages READ packages CONSTANT)
    Q_PROPERTY(CallState callState READ callState WRITE setCallState NOTIFY callStateChanged)
    Q_PROPERTY(QString locale READ locale WRITE setLocale NOTIFY localeChanged)
    Q_PROPERTY(QString suPath READ suPath WRITE setSuPath NOTIFY suPathChanged)
    Q_PROPERTY(int version READ version WRITE setVersion NOTIFY versionChanged)

public:
    enum class CallState {
        CallStateNone,
        CallStateRinging,
        CallStateActive
    };
    Q_ENUM(CallState);

public:
    explicit Platform(QObject* parent = nullptr);

    ContactList* contacts() const;
    PackageList* packages() const;

    CallState callState() const;
    void setCallState(CallState callState);

    const QString& locale() const;
    void setLocale(const QString& locale);

    const QString& suPath() const;
    void setSuPath(const QString& suPath);

    int version() const;
    void setVersion(int version);

signals:
    void callStateChanged(Model::Platform::CallState callState);
    void localeChanged(const QString& locale);
    void suPathChanged(const QString& suPath);
    void versionChanged(int version);

    // Methods
    void request(const QString& command);

private:
    ContactList* mContacts{nullptr};
    PackageList* mPackages{nullptr};

    CallState mCallState{CallState::CallStateNone};
    QString mLocale;
    QString mSuPath;
    int mVersion{0};
};

} // namespace Model
