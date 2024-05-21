#pragma once

#include <situations-model/model_global.h>
#include <situations-model/contactlist.h>
#include <situations-model/featurelist.h>
#include <situations-model/packagelist.h>
#include <situations-model/platform.h>
#include <situations-model/settings.h>
#include <situations-model/situationlist.h>

#include <QJsonObject>
#include <QObject>
#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include <QtQml/qqmlregistration.h>
#endif

namespace Model {

/**
 * @brief The Application class
 */
class MODEL_SHARED_EXPORT Application : public QObject {
    Q_OBJECT
#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QML_ELEMENT
    QML_SINGLETON
#endif
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
