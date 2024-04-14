#include "util.h"

#include <QCoreApplication>
#include <QDir>

namespace Model {
namespace Util {

QString pluginPath(const QString& id) {
    QDir pluginDir(QCoreApplication::applicationDirPath());

#ifdef QT_DEBUG
    pluginDir.cd(QStringLiteral("../../plugins/%1/debug").arg(id));
#else
    pluginDir.cd(QStringLiteral("../../plugins/%1/release").arg(id));
#endif // QT_DEBUG

    return pluginDir.absoluteFilePath(QStringLiteral("situations2%1.dll").arg(id));
}

} // namespace Util
} // namespace Model
