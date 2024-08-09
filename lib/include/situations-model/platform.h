#pragma once

#include <situations-model/model_global.h>
#include <situations-model/contactlist.h>
#include <situations-model/packagelist.h>

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
    Q_PROPERTY(bool rooted READ isRooted WRITE setRooted NOTIFY rootedChanged)
    Q_PROPERTY(int version READ version WRITE setVersion NOTIFY versionChanged)

public:
    explicit Platform(QObject* parent = nullptr);

    ContactList* contacts() const;
    PackageList* packages() const;

    bool isRooted() const;
    void setRooted(bool rooted);

    int version() const;
    void setVersion(int version);

signals:
    void rootedChanged(bool rooted);
    void versionChanged(int version);

    // Methods
    void request(const QString& command);

private:
    ContactList* mContacts{nullptr};
    PackageList* mPackages{nullptr};

    bool mRooted{false};
    int mVersion{0};
};

} // namespace Model
