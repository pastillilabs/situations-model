#pragma once

#include <model/model_global.h>

#include <QJsonObject>
#include <QObject>
#include <QString>

namespace Model {

/**
 * @brief The Condition class
 */
class MODEL_SHARED_EXPORT Condition : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString uid READ uid WRITE setUid NOTIFY uidChanged)
    Q_PROPERTY(QJsonObject payload READ payload WRITE setPayload NOTIFY payloadChanged)
    Q_PROPERTY(int delay READ delay WRITE setDelay NOTIFY delayChanged)
    Q_PROPERTY(ReadyState readyState READ readyState WRITE setReadyState NOTIFY readyStateChanged)
    Q_PROPERTY(bool running READ isRunning WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)

public:
    enum class ReadyState {
        ReadyStateReady,
        ReadyStateAdding,
        ReadyStateEditing
    };
    Q_ENUM(ReadyState)

    enum class Comparison {
        ComparisonLessThan,
        ComparisonMoreThan,
        ComparisonEquals
    };
    Q_ENUM(Comparison)

    enum class OptionalState {
        OptionalStateFalse,
        OptionalStateTrue,
        OptionalStateUndefined
    };
    Q_ENUM(OptionalState)

public:
    Q_INVOKABLE explicit Condition(QObject* parent = nullptr);
    virtual ~Condition() = default;

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

    bool isRunning() const;
    void setRunning(bool running);

    bool isActive() const;
    void setActive(bool active);

signals:
    void uidChanged(const QString& uid);
    void payloadChanged(const QJsonObject& payload);
    void delayChanged(int delay);
    void readyStateChanged(Condition::ReadyState readyState);
    void runningChanged(bool running);
    void activeChanged(bool active);

    // Methods
    void reqCommit(const QJsonObject& payload);
    void reqEdit(bool edit);

private:
    QString mUid;
    QJsonObject mPayload;
    int mDelay{0};
    ReadyState mReadyState{ReadyState::ReadyStateReady};
    bool mRunning{false};
    bool mActive{false};
};

} // namespace Model
