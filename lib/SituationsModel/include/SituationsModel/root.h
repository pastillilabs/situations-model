#pragma once

#include <SituationsModel/model_global.h>
#include <SituationsModel/contactlist.h>
#include <SituationsModel/featurelist.h>
#include <SituationsModel/packagelist.h>
#include <SituationsModel/platform.h>
#include <SituationsModel/settings.h>
#include <SituationsModel/situationlist.h>

#include <QJsonObject>
#include <QObject>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtQml/qqmlregistration.h>
#else
#define QML_ELEMENT
#define QML_SINGLETON
#endif

namespace Model {

/**
 * @brief The Root class
 */
class MODEL_SHARED_EXPORT Root : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(FeatureList* features READ features CONSTANT)
    Q_PROPERTY(Platform* platform READ platform CONSTANT)
    Q_PROPERTY(Settings* settings READ settings CONSTANT)
    Q_PROPERTY(SituationList* situations READ situations CONSTANT)
    Q_PROPERTY(bool importing READ isImporting WRITE setImporting NOTIFY importingChanged)
    Q_PROPERTY(bool restarting READ isRestarting WRITE setRestarting NOTIFY restartingChanged)
    Q_PROPERTY(int build READ build WRITE setBuild NOTIFY buildChanged)

public:
    static Root* instance();

public:
    explicit Root(QObject* parent = nullptr);
    virtual ~Root();

    QJsonObject toJson(bool persistent) const;
    void fromJson(const QJsonObject& jsonObject, bool persistent, const SituationList::Initializer& situationInitializer);

    FeatureList* features() const;
    Platform* platform() const;
    Settings* settings() const;
    SituationList* situations() const;

    bool isImporting() const;
    void setImporting(bool importing);

    bool isRestarting() const;
    void setRestarting(bool restarting);

    int build() const;
    void setBuild(int build);

signals:
    void importingChanged(bool importing);
    void restartingChanged(bool restarting);
    void buildChanged(int build);

    // Methods
    void reqExport();
    void indExport(const QJsonObject& jsonObject);
    void reqImport(const QJsonObject& jsonObject);
    void indImport();
    void reqRestart();

private:
    FeatureList* mFeatures{nullptr};
    Platform* mPlatform{nullptr};
    Settings* mSettings{nullptr};
    SituationList* mSituations{nullptr};

    bool mImporting{false};
    bool mRestarting{false};
    int mBuild{0};
};

} // namespace Model
