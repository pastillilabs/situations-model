#include "model/feature.h"
#include "logging.h"
#include "util.h"

#include <xylitol/util.h>

#include <QJsonObject>

#include <cstring>

namespace Model {

Feature::Feature(QObject* parent)
    : QObject(parent) {
    const auto resetPluginLoader = [this] {
        delete mPluginLoader;
        mPluginLoader = nullptr;

        QPluginLoader* pluginLoader{nullptr};
        if(!name().isEmpty() && typeFlags().testFlag(TypeFlagPlugin)) {
            pluginLoader = new QPluginLoader(Util::pluginPath(name()), this);
            if(!pluginLoader->load()) {
                qCWarning(model) << "Failed to load plugin" << pluginLoader->fileName();
                qCWarning(model) << "Error:" << pluginLoader->errorString();

                delete pluginLoader;
                pluginLoader = nullptr;
            }
        }

        setPluginLoader(pluginLoader);
    };

    connect(this, &Feature::nameChanged, this, resetPluginLoader);
    connect(this, &Feature::typeFlagsChanged, this, resetPluginLoader);
}

Feature::~Feature() {
    delete mPlugin;
    mPlugin = nullptr;

    delete mPluginLoader;
    mPluginLoader = nullptr;
}

QJsonObject Feature::toJson(bool persistent) const {
    if(persistent) {
        return {
            {QLatin1String("name"), mName},
            {QLatin1String("price"), mPrice},
            {QLatin1String("purchaseState"), static_cast<int>(purchaseState())},
            {QLatin1String("receipt"), mReceipt},
            {QLatin1String("signature"), mSignature},
            {QLatin1String("removeDate"), mRemoveDate.toString(Qt::ISODate)},
            {QLatin1String("installed"), mInstalled},
            {QLatin1String("plugin"), mPlugin ? mPlugin->toJson(persistent) : QJsonObject()}
        };
    }
    else {
        return {
            {QLatin1String("name"), mName},
            {QLatin1String("plugin"), mPlugin ? mPlugin->toJson(persistent) : QJsonObject()}
        };
    }
}

void Feature::fromJson(const QJsonObject& jsonObject, bool persistent) {
    if(persistent) {
        const QJsonValue name = jsonObject.value(QLatin1String("name"));
        const QJsonValue price = jsonObject.value(QLatin1String("price"));
        const QJsonValue receipt = jsonObject.value(QLatin1String("receipt"));
        const QJsonValue signature = jsonObject.value(QLatin1String("signature"));
        const QJsonValue removeDate = jsonObject.value(QLatin1String("removeDate"));
        const QJsonValue installed = jsonObject.value(QLatin1String("installed"));
        const QJsonValue plugin = jsonObject.value(QLatin1String("plugin"));

        if(!name.isUndefined()) setName(name.toString());
        if(!price.isUndefined()) setPrice(price.toString());
        if(!receipt.isUndefined()) setReceipt(receipt.toString());
        if(!signature.isUndefined()) setSignature(signature.toString());
        if(!removeDate.isUndefined()) setRemoveDate(QDateTime::fromString(removeDate.toString(), Qt::ISODate));
        if(!installed.isUndefined()) setInstalled(installed.toBool());
        if(!plugin.isUndefined() && mPlugin) mPlugin->fromJson(plugin.toObject(), persistent);
    }
    else {
        const QJsonValue purchaseState = jsonObject.value(QLatin1String("purchaseState"));
        const QJsonValue plugin = jsonObject.value(QLatin1String("plugin"));

        if(!purchaseState.isUndefined()) setPurchaseState(static_cast<PurchaseState>(purchaseState.toInt()));
        if(!plugin.isUndefined() && mPlugin) mPlugin->fromJson(plugin.toObject(), persistent);
    }
}

const QString& Feature::name() const {
    return mName;
}

void Feature::setName(const QString& name) {
    if(name != mName) {
        mName = name;
        emit nameChanged(name);
    }
}

const Feature::TypeFlags& Feature::typeFlags() const {
    return mTypeFlags;
}

void Feature::setTypeFlags(const TypeFlags& typeFlags) {
    if(typeFlags != mTypeFlags) {
        mTypeFlags = typeFlags;
        emit typeFlagsChanged(typeFlags);
    }
}

const VersionLimits& Feature::actionLimits() const {
    return mActionLimits;
}

void Feature::setActionLimits(const VersionLimits& actionLimits) {
    if(actionLimits != mActionLimits) {
        mActionLimits = actionLimits;
        emit actionLimitsChanged(actionLimits);
    }
}

const VersionLimits& Feature::conditionLimits() const {
    return mConditionLimits;
}

void Feature::setConditionLimits(const VersionLimits& conditionLimits) {
    if(conditionLimits != mConditionLimits) {
        mConditionLimits = conditionLimits;
        emit conditionLimitsChanged(conditionLimits);
    }
}

const QStringList& Feature::packages() const {
    return mPackages;
}

void Feature::setPackages(const QStringList& packages) {
    if(packages != mPackages) {
        mPackages = packages;
        emit packagesChanged(packages);
    }
}

const QString& Feature::base() const {
    return mBase;
}

void Feature::setBase(const QString& base) {
    if(base != mBase) {
        mBase = base;
        emit baseChanged(base);
    }
}

Feature::PurchaseState Feature::purchaseState() const {
    return mPurchaseState;
}

void Feature::setPurchaseState(PurchaseState purchaseState) {
    if(purchaseState != mPurchaseState) {
        mPurchaseState = purchaseState;
        emit purchaseStateChanged(purchaseState);
    }
}

const QString& Feature::price() const {
    return mPrice;
}

void Feature::setPrice(const QString& price) {
    if(price != mPrice) {
        mPrice = price;
        emit priceChanged(price);
    }
}

const QString& Feature::receipt() const {
    return mReceipt;
}

void Feature::setReceipt(const QString& receipt) {
    if(receipt != mReceipt) {
        mReceipt = receipt;
        emit receiptChanged(receipt);
    }
}

const QString& Feature::signature() const {
    return mSignature;
}

void Feature::setSignature(const QString& signature) {
    if(signature != mSignature) {
        mSignature = signature;
        emit signatureChanged(signature);
    }
}

const QDateTime& Feature::removeDate() const {
    return mRemoveDate;
}

void Feature::setRemoveDate(const QDateTime& removeDate) {
    if(removeDate != mRemoveDate) {
        mRemoveDate = removeDate;
        emit removeDateChanged(removeDate);
    }
}
bool Feature::isInstalled() const {
    return mInstalled;
}

void Feature::setInstalled(bool installed) {
    if(installed != mInstalled) {
        mInstalled = installed;
        emit installedChanged(installed);
    }
}

Plugin* Feature::plugin() const {
    return mPlugin;
}

void Feature::setPlugin(Plugin* plugin) {
    if(plugin != mPlugin) {
        mPlugin = plugin;
        emit pluginChanged(plugin);
    }
}

QPluginLoader* Feature::pluginLoader() const {
    return mPluginLoader;
}

void Feature::setPluginLoader(QPluginLoader* pluginLoader) {
    if(pluginLoader != mPluginLoader) {
        mPluginLoader = pluginLoader;
        emit pluginLoaderChanged(pluginLoader);
    }
}

Plugin* Feature::createPlugin() {
    Plugin* plugin = nullptr;
    if(!mPlugin && mPluginLoader) {
        plugin = qobject_cast<Plugin*>(mPluginLoader->instance());
        if(plugin) {
            setPlugin(plugin);
        }
        else {
            qCWarning(model) << "Failed to instantiate plugin" << mPluginLoader->fileName();
            qCWarning(model) << "Error:" << mPluginLoader->errorString();
        }
    }

    return plugin;
}

bool Feature::isAvailableAction(int platformVersion, bool rooted) const {
    const bool normalAction = (platformVersion >= mActionLimits.min() && platformVersion <= mActionLimits.max());
    const bool rootAction = (platformVersion >= mActionLimits.rootMin() && platformVersion <= mActionLimits.rootMax());

    return (normalAction || (rooted && rootAction));
}

bool Feature::isAvailableCondition(int platformVersion, bool rooted) const {
    const bool normalCondition = (platformVersion >= mConditionLimits.min() && platformVersion <= mConditionLimits.max());
    const bool rootCondition = (platformVersion >= mConditionLimits.rootMin() && platformVersion <= mConditionLimits.rootMax());

    return (normalCondition || (rooted && rootCondition));
}

QVariant Feature::xylitolFromVariant(const QMetaProperty& metaProperty, const QVariant& variant) {
    QVariant value;

    if(std::strcmp(metaProperty.name(), "plugin") == 0) {
        Plugin* plugin = nullptr;

        if(!variant.isNull() && mPluginLoader) {
            plugin = qobject_cast<Plugin*>(mPluginLoader->instance());
            if(plugin) {
                Xylitol::fromVariant(*plugin, variant);
                value = QVariant::fromValue(plugin);
            }
            else {
                qCWarning(model) << "Failed to instantiate plugin" << mPluginLoader->fileName();
                qCWarning(model) << "Error:" << mPluginLoader->errorString();
            }
        }
    }

    return value;
}

void Feature::xylitolWrite(const QMetaProperty& metaProperty, const QVariant& value) {
    if(std::strcmp(metaProperty.name(), "plugin") == 0) {
        setPlugin(value.value<Plugin*>());
    }
}

} // namespace Model
