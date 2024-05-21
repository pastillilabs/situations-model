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

void Plugin::registerTypes(const char* uri) {
    // @uri com.pastillilabs.situations.model
#if QT_VERSION >= QT_VERSION_CHECK(5, 9, 0)
    qmlRegisterModule(uri, 1, 0);
#endif
    qmlRegisterSingletonType<Model::Application>(uri, 1, 0, "ApplicationModel", [](QQmlEngine* /*engine*/, QJSEngine* /*scriptEngine*/) -> QObject* {
        return new Model::Application();
    });
    qmlRegisterType<Model::Action>(uri, 1, 0, "ActionModel");
    qmlRegisterType<Model::ActionGroup>(uri, 1, 0, "ActionGroupModel");
    qmlRegisterType<Model::ActionGroupList>(uri, 1, 0, "ActionGroupListModel");
    qmlRegisterType<Model::Condition>(uri, 1, 0, "ConditionModel");
    qmlRegisterType<Model::ConditionGroup>(uri, 1, 0, "ConditionGroup");
    qmlRegisterType<Model::ConditionGroupList>(uri, 1, 0, "ConditionGroupListModel");
    qmlRegisterType<Model::ContactList>(uri, 1, 0, "ContactListModel");
    qmlRegisterType<Model::FeatureList>(uri, 1, 0, "FeatureListModel");
    qmlRegisterType<Model::Feature>(uri, 1, 0, "FeatureModel");
    qmlRegisterType<Model::PackageList>(uri, 1, 0, "PackageListModel");
    qmlRegisterType<Model::Platform>(uri, 1, 0, "PlatformModel");
    qmlRegisterType<Model::Plugin>(uri, 1, 0, "PluginModel");
    qmlRegisterType<Model::Settings>(uri, 1, 0, "SettingsModel");
    qmlRegisterType<Model::Situation>(uri, 1, 0, "SituationModel");
    qmlRegisterType<Model::SituationList>(uri, 1, 0, "SituationListModel");
    qmlRegisterUncreatableType<Model::ActionProperties>(uri, 1, 0, "ActionProperties", QLatin1String("Cannot create ActionProperties instance."));
    qmlRegisterUncreatableType<Model::ConditionProperties>(uri, 1, 0, "ConditionProperties", QLatin1String("Cannot create ConditionProperties instance."));
    qmlRegisterUncreatableType<Model::VersionLimits>(uri, 1, 0, "VersionLimits", QLatin1String("Cannot create VersionLimits instance."));
}
