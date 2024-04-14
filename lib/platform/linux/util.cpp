#include "util.h"

#include <QCoreApplication>
#include <QDir>

namespace Model {
namespace Util {

QString pluginPath(const QString& id) {
    QDir pluginDir(QCoreApplication::applicationDirPath());
    pluginDir.cd(QStringLiteral("../plugins/%1").arg(id));

    return pluginDir.absoluteFilePath(QStringLiteral("libsituations2%1.so").arg(id));
}

} // namespace Util
} // namespace Model
