#pragma once

#include <model/model_global.h>
#include <model/contactlist.h>
#include <model/featurelist.h>
#include <model/packagelist.h>
#include <model/platform.h>
#include <model/settings.h>
#include <model/situationlist.h>

#include <QJsonObject>
#include <QObject>

namespace Model {

/**
 * @brief The Application class
 */
class MODEL_SHARED_EXPORT Application : public QObject {
    Q_OBJECT
    Q_PROPERTY(FeatureList* features READ features CONSTANT)
    Q_PROPERTY(Platform* platform READ platform CONSTANT)
    Q_PROPERTY(Settings* settings READ settings CONSTANT)
    Q_PROPERTY(SituationList* situations READ situations CONSTANT)
    Q_PROPERTY(bool importing READ isImporting WRITE setImporting NOTIFY importingChanged)
    Q_PROPERTY(bool restarting READ isRestarting WRITE setRestarting NOTIFY restartingChanged)
    Q_PROPERTY(int build READ build WRITE setBuild NOTIFY buildChanged)

public:
    static Application* instance();

public:
    explicit Application(QObject* parent = nullptr);
    virtual ~Application();

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
    void reqImport(const QJsonObject& jsonObject);
    void indExport(const QJsonObject& jsonObject);
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
