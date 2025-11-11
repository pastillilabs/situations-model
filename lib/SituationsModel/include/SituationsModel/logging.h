#pragma once

#include <SituationsModel/model_global.h>

#include <QLoggingCategory>

namespace Model {

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
Q_DECLARE_EXPORTED_LOGGING_CATEGORY(category, MODEL_SHARED_EXPORT)
#else
Q_DECLARE_LOGGING_CATEGORY(category)
#endif

} // namespace Model
