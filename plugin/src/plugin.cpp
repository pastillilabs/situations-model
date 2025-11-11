#include "plugin.h"

#include <SituationsModel/action.h>
#include <SituationsModel/actiongroup.h>
#include <SituationsModel/actiongrouplist.h>
#include <SituationsModel/actionproperties.h>
#include <SituationsModel/application.h>
#include <SituationsModel/condition.h>
#include <SituationsModel/conditiongroup.h>
#include <SituationsModel/conditiongrouplist.h>
#include <SituationsModel/conditionproperties.h>
#include <SituationsModel/contactlist.h>
#include <SituationsModel/feature.h>
#include <SituationsModel/featurelist.h>
#include <SituationsModel/packagelist.h>
#include <SituationsModel/platform.h>
#include <SituationsModel/plugin.h>
#include <SituationsModel/settings.h>
#include <SituationsModel/situation.h>
#include <SituationsModel/situationlist.h>
#include <SituationsModel/versionlimits.h>

#include <qqml.h>

void Plugin::registerTypes([[maybe_unused]] const char* uri) {
#if(QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    // @uri SituationsModel
#if QT_VERSION >= QT_VERSION_CHECK(5, 9, 0)
    qmlRegisterModule(uri, 1, 0);
#endif
    qmlRegisterSingletonType<Model::Application>(uri, 1, 0, "Application", [](QQmlEngine* /*engine*/, QJSEngine* /*scriptEngine*/) -> QObject* {
        return new Model::Application();
    });
    qmlRegisterType<Model::Action>(uri, 1, 0, "Action");
    qmlRegisterType<Model::ActionGroup>(uri, 1, 0, "ActionGroup");
    qmlRegisterType<Model::ActionGroupList>(uri, 1, 0, "ActionGroupList");
    qmlRegisterType<Model::Condition>(uri, 1, 0, "Condition");
    qmlRegisterType<Model::ConditionGroup>(uri, 1, 0, "ConditionGroup");
    qmlRegisterType<Model::ConditionGroupList>(uri, 1, 0, "ConditionGroupList");
    qmlRegisterType<Model::ContactList>(uri, 1, 0, "ContactList");
    qmlRegisterType<Model::Feature>(uri, 1, 0, "Feature");
    qmlRegisterType<Model::FeatureList>(uri, 1, 0, "FeatureList");
    qmlRegisterType<Model::PackageList>(uri, 1, 0, "PackageList");
    qmlRegisterType<Model::Platform>(uri, 1, 0, "Platform");
    qmlRegisterType<Model::Plugin>(uri, 1, 0, "Plugin");
    qmlRegisterType<Model::Settings>(uri, 1, 0, "Settings");
    qmlRegisterType<Model::Situation>(uri, 1, 0, "Situation");
    qmlRegisterType<Model::SituationList>(uri, 1, 0, "SituationList");
    qmlRegisterUncreatableType<Model::ActionProperties>(uri, 1, 0, "actionProperties", QLatin1String("Cannot create ActionProperties instance."));
    qmlRegisterUncreatableType<Model::ConditionProperties>(uri, 1, 0, "conditionProperties", QLatin1String("Cannot create ConditionProperties instance."));
    qmlRegisterUncreatableType<Model::VersionLimits>(uri, 1, 0, "versionLimits", QLatin1String("Cannot create VersionLimits instance."));
#endif
}
