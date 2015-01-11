#include "util.h"

#include <windows.h>

#include <QApplication>
#include <QRegExp>

namespace Util {

QString VersionFileUrl()
{
    return "http://bakamplayer.u8sand.net/version_windows";
}

bool DimLightsSupported()
{
    return true;
}

void SetAlwaysOnTop(WId wid, bool ontop)
{
    SetWindowPos((HWND)wid,
                 ontop ? HWND_TOPMOST : HWND_NOTOPMOST,
                 0, 0, 0, 0,
                 SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);
}

Settings *InitializeSettings(QObject *parent)
{
    // saves to $(application directory)\${SETTINGS_FILE}.ini
    return new Settings(QString("%0\\%1.ini").arg(QApplication::applicationDirPath(), SETTINGS_FILE), parent);
}

bool IsValidFile(QString path)
{
    QRegExp rx("^(\\.{1,2}|[a-z]:|\\\\\\\\)", Qt::CaseInsensitive); // relative path, network location, drive
    return (rx.indexIn(path) != -1);
}

bool IsValidLocation(QString loc)
{
    QRegExp rx("^([a-z]{2,}://|\\.{1,2}|[a-z]:|\\\\\\\\)", Qt::CaseInsensitive); // url, relative path, network location, drive
    return (rx.indexIn(loc) != -1);
}

QString ShortenPathToParent(const QString &path)
{
    int pos = path.lastIndexOf('\\');
    if(pos != -1)
    {
        pos = path.lastIndexOf('\\', pos-1);
        if(pos != -1)
            return path.mid(pos+1);
    }
    return path;
}

}
