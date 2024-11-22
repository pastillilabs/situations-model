#include "situations-model/application.h"

#include <xylitol/templates.h>

namespace Model {

namespace {

Application* application = nullptr;

} // namespace

Application* Application::instance() {
    return application;
}

Application::Application(QObject* parent)
    : QObject(parent)
    , mFeatures(new FeatureList(this))
    , mPlatform(new Platform(this))
    , mSettings(new Settings(this))
    , mSituations(new SituationList(this)) {
    application = this;

    Xylitol::registerGadget<ActionProperties>();
    Xylitol::registerGadget<ConditionProperties>();
    Xylitol::registerGadget<VersionLimits>();
}

QJsonObject Application::toJson(bool persistent) const {
    return QJsonObject{
        {QLatin1String("build"), mBuild},
        {QLatin1String("features"), mFeatures->toJson(persistent)},
        {QLatin1String("situations"), mSituations->toJson(persistent)},
        {QLatin1String("settings"), mSettings->toJson(persistent)}
    };
}

void Application::fromJson(const QJsonObject& jsonObject, bool persistent, const SituationList::Initializer& situationInitializer) {
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

Application::~Application() {
    application = nullptr;
}

FeatureList* Application::features() const {
    return mFeatures;
}

Platform* Application::platform() const {
    return mPlatform;
}

Settings* Application::settings() const {
    return mSettings;
}

SituationList* Application::situations() const {
    return mSituations;
}

bool Application::isExporting() const {
    return mExporting;
}

void Application::setExporting(bool exporting) {
    if(exporting != mExporting) {
        mExporting = exporting;
        emit exportingChanged(exporting);
    }
}

bool Application::isImporting() const {
    return mImporting;
}

void Application::setImporting(bool importing) {
    if(importing != mImporting) {
        mImporting = importing;
        emit importingChanged(importing);
    }
}

bool Application::isRestarting() const {
    return mRestarting;
}

void Application::setRestarting(bool restarting) {
    if(restarting != mRestarting) {
        mRestarting = restarting;
        emit restartingChanged(restarting);
    }
}

int Application::build() const {
    return mBuild;
}

void Application::setBuild(int build) {
    if(build != mBuild) {
        mBuild = build;
        emit buildChanged(build);
    }
}

} // namespace Model
