#pragma once

#include <situations-model/model_global.h>
#include <situations-model/actiongroup.h>
#include <xylitol/listmodel.h>

#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QVariant>
#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include <QtQml/qqmlregistration.h>
#endif

namespace Model {

/**
 * @brief The ActionGroupList class
 */
class MODEL_SHARED_EXPORT ActionGroupList : public Xylitol::ListModel {
    Q_OBJECT
#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QML_ELEMENT
#endif

public:
    enum Role {
        RoleGroup = Qt::UserRole
    };
    Q_ENUM(Role)

public:
    explicit ActionGroupList(QObject* parent = nullptr);
    virtual ~ActionGroupList() = default;

    QJsonObject toJson(bool persistent) const;
    void fromJson(const QJsonObject& jsonObject, bool persistent);

    void add(const QString& name, int priority);
    void remove(const QString& name);
    int indexOfName(const QString& name) const;

    Q_INVOKABLE Model::ActionGroup* findByName(const QString& name) const;

public: // From Xylitol::ListModel
    QHash<int, QByteArray> roleNames() const override;
    QHash<int, int> roleTypes() const override;
};

} // namespace Model
