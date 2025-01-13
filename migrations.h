#pragma once

#define migration_version(x) (migrate(version, x, m_##x))

#include <QSqlDatabase>
int migrate_db();
