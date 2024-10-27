#pragma once

#include <situations-model/model_global.h>
#include <situations-model/actiongrouplist.h>
#include <situations-model/conditiongrouplist.h>

#include <QDateTime>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QTime>
#include <QtQml/qqmlregistration.h>

namespace Model {

/**
 * @brief The Situation class
 */
class MODEL_SHARED_EXPORT Situation : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(ActionGroupList* actionGroups READ actionGroups CONSTANT)
    Q_PROPERTY(ConditionGroupList* conditionGroups READ conditionGroups CONSTANT)

    Q_PROPERTY(QString uid READ uid WRITE setUid NOTIFY uidChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QJsonObject metaData READ metaData WRITE setMetaData NOTIFY metaDataChanged)
    Q_PROPERTY(bool manual READ isManual WRITE setManual NOTIFY manualChanged)
    Q_PROPERTY(QDateTime timingStart READ timingStart WRITE setTimingStart NOTIFY timingStartChanged)
    Q_PROPERTY(QTime timingDuration READ timingDuration WRITE setTimingDuration NOTIFY timingDurationChanged)

    Q_PROPERTY(bool proposal READ isProposal WRITE setProposal NOTIFY proposalChanged)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)

public:
    Q_INVOKABLE explicit Situation(QObject* parent = nullptr);
    virtual ~Situation() = default;

    QJsonObject toJson(bool persistent) const;
    void fromJson(const QJsonObject& jsonObject, bool persistent);

    ActionGroupList* actionGroups() const;
    ConditionGroupList* conditionGroups() const;

    const QString& uid() const;
    void setUid(const QString& uid);

    const QString& name() const;
    void setName(const QString& name);

    const QString& icon() const;
    void setIcon(const QString& icon);

    const QJsonObject& metaData() const;
    void setMetaData(const QJsonObject& metaData);

    bool isManual() const;
    void setManual(bool manual);

    const QDateTime& timingStart() const;
    void setTimingStart(const QDateTime& timingStart);

    const QTime& timingDuration() const;
    void setTimingDuration(const QTime& timingDuration);

    bool isProposal() const;
    void setProposal(bool proposal);

    bool isActive() const;
    void setActive(bool active);

signals:
    void uidChanged(const QString& uid);
    void nameChanged(const QString& name);
    void iconChanged(const QString& icon);
    void metaDataChanged(const QJsonObject& metaData);
    void manualChanged(bool manual);
    void timingStartChanged(const QDateTime& timingStart);
    void timingDurationChanged(const QTime& timingDuration);
    void proposalChanged(bool proposal);
    void activeChanged(bool active);

    // Methods
    void reqSetName(const QString& name);
    void reqSetIcon(const QString& icon);
    void reqSetManual(bool manual);
    void reqSetTimingStart(const QDateTime& timingStart);
    void reqSetTimingDuration(const QTime& timingDuration);
    void reqSetActive(bool active);

private:
    ActionGroupList* mActionGroups{nullptr};
    ConditionGroupList* mConditionGroups{nullptr};

    QString mUid;
    QString mName;
    QString mIcon;
    QJsonObject mMetaData;
    bool mManual{false};
    QDateTime mTimingStart;
    QTime mTimingDuration{1, 0}; // Default to 1 hour
    bool mProposal{false};
    bool mActive{false};
};

} // namespace Model
