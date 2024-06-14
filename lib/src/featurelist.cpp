#include "situations-model/featurelist.h"
#include "situations-model/feature.h"

namespace Model {

FeatureList::FeatureList(QObject* parent)
    : Xylitol::ListModel(parent) {
    const auto updateHelpers = [this] {
        QStringList installed;
        QStringList purchased;

        const auto& container = mContainer;
        for(const auto& item : container) {
            const Feature* feature = item.value(FeatureList::RoleFeature).value<Feature*>();

            if(feature->isInstalled()) {
                installed.append(feature->name());
            }

            if(feature->purchaseState() == Feature::PurchaseState::PurchaseStatePurchased) {
                purchased.append(feature->name());
            }
        }

        if(purchased != mPurchased) {
            mPurchased = purchased;
            emit purchasedChanged(purchased);
        }

        if(installed != mInstalled) {
            mInstalled = installed;
            emit installedChanged(installed);
        }
    };

    connect(this, &FeatureList::rowsInserted,
            this, [this, updateHelpers]([[maybe_unused]] const QModelIndex& parent, int first, int last) {
                for(int i = first; i <= last; ++i) {
                    const Item& item = mContainer.at(i);
                    const Feature* feature = item.value(FeatureList::RoleFeature).value<Feature*>();
                    connect(feature, &Feature::installedChanged, this, updateHelpers);
                    connect(feature, &Feature::purchaseStateChanged, this, updateHelpers);
                }

                updateHelpers();
            });
    connect(this, &FeatureList::rowsRemoved, this, updateHelpers);
    connect(this, &FeatureList::modelReset,
            this, [this, updateHelpers] {
                const auto& container = mContainer;
                for(const Item& item : container) {
                    const Feature* feature = item.value(FeatureList::RoleFeature).value<Feature*>();
                    connect(feature, &Feature::installedChanged, this, updateHelpers);
                    connect(feature, &Feature::purchaseStateChanged, this, updateHelpers);
                }

                updateHelpers();
            });
}

QJsonObject FeatureList::toJson(bool persistent) const {
    QJsonArray featureArray;
    for(const Model::FeatureList::Item& item : container()) {
        const Model::Feature* feature = item.value(Model::FeatureList::RoleFeature).value<Model::Feature*>();
        featureArray.append(feature->toJson(persistent));
    }

    return {
        {QLatin1String("container"), featureArray}
    };
}

void FeatureList::fromJson(const QJsonObject& jsonObject, bool persistent) {
    const QJsonArray container = jsonObject.value(QLatin1String("container")).toArray();

    for(const QJsonValue& featureValue : container) {
        const QJsonValue name = featureValue.toObject().value(QLatin1String("name"));

        Model::Feature* feature = featureByName(name.toString());
        if(feature) {
            feature->fromJson(featureValue.toObject(), persistent);
        }
    }
}

int FeatureList::versionBuild() const {
    return mVersionBuild;
}

void FeatureList::setVersionBuild(int versionBuild) {
    if(versionBuild != mVersionBuild) {
        mVersionBuild = versionBuild;
        emit versionBuildChanged(versionBuild);
    }
}

bool FeatureList::isUpdating() const {
    return mUpdating;
}

void FeatureList::setUpdating(bool updating) {
    if(updating != mUpdating) {
        mUpdating = updating;
        emit updatingChanged(updating);
    }
}

bool FeatureList::isUpdatingFailed() const {
    return mUpdatingFailed;
}

void FeatureList::setUpdatingFailed(bool updatingFailed) {
    if(updatingFailed != mUpdatingFailed) {
        mUpdatingFailed = updatingFailed;
        emit updatingFailedChanged(updatingFailed);
    }
}

int FeatureList::indexOfName(const QString& name) const {
    for(int i = 0; i < mContainer.count(); ++i) {
        const Feature* feature = mContainer.at(i).value(FeatureList::RoleFeature).value<Feature*>();
        if(feature->name() == name) {
            return i;
        }
    }

    return -1;
}

int FeatureList::indexOfBase(const QString& base) const {
    for(int i = 0; i < mContainer.count(); ++i) {
        const Feature* feature = mContainer.at(i).value(FeatureList::RoleFeature).value<Feature*>();
        if(feature->base() == base && Feature::TypeFlags::fromInt(feature->typeFlags()).testFlag(Model::Feature::TypeFlagExtension)) {
            return i;
        }
    }

    return -1;
}

void FeatureList::add(const QString& name,
                      const Feature::TypeFlags& typeFlags,
                      const VersionLimits& actionLimits,
                      const VersionLimits& conditionLimits,
                      const QStringList& packages,
                      const QString& base) {
    if(indexOfName(name) < 0) {
        Feature* feature = new Feature(this);
        feature->setName(name);
        feature->setTypeFlags(typeFlags);
        feature->setActionLimits(actionLimits);
        feature->setConditionLimits(conditionLimits);
        feature->setPackages(packages);
        feature->setBase(base);

        const int index = mContainer.count();
        beginInsertRows(QModelIndex(), index, index);
        mContainer.append({{RoleFeature, QVariant::fromValue(feature)}});
        endInsertRows();
    }
}

const QStringList& FeatureList::installed() const {
    return mInstalled;
}

const QStringList& FeatureList::purchased() const {
    return mPurchased;
}

Feature* FeatureList::featureByName(const QString& name) const {
    Feature* feature = nullptr;
    const int index = indexOfName(name);
    if(index >= 0) {
        feature = mContainer.at(index).value(FeatureList::RoleFeature).value<Feature*>();
    }

    return feature;
}

Feature* FeatureList::featureByBase(const QString& base) const {
    Feature* feature = nullptr;
    const int index = indexOfBase(base);
    if(index >= 0) {
        feature = mContainer.at(index).value(FeatureList::RoleFeature).value<Feature*>();
    }

    return feature;
}

Plugin* FeatureList::pluginByName(const QString& name) const {
    Plugin* plugin = nullptr;
    const Feature* feature = featureByName(name);
    if(feature) {
        plugin = feature->plugin();
    }

    return plugin;
}

QHash<int, QByteArray> FeatureList::roleNames() const {
    static const QHash<int, QByteArray> names{
        {RoleFeature, "feature"}
    };
    return names;
}

QHash<int, int> FeatureList::roleTypes() const {
    static const QHash<int, int> types{
        {RoleFeature, qMetaTypeId<Feature*>()}
    };
    return types;
}

} // namespace Model
