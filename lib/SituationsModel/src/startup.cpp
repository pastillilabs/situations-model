#include "SituationsModel/startup.h"

namespace Model {

namespace {

QString toString(const QDateTime& dateTime) {
#if QT_VERSION < QT_VERSION_CHECK(5, 8, 0)
    const int msec = dateTime.time().msec();
    const QString isoDate = dateTime.toString(Qt::DateFormat::ISODate);
    const QString isoDateWithMs = QStringLiteral("%1.%2").arg(isoDate).arg(msec, 3, 10, QLatin1Char('0'));

    return dateTime.isNull() ? QString() : isoDateWithMs;
#else
    return dateTime.toString(Qt::DateFormat::ISODateWithMs);
#endif
}

QDateTime fromString(const QString& string) {
    QDateTime dateTime;
#if QT_VERSION < QT_VERSION_CHECK(5, 8, 0)
    dateTime = QDateTime::fromString(string, Qt::DateFormat::ISODate);
#else
    dateTime = QDateTime::fromString(string, Qt::DateFormat::ISODateWithMs);
#endif

    return dateTime;
}

} // namespace

Startup::Startup(QObject* parent)
    : QObject(parent)
    , mActionGroups(new ActionGroupList(this)) {}

QJsonObject Startup::toJson(bool persistent) const {
    if(persistent) {
        QString dateTime;

        return {
            {QLatin1String("actionGroups"), mActionGroups->toJson(persistent)},
            {QLatin1String("dateTime"), toString(mDateTime)},
            {QLatin1String("type"), static_cast<int>(mType)}
        };
    }
    else {
        return {};
    }
}

void Startup::fromJson(const QJsonObject& jsonObject, bool persistent) {
    if(persistent) {
        const QJsonValue actionGroups = jsonObject.value(QLatin1String("actionGroups"));
        const QJsonValue dateTime = jsonObject.value(QLatin1String("dateTime"));
        const QJsonValue type = jsonObject.value(QLatin1String("type"));

        if(!actionGroups.isUndefined()) {
            this->actionGroups()->fromJson(actionGroups.toObject(), persistent);
        }
        if(!dateTime.isUndefined()) {
            setDateTime(fromString(dateTime.toString()));
        }
        if(!type.isUndefined()) {
            setType(static_cast<Type>(type.toInt()));
        }
    }
}

ActionGroupList* Startup::actionGroups() const {
    return mActionGroups;
}

QDateTime Startup::dateTime() const {
    return mDateTime;
}

void Startup::setDateTime(const QDateTime& dateTime) {
    if(dateTime != mDateTime) {
        mDateTime = dateTime;
        emit dateTimeChanged(dateTime);
    }
}

Startup::Type Startup::type() const {
    return mType;
}

void Startup::setType(Type type) {
    if(type != mType) {
        mType = type;
        emit typeChanged(type);
    }
}

} // namespace Model
