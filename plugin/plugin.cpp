#include "plugin.h"

#include <situations-model/action.h>
#include <situations-model/actiongroup.h>
#include <situations-model/actiongrouplist.h>
#include <situations-model/actionproperties.h>
#include <situations-model/application.h>
#include <situations-model/condition.h>
#include <situations-model/conditiongroup.h>
#include <situations-model/conditiongrouplist.h>
#include <situations-model/conditionproperties.h>
#include <situations-model/contactlist.h>
#include <situations-model/feature.h>
#include <situations-model/featurelist.h>
#include <situations-model/packagelist.h>
#include <situations-model/platform.h>
#include <situations-model/plugin.h>
#include <situations-model/settings.h>
#include <situations-model/situation.h>
#include <situations-model/situationlist.h>
#include <situations-model/versionlimits.h>

#include <qqml.h>

void Plugin::registerTypes([[maybe_unused]] const char* uri) {
#if(QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    // @uri com.pastillilabs.situations.model
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
    qmlRegisterType<Model::FeatureList>(uri, 1, 0, "FeatureList");
    qmlRegisterType<Model::Feature>(uri, 1, 0, "Feature");
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
