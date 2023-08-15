#pragma once

#include <QtCore/qglobal.h>

#if defined(MODEL_LIBRARY)
#  define MODEL_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define MODEL_SHARED_EXPORT Q_DECL_IMPORT
#endif
