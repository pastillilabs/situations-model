#pragma once

#include <situations-model/model_global.h>
#include <situations-model/action.h>
#include <situations-model/actionproperties.h>
#include <situations-model/condition.h>
#include <situations-model/conditionproperties.h>

#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QUrl>
#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include <QtQml/qqmlregistration.h>
#endif

namespace Model {

/**
 * @brief The Plugin class
 */
class MODEL_SHARED_EXPORT Plugin : public QObject {
    Q_OBJECT
#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QML_ELEMENT
#endif
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QObject* model READ model CONSTANT)
    Q_PROPERTY(bool actionRunning READ isActionRunning WRITE setActionRunning NOTIFY actionRunningChanged)
    Q_PROPERTY(bool conditionRunning READ isConditionRunning WRITE setConditionRunning NOTIFY conditionRunningChanged)
    Q_PROPERTY(QJsonObject stash READ stash WRITE setStash NOTIFY stashChanged)

    Q_PROPERTY(Category category READ category CONSTANT STORED false)
    Q_PROPERTY(Model::ActionProperties actionProperties READ actionProperties CONSTANT STORED false)
    Q_PROPERTY(Model::ConditionProperties conditionProperties READ conditionProperties CONSTANT STORED false)
    Q_PROPERTY(bool controller READ isController NOTIFY controllerChanged STORED false)

public:
    enum class Category {
        CategoryNone,
        CategoryTimeAndLocation,
        CategoryDevice,
        CategoryConnectivity,
        CategoryCommunications,
        CategoryUserInterface,
        CategoryAction
    };
    Q_ENUM(Category)

public:
    explicit Plugin(QObject* parent = nullptr);
    Plugin(const QString& name, Category category, QObject* parent = nullptr);
    virtual ~Plugin() = default;

    const QString& name() const;
    virtual QObject* model() const;

    bool isActionRunning() const;
    void setActionRunning(bool actionRunning);

    bool isConditionRunning() const;
    void setConditionRunning(bool conditionRunning);

    const QJsonObject& stash() const;
    void setStash(const QJsonObject& stash);

    Category category() const;
    const ActionProperties& actionProperties() const;
    const ConditionProperties& conditionProperties() const;
    ActionProperties& actionProperties();
    ConditionProperties& conditionProperties();

    bool isController() const;
    void setController(bool controller);

    virtual void qmlRegisterTypes() const;

    virtual QJsonObject toJson(bool persistent) const;
    virtual void fromJson(const QJsonObject& jsonObject, bool persistent);

    virtual QJsonArray defaults(const QJsonArray& metaData) const;
    virtual QJsonObject systemPayload() const;

    virtual void starting(const Action& action);
    virtual void started(const Action& action);
    virtual void stopping(const Action& action);
    virtual void stopped(const Action& action);

    virtual void execute(const QJsonObject& payload);
    virtual void evaluate(const QVector<Condition*>& conditions);

signals:
    void actionRunningChanged(bool actionRunning);
    void conditionRunningChanged(bool conditionRunning);
    void stashChanged(const QJsonObject& stash);
    void controllerChanged(bool controller);

    // Methods
    void reqEvaluate();

private:
    const QString mName;
    bool mActionRunning{false};
    bool mConditionRunning{false};
    QJsonObject mStash;

    const Category mCategory{Category::CategoryNone};
    ActionProperties mActionProperties;
    ConditionProperties mConditionProperties;
    bool mController{false};
};

} // namespace Model
