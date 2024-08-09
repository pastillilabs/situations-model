#pragma once

#include <situations-model/model_global.h>

#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>

namespace Model {

/**
 * @brief The Action class
 */
class MODEL_SHARED_EXPORT Action : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString uid READ uid WRITE setUid NOTIFY uidChanged)
    Q_PROPERTY(QJsonObject payload READ payload WRITE setPayload NOTIFY payloadChanged)
    Q_PROPERTY(int delay READ delay WRITE setDelay NOTIFY delayChanged)
    Q_PROPERTY(ReadyState readyState READ readyState WRITE setReadyState NOTIFY readyStateChanged)
    Q_PROPERTY(RunningState runningState READ runningState WRITE setRunningState NOTIFY runningStateChanged)
    Q_PROPERTY(ActiveState activeState READ activeState WRITE setActiveState NOTIFY activeStateChanged)

public:
    enum class ReadyState {
        ReadyStateReady,
        ReadyStateAdding,
        ReadyStateEditing
    };
    Q_ENUM(ReadyState)

    enum class RunningState {
        RunningStateStarting,
        RunningStateStarted,
        RunningStateStopping,
        RunningStateStopped
    };
    Q_ENUM(RunningState)

    enum class ActiveState {
        ActiveStateActivating,
        ActiveStateActive,
        ActiveStateInactivating,
        ActiveStateInactive
    };
    Q_ENUM(ActiveState)

    enum class OptionalState {
        OptionalStateFalse,
        OptionalStateTrue,
        OptionalStateUndefined
    };
    Q_ENUM(OptionalState)

public:
    Q_INVOKABLE explicit Action(QObject* parent = nullptr);
    virtual ~Action() = default;

    QJsonObject toJson(bool persistent) const;
    void fromJson(const QJsonObject& jsonObject, bool persistent);

    const QString& uid() const;
    void setUid(const QString& uid);

    const QJsonObject& payload() const;
    void setPayload(const QJsonObject& payload);

    int delay() const;
    void setDelay(int delay);

    ReadyState readyState() const;
    void setReadyState(ReadyState readyState);

    RunningState runningState() const;
    void setRunningState(RunningState runningState);

    ActiveState activeState() const;
    void setActiveState(ActiveState activeState);

signals:
    void uidChanged(const QString& uid);
    void payloadChanged(const QJsonObject& payload);
    void delayChanged(int delay);
    void readyStateChanged(Action::ReadyState readyState);
    void runningStateChanged(Action::RunningState runningState);
    void activeStateChanged(Action::ActiveState activeState);

    // Methods
    void reqCommit(const QJsonObject& payload);
    void reqEdit(bool edit);

private:
    QString mUid;
    QJsonObject mPayload;
    int mDelay{0};
    ReadyState mReadyState{ReadyState::ReadyStateReady};
    RunningState mRunningState{RunningState::RunningStateStopped};
    ActiveState mActiveState{ActiveState::ActiveStateInactive};
};

} // namespace Model
