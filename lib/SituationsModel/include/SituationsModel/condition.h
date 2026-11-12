#pragma once

#include <SituationsModel/model_global.h>

#include <QDateTime>
#include <QJsonObject>
#include <QObject>
#include <QString>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtQml/qqmlregistration.h>
#else
#define QML_ELEMENT
#endif

namespace Model {

/**
 * @brief The Condition class
 */
class MODEL_SHARED_EXPORT Condition : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString uid READ uid WRITE setUid NOTIFY uidChanged)
    Q_PROPERTY(QJsonObject payload READ payload WRITE setPayload NOTIFY payloadChanged)
    Q_PROPERTY(QJsonObject settings READ settings WRITE setSettings NOTIFY settingsChanged)
    Q_PROPERTY(ReadyState readyState READ readyState WRITE setReadyState NOTIFY readyStateChanged)
    Q_PROPERTY(QDateTime running READ running WRITE setRunning NOTIFY runningChanged)
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

    void clone(const Condition& source);

    const QString& uid() const;
    void setUid(const QString& uid);

    const QJsonObject& payload() const;
    void setPayload(const QJsonObject& payload);

    const QJsonObject& settings() const;
    void setSettings(const QJsonObject& settings);

    ReadyState readyState() const;
    void setReadyState(ReadyState readyState);

    QDateTime running() const;
    void setRunning(const QDateTime& running);

    bool isActive() const;
    void setActive(bool active);

signals:
    void uidChanged(const QString& uid);
    void payloadChanged(const QJsonObject& payload);
    void settingsChanged(const QJsonObject& settings);
    void readyStateChanged(Model::Condition::ReadyState readyState);
    void runningChanged(QDateTime running);
    void activeChanged(bool active);

    // Methods
    void reqCommit(const QJsonObject& payload);
    void reqEdit(bool edit);
    void reqEvaluate();

private:
    QString mUid;
    QJsonObject mPayload;
    QJsonObject mSettings;
    ReadyState mReadyState{ReadyState::ReadyStateReady};
    QDateTime mRunning;
    bool mActive{false};
};

} // namespace Model
