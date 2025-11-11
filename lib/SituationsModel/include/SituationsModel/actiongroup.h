#pragma once

#include <SituationsModel/action.h>
#include <SituationsModel/model_global.h>
#include <Xylitol/listmodel.h>

#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include <QObject>
#include <QString>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtQml/qqmlregistration.h>
#else
#define QML_ELEMENT
#endif

#include <functional>

namespace Model {

/**
 * @brief The ActionGroup class
 */
class MODEL_SHARED_EXPORT ActionGroup  : public Xylitol::ListModel {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int priority READ priority WRITE setPriority NOTIFY priorityChanged)

    Q_PROPERTY(int count READ count NOTIFY countChanged STORED false)

public:
    enum Role {
        RoleAction = Qt::UserRole
    };
    Q_ENUM(Role)

public:
    Q_INVOKABLE explicit ActionGroup(QObject* parent = nullptr);
    virtual ~ActionGroup() = default;

    QJsonObject toJson(bool persistent) const;
    void fromJson(const QJsonObject& jsonObject, bool persistent);

    void clone(const ActionGroup& source);

    const QString& name() const;
    void setName(const QString& name);

    int priority() const;
    void setPriority(int priority);

    int count() const;

    void add(const std::function<void(Action& action)>& initializer);
    void remove(const QString& uid);

    Model::Action* findByUid(const QString& uid) const;
    int indexOfUid(const QString& uid) const;
    int readyCount() const;

public: // From Xylitol::ListModel
    QHash<int, QByteArray> roleNames() const override;
    QHash<int, int> roleTypes() const override;

signals:
    void nameChanged(const QString& name);
    void priorityChanged(int priority);
    void countChanged(int count);

    // Methods
    void reqAdd();
    void reqRemove(const QString& uid);

private:
    QString mName;
    int mPriority{0};
};

} // namespace Model
