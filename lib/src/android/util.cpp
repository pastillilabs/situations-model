#include "util.h"

#include <QCoreApplication>
#include <QDir>

namespace Model {
namespace Util {

QString pluginPath(const QString& id) {
    const QDir pluginDir(QCoreApplication::applicationDirPath());
    return pluginDir.absoluteFilePath(QStringLiteral("libsituations%1_%2.so").arg(id, QStringLiteral(ANDROID_ABI)));
}

} // namespace Util
} // namespace Model
