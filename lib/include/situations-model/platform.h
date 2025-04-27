#pragma once

#include <situations-model/model_global.h>
#include <situations-model/contactlist.h>
#include <situations-model/packagelist.h>

#include <QString>
#include <QtQml/qqmlregistration.h>

namespace Model {

/**
 * @brief The Platform class
 */
class MODEL_SHARED_EXPORT Platform : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(ContactList* contacts READ contacts CONSTANT)
    Q_PROPERTY(PackageList* packages READ packages CONSTANT)
    Q_PROPERTY(QString locale READ locale WRITE setLocale NOTIFY localeChanged)
    Q_PROPERTY(QString suPath READ suPath WRITE setSuPath NOTIFY suPathChanged)
    Q_PROPERTY(int version READ version WRITE setVersion NOTIFY versionChanged)

public:
    explicit Platform(QObject* parent = nullptr);

    ContactList* contacts() const;
    PackageList* packages() const;

    const QString& locale() const;
    void setLocale(const QString& locale);

    const QString& suPath() const;
    void setSuPath(const QString& suPath);

    int version() const;
    void setVersion(int version);

signals:
    void localeChanged(const QString& locale);
    void suPathChanged(const QString& suPath);
    void versionChanged(int version);

    // Methods
    void request(const QString& command);

private:
    ContactList* mContacts{nullptr};
    PackageList* mPackages{nullptr};

    QString mLocale;
    QString mSuPath;
    int mVersion{0};
};

} // namespace Model
