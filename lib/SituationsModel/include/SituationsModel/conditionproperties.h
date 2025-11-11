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
 * @brief The ConditionProperties class
 */
class MODEL_SHARED_EXPORT ConditionProperties {
    Q_GADGET
    QML_VALUE_TYPE(conditionProperties)
    Q_PROPERTY(QStringList permissions READ permissions WRITE setPermissions)
    Q_PROPERTY(QStringList extraPermissions READ extraPermissions WRITE setExtraPermissions)
    Q_PROPERTY(int maxCount READ maxCount WRITE setMaxCount)
    Q_PROPERTY(int priority READ priority WRITE setPriority)

public:
    ConditionProperties();
    virtual ~ConditionProperties() = default;

    bool operator==(const ConditionProperties& other) const;
    bool operator!=(const ConditionProperties& other) const;
    bool operator<(const ConditionProperties& other) const;

    const QStringList& permissions() const;
    void setPermissions(const QStringList& permissions);

    const QStringList& extraPermissions() const;
    void setExtraPermissions(const QStringList& extraPrmissions);

    int maxCount() const;
    void setMaxCount(int maxCount);

    int priority() const;
    void setPriority(int priority);

private:
    QStringList mPermissions;
    QStringList mExtraPermissions;
    int mMaxCount{1};
    int mPriority{0};
};

} // namespace Model
