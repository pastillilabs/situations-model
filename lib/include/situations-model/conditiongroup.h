#pragma once

#include <situations-model/condition.h>
#include <situations-model/model_global.h>
#include <xylitol/listmodel.h>

#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>

#include <functional>

namespace Model {

/**
 * @brief The ConditionGroup class
 */
class MODEL_SHARED_EXPORT ConditionGroup : public Xylitol::ListModel {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int priority READ priority WRITE setPriority NOTIFY priorityChanged)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(bool negative READ isNegative WRITE setNegative NOTIFY negativeChanged)

    Q_PROPERTY(int count READ count NOTIFY countChanged STORED false)

public:
    enum Role {
        RoleCondition = Qt::UserRole
    };
    Q_ENUM(Role)

public:
    Q_INVOKABLE explicit ConditionGroup(QObject* parent = nullptr);
    virtual ~ConditionGroup() = default;

    QJsonObject toJson(bool persistent) const;
    void fromJson(const QJsonObject& jsonObject, bool persistent);

    void clone(const ConditionGroup& source);

    const QString& name() const;
    void setName(const QString& name);

    int priority() const;
    void setPriority(int priority);

    bool isActive() const;
    void setActive(bool active);

    bool isNegative() const;
    void setNegative(bool negative);

    int count() const;

    void add(const std::function<void(Condition& condition)>& initializer);
    void remove(const QString& uid);

    Model::Condition* findByUid(const QString& uid) const;
    int indexOfUid(const QString& uid) const;
    int readyCount() const;

public: // From Xylitol::ListModel
    QHash<int, QByteArray> roleNames() const override;
    QHash<int, int> roleTypes() const override;

signals:
    void nameChanged(const QString& name);
    void priorityChanged(int priority);
    void activeChanged(bool active);
    void negativeChanged(bool negative);
    void countChanged(int count);

    // Methods
    void reqAdd();
    void reqRemove(const QString& uid);
    void reqSetNegative(bool negative);

private:
    QString mName;
    int mPriority{0};
    bool mActive{false};
    bool mNegative{false};
};

} // namespace Model
