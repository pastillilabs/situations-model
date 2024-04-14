#include "util.h"

#include <QCoreApplication>
#include <QDir>

namespace Model {
namespace Util {

QString pluginPath(const QString& id) {
    const QDir pluginDir(QStringLiteral("/usr/share/harbour-situations2application/lib"));

    return pluginDir.absoluteFilePath(QStringLiteral("libsituations2%1.so").arg(id));
}

} // namespace Util
} // namespace Model
