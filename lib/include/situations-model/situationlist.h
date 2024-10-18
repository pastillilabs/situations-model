#pragma once

#include <situations-model/model_global.h>
#include <situations-model/situation.h>
#include <xylitol/listmodel.h>

#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QtQml/qqmlregistration.h>

#include <functional>

namespace Model {

/**
 * @brief The SituationList class
 */
class MODEL_SHARED_EXPORT SituationList : public Xylitol::ListModel {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int count READ count NOTIFY countChanged STORED false)

public:
    enum Role {
        RoleSituation = Qt::UserRole
    };
    Q_ENUM(Role)

    typedef std::function<void(Situation& situation)> Initializer;

public:
    explicit SituationList(QObject* parent = nullptr);
    virtual ~SituationList() = default;

    QJsonObject toJson(bool persistent) const;
    void fromJson(const QJsonObject& jsonObject, bool persistent, const Initializer& initializer);

    void add(const Initializer& initializer);
    void remove(const QString& uid);
    void move(const QString& uid, int target);
    void reset();
    int count() const;

    Q_INVOKABLE Model::Situation* findByUid(const QString& uid) const;
    Q_INVOKABLE int indexOfUid(const QString& uid) const;
    Q_INVOKABLE QString uidByIndex(int index) const;

signals:
    void countChanged(int count);

    // Methods
    void reqAdd(const QString& uid, const QString& name, const QString& icon, const QJsonObject& metaData);
    void reqRemove(const QString& uid);
    void reqMove(const QString& uid, int index);

public: // From Xylitol::ListModel
    QHash<int, QByteArray> roleNames() const override;
    QHash<int, int> roleTypes() const override;
};

} // namespace Model
