#include "util.h"

#include <QCoreApplication>
#include <QDir>

namespace Model {
namespace Util {

QString pluginPath(const QString& id) {
    const QDir pluginDir(QCoreApplication::applicationDirPath());

    return pluginDir.absoluteFilePath(QStringLiteral(PLUGIN_FILE_TEMPLATE).arg(id));
}

} // namespace Util
} // namespace Model
