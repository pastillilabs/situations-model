#pragma once

#include <SituationsModel/model_global.h>
#include <SituationsModel/actiongrouplist.h>

#include <QDateTime>
#include <QJsonObject>
#include <QObject>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtQml/qqmlregistration.h>
#else
#define QML_ELEMENT
#endif

namespace Model {

/**
 * @brief The Startup class
 */
class MODEL_SHARED_EXPORT Startup : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(ActionGroupList* actionGroups READ actionGroups CONSTANT)
    Q_PROPERTY(QDateTime dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged)
    Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)

public:
    enum class Type {
        TypeBoot,
        TypeAny
    };
    Q_ENUM(Type)

public:
    Q_INVOKABLE explicit Startup(QObject* parent = nullptr);
    virtual ~Startup() = default;

    QJsonObject toJson(bool persistent) const;
    void fromJson(const QJsonObject& jsonObject, bool persistent);

    ActionGroupList* actionGroups() const;

    QDateTime dateTime() const;
    void setDateTime(const QDateTime& datetime);

    Type type() const;
    void setType(Type type);

signals:
    void dateTimeChanged(const QDateTime& dateTime);
    void typeChanged(Model::Startup::Type type);

    // Methods
    void reqSetDateTime(const QDateTime& datTime);
    void reqSetType(Model::Startup::Type type);

private:
    ActionGroupList* mActionGroups{nullptr};
    QDateTime mDateTime;
    Type mType{Type::TypeBoot};
};

} // namespace Model
