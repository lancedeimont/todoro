#include "misc.h"

QString misc::filesPath()
{
    return QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).back();
}

misc::misc()
{

}
