#pragma once

#include <situations-model/model_global.h>
#include <xylitol/listmodel.h>

#include <QByteArray>
#include <QHash>
#include <QObject>
#include <QString>
#include <QVector>
#include <QtQml/qqmlregistration.h>

namespace Model {

/**
 * @brief The PackageList class
 */
class MODEL_SHARED_EXPORT PackageList : public Xylitol::ListModel {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool updating READ isUpdating WRITE setUpdating NOTIFY updatingChanged)

public:
    enum Role {
        RoleId = Qt::UserRole,
        RoleName
    };

public:
    explicit PackageList(QObject* parent = nullptr);
    virtual ~PackageList() = default;

    bool isUpdating() const;
    void setUpdating(bool updating);

    void reset(const Container& container);
    void update(const Item& item);

    Q_INVOKABLE int indexOf(const QString& id) const;
    Q_INVOKABLE QString idByIndex(int index) const;
    Q_INVOKABLE QString nameByIndex(int index) const;

signals:
    void updatingChanged(bool updating);

    // Methods
    void reqUpdate();

public: // From Xylitol::ListModel
    QHash<int, QByteArray> roleNames() const override;
    QHash<int, int> roleTypes() const override;

private:
    bool mUpdating{false};
};

} // namespace Model
