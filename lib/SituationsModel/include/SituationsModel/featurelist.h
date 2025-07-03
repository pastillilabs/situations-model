#pragma once

#include <SituationsModel/feature.h>
#include <SituationsModel/model_global.h>
#include <SituationsModel/plugin.h>
#include <Xylitol/listmodel.h>

#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QtQml/qqmlregistration.h>

namespace Model {

/**
 * @brief The FeatureList class
 */
class MODEL_SHARED_EXPORT FeatureList : public Xylitol::ListModel {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int versionBuild READ versionBuild WRITE setVersionBuild NOTIFY versionBuildChanged)
    Q_PROPERTY(bool updating READ isUpdating WRITE setUpdating NOTIFY updatingChanged)
    Q_PROPERTY(bool updatingFailed READ isUpdatingFailed WRITE setUpdatingFailed NOTIFY updatingFailedChanged)

    Q_PROPERTY(QStringList installed READ installed NOTIFY installedChanged STORED false)
    Q_PROPERTY(QStringList purchased READ purchased NOTIFY purchasedChanged STORED false)

public:
    enum Role {
        RoleFeature = Qt::UserRole
    };
    Q_ENUM(Role)

public:
    explicit FeatureList(QObject* parent = nullptr);
    virtual ~FeatureList() = default;

    QJsonObject toJson(bool persistent) const;
    void fromJson(const QJsonObject& jsonObject, bool persistent);

    int versionBuild() const;
    void setVersionBuild(int versionBuild);

    bool isUpdating() const;
    void setUpdating(bool updating);

    bool isUpdatingFailed() const;
    void setUpdatingFailed(bool updatingFailed);

    int indexOfName(const QString& name) const;
    int indexOfBase(const QString& base) const;
    void add(const QString& name,
             const Feature::TypeFlags& typeFlags,
             const VersionLimits& actionLimits = {},
             const VersionLimits& conditionLimits = {},
             const QStringList& packages = {},
             const QString& base = {});

    const QStringList& installed() const;
    const QStringList& purchased() const;

    Q_INVOKABLE Model::Feature* featureByName(const QString& name) const;
    Q_INVOKABLE Model::Feature* featureByBase(const QString& base) const;
    Q_INVOKABLE Model::Plugin* pluginByName(const QString& name) const;

public: // From Xylitol::ListModel
    QHash<int, QByteArray> roleNames() const override;
    QHash<int, int> roleTypes() const override;

signals:
    void versionBuildChanged(int versionBuild);
    void updatingChanged(bool updating);
    void updatingFailedChanged(bool updatingFailed);
    void installedChanged(const QStringList& installed);
    void purchasedChanged(const QStringList& purchased);

    // Methods
    void reqUpdate();

private:
    int mVersionBuild{0};
    bool mUpdating{false};
    bool mUpdatingFailed{false};

    QStringList mInstalled;
    QStringList mPurchased;
};

} // namespace Model
