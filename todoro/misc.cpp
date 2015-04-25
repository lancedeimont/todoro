#include "misc.h"

QString misc::filesPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::DataLocation);
}

misc::misc()
{

}
