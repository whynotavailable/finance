#pragma once

#define migration_version(current, x) (migrate(current, x, m_##x))

#include <QSqlDatabase>
int migrate_db();
