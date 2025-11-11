#pragma once

#include <SituationsModel/model_global.h>

#include <QObject>
#include <QString>
#include <QStringList>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtQml/qqmlregistration.h>
#else
#define QML_VALUE_TYPE(x)
#endif

namespace Model {

/**
 * @brief The ActionProperties class
 */
class MODEL_SHARED_EXPORT ActionProperties {
    Q_GADGET
    QML_VALUE_TYPE(actionProperties)
    Q_PROPERTY(QStringList permissions READ permissions WRITE setPermissions)
    Q_PROPERTY(QStringList extraPermissions READ extraPermissions WRITE setExtraPermissions)
    Q_PROPERTY(bool callBlocker READ isCallBlocker WRITE setCallBlocker)
    Q_PROPERTY(bool enabler READ isEnabler WRITE setEnabler)
    Q_PROPERTY(bool sequenceable READ isSequenceable WRITE setSequenceable)
    Q_PROPERTY(int delay READ delay WRITE setDelay)
    Q_PROPERTY(int maxCount READ maxCount WRITE setMaxCount)
    Q_PROPERTY(int priority READ priority WRITE setPriority)

public:
    ActionProperties();
    virtual ~ActionProperties() = default;

    bool operator==(const ActionProperties& other) const;
    bool operator!=(const ActionProperties& other) const;
    bool operator<(const ActionProperties& other) const;

    const QStringList& permissions() const;
    void setPermissions(const QStringList& permissions);

    const QStringList& extraPermissions() const;
    void setExtraPermissions(const QStringList& extraPrmissions);

    bool isCallBlocker() const;
    void setCallBlocker(bool callBlocker);

    bool isEnabler() const;
    void setEnabler(bool enabler);

    bool isSequenceable() const;
    void setSequenceable(bool sequenceable);

    int delay() const;
    void setDelay(int delay);

    int maxCount() const;
    void setMaxCount(int maxCount);

    int priority() const;
    void setPriority(int priority);

private:
    QStringList mPermissions;
    QStringList mExtraPermissions;
    bool mCallBlocker{false};
    bool mEnabler{false};
    bool mSequenceable{false};
    int mDelay{0};
    int mMaxCount{1};
    int mPriority{0};
};

} // namespace Model
