#pragma once

#include <SituationsModel/model_global.h>

#include <QObject>
#include <QtQml/qqmlregistration.h>

namespace Model {

/**
 * @brief The VersionLimits class
 */
class MODEL_SHARED_EXPORT VersionLimits {
    Q_GADGET
    QML_VALUE_TYPE(versionLimits)
    Q_PROPERTY(int min READ min WRITE setMin)
    Q_PROPERTY(int max READ max WRITE setMax)
    Q_PROPERTY(int rootMin READ rootMin WRITE setRootMin)
    Q_PROPERTY(int rootMax READ rootMax WRITE setRootMax)

public:
    Q_INVOKABLE VersionLimits() = default;
    VersionLimits(int min, int max);
    VersionLimits(int min, int max, int rootMin, int rootMax);

    bool operator==(const VersionLimits& other) const;
    bool operator!=(const VersionLimits& other) const;
    bool operator<(const VersionLimits& other) const;

    int min() const;
    void setMin(int min);

    int max() const;
    void setMax(int max);

    int rootMin() const;
    void setRootMin(int rootMin);

    int rootMax() const;
    void setRootMax(int rootMax);

private:
    int mMin{-1};
    int mMax{-1};
    int mRootMin{-1};
    int mRootMax{-1};
};

} // namespace Model
