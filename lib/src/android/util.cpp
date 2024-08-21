#include "util.h"

#include <QCoreApplication>
#include <QDir>

namespace Model {
namespace Util {

QString pluginPath(const QString& id) {
    const QDir pluginDir(QCoreApplication::applicationDirPath());

    return pluginDir.absoluteFilePath(QStringLiteral("libsituations%1.so").arg(id));
}

} // namespace Util
} // namespace Model
