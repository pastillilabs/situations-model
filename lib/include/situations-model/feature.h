#pragma once

#include <situations-model/model_global.h>
#include <situations-model/plugin.h>
#include <situations-model/versionlimits.h>

#include <QDateTime>
#include <QJsonObject>
#include <QJsonValue>
#include <QMetaProperty>
#include <QObject>
#include <QPluginLoader>
#include <QString>
#include <QStringList>
#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include <QtQml/qqmlregistration.h>
#endif

namespace Model {

/**
 * @brief The Feature class
 */
class MODEL_SHARED_EXPORT Feature : public QObject {
    Q_OBJECT
#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QML_ELEMENT
#endif
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int typeFlags READ typeFlags WRITE setTypeFlags NOTIFY typeFlagsChanged)
    Q_PROPERTY(Model::VersionLimits actionLimits READ actionLimits WRITE setActionLimits NOTIFY actionLimitsChanged)
    Q_PROPERTY(Model::VersionLimits conditionLimits READ conditionLimits WRITE setConditionLimits NOTIFY conditionLimitsChanged)
    Q_PROPERTY(QStringList packages READ packages WRITE setPackages NOTIFY packagesChanged)
    Q_PROPERTY(QString base READ base WRITE setBase NOTIFY baseChanged)
    Q_PROPERTY(PurchaseState purchaseState READ purchaseState WRITE setPurchaseState NOTIFY purchaseStateChanged)
    Q_PROPERTY(QString price READ price WRITE setPrice NOTIFY priceChanged)
    Q_PROPERTY(QString receipt READ receipt WRITE setReceipt NOTIFY receiptChanged)
    Q_PROPERTY(QString signature READ signature WRITE setSignature NOTIFY signatureChanged)
    Q_PROPERTY(QDateTime removeDate READ removeDate WRITE setRemoveDate NOTIFY removeDateChanged)
    Q_PROPERTY(bool installed READ isInstalled WRITE setInstalled NOTIFY installedChanged)
    Q_PROPERTY(Plugin* plugin READ plugin NOTIFY pluginChanged)

    Q_PROPERTY(QPluginLoader* pluginLoader READ pluginLoader NOTIFY pluginLoaderChanged STORED false)

public:
    enum TypeFlag {
        TypeFlagNone        = 0,
        TypeFlagPlugin      = 1 << 0,
        TypeFlagExtension   = 1 << 1,
        TypeFlagPackage     = 1 << 2,
        TypeFlagFree        = 1 << 3,
        TypeFlagPaid        = 1 << 4
    };
    Q_ENUM(TypeFlag)
    Q_DECLARE_FLAGS(TypeFlags, TypeFlag)
    Q_FLAG(TypeFlags)

    enum class PurchaseState {
        PurchaseStateNone,
        PurchaseStatePending,
        PurchaseStatePurchased
    };
    Q_ENUM(PurchaseState)

public:
    Q_INVOKABLE explicit Feature(QObject* parent = nullptr);
    virtual ~Feature();

    QJsonObject toJson(bool persistent) const;
    void fromJson(const QJsonObject& jsonObject, bool persistent);

    const QString& name() const;
    void setName(const QString& name);

    int typeFlags() const;
    void setTypeFlags(int typeFlags);

    const VersionLimits& actionLimits() const;
    void setActionLimits(const VersionLimits& actionLimits);

    const VersionLimits& conditionLimits() const;
    void setConditionLimits(const VersionLimits& conditionLimits);

    const QStringList& packages() const;
    void setPackages(const QStringList& packages);

    const QString& base() const;
    void setBase(const QString& base);

    PurchaseState purchaseState() const;
    void setPurchaseState(PurchaseState purchaseState);

    const QString& price() const;
    void setPrice(const QString& price);

    const QString& receipt() const;
    void setReceipt(const QString& receipt);

    const QString& signature() const;
    void setSignature(const QString& signature);

    const QDateTime& removeDate() const;
    void setRemoveDate(const QDateTime& removeDate);

    bool isInstalled() const;
    void setInstalled(bool installed);

    Plugin* plugin() const;
    void setPlugin(Plugin* plugin);

    QPluginLoader* pluginLoader() const;
    void setPluginLoader(QPluginLoader* pluginLoader);

    Plugin* createPlugin();

    Q_INVOKABLE bool isAvailableAction(int platformVersion, bool rooted) const;
    Q_INVOKABLE bool isAvailableCondition(int platformVersion, bool rooted) const;

    Q_INVOKABLE QVariant xylitolFromVariant(const QMetaProperty& metaProperty, const QVariant& variant);
    Q_INVOKABLE void xylitolWrite(const QMetaProperty& metaProperty, const QVariant& value);

signals:
    void nameChanged(const QString& name);
    void typeFlagsChanged(int typeFlags);
    void actionLimitsChanged(const Model::VersionLimits& actionLimits);
    void conditionLimitsChanged(const Model::VersionLimits& conditionLimits);
    void packagesChanged(const QStringList& packages);
    void baseChanged(const QString& base);
    void purchaseStateChanged(Model::Feature::PurchaseState purchaseState);
    void priceChanged(const QString& price);
    void receiptChanged(const QString& receipt);
    void signatureChanged(const QString& signature);
    void removeDateChanged(const QDateTime& removeDate);
    void installedChanged(bool installed);
    void pluginChanged(Model::Plugin* plugin);

    void pluginLoaderChanged(QPluginLoader* pluginLoader);

    // Methods
    void reqInstall();
    void reqUninstall();

private:
    QString mName;
    int mTypeFlags{TypeFlag::TypeFlagNone};
    VersionLimits mActionLimits;
    VersionLimits mConditionLimits;
    QStringList mPackages;
    QString mBase;
    PurchaseState mPurchaseState{PurchaseState::PurchaseStateNone};
    QString mPrice;
    QString mReceipt;
    QString mSignature;
    QDateTime mRemoveDate;
    bool mInstalled{false};
    Plugin* mPlugin{nullptr};

    QPluginLoader* mPluginLoader{nullptr};
};

} // namespace Model

Q_DECLARE_OPERATORS_FOR_FLAGS(Model::Feature::TypeFlags)
