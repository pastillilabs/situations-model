#include "SituationsModel/root.h"

#include <Xylitol/templates.h>

namespace Model {

namespace {

Root* root = nullptr;

} // namespace

Root* Root::instance() {
    return root;
}

Root::Root(QObject* parent)
    : QObject(parent)
    , mFeatures(new FeatureList(this))
    , mPlatform(new Platform(this))
    , mSettings(new Settings(this))
    , mSituations(new SituationList(this)) {
    root = this;

    Xylitol::registerGadget<ActionProperties>();
    Xylitol::registerGadget<ConditionProperties>();
    Xylitol::registerGadget<VersionLimits>();
}

QJsonObject Root::toJson(bool persistent) const {
    return QJsonObject{
        {QLatin1String("build"), mBuild},
        {QLatin1String("features"), mFeatures->toJson(persistent)},
        {QLatin1String("situations"), mSituations->toJson(persistent)},
        {QLatin1String("settings"), mSettings->toJson(persistent)}
    };
}

void Root::fromJson(const QJsonObject& jsonObject, bool persistent, const SituationList::Initializer& situationInitializer) {
    const QJsonValue build = jsonObject.value(QLatin1String("build"));
    const QJsonValue features = jsonObject.value(QLatin1String("features"));
    const QJsonValue situations = jsonObject.value(QLatin1String("situations"));
    const QJsonValue settings = jsonObject.value(QLatin1String("settings"));

    if(!build.isUndefined()) {
        setBuild(build.toInt());
    }
    if(!features.isUndefined()) {
        mFeatures->fromJson(features.toObject(), persistent);
    }
    if(!situations.isUndefined()) {
        mSituations->fromJson(situations.toObject(), persistent, situationInitializer);
    }
    if(!settings.isUndefined()) {
        mSettings->fromJson(settings.toObject(), persistent);
    }
}

Root::~Root() {
    root = nullptr;
}

FeatureList* Root::features() const {
    return mFeatures;
}

Platform* Root::platform() const {
    return mPlatform;
}

Settings* Root::settings() const {
    return mSettings;
}

SituationList* Root::situations() const {
    return mSituations;
}

bool Root::isImporting() const {
    return mImporting;
}

void Root::setImporting(bool importing) {
    if(importing != mImporting) {
        mImporting = importing;
        emit importingChanged(importing);
    }
}

bool Root::isRestarting() const {
    return mRestarting;
}

void Root::setRestarting(bool restarting) {
    if(restarting != mRestarting) {
        mRestarting = restarting;
        emit restartingChanged(restarting);
    }
}

int Root::build() const {
    return mBuild;
}

void Root::setBuild(int build) {
    if(build != mBuild) {
        mBuild = build;
        emit buildChanged(build);
    }
}

} // namespace Model
