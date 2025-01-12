#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

const int version = 1;

// The first migration just adds the version table.
const char *m_00 = R"ll(
CREATE TABLE IF NOT EXISTS config (
    key TEXT PRIMARY KEY,
    value TEXT
);
--#--
INSERT INTO config (key, value) VALUES ('db-version', '0')
ON CONFLICT DO NOTHING;
)ll";

int migrate(int current, int target, const char *query_text) {
    if (current >= target) {
        return 0;
    }

    auto q_splits = QString(query_text).split("--#--");

    QSqlDatabase::database().transaction();

    foreach (auto query, q_splits) {
        int r;
        if (query.trimmed().isEmpty()) {
            continue;
        }

        QSqlQuery q;
        r = q.exec(query);

        if (!r) {
            qDebug() << q.lastError();
            QSqlDatabase::database().rollback();
            return 1;
        }
    }

    QSqlDatabase::database().commit();

    return 1;
}

int get_version() {
    int r;
    QSqlQuery q;

    r = q.exec("SELECT value FROM config WHERE key = 'db-version';");
    if (!r && q.lastError().databaseText().contains("config")) {
        return -1;
    } else if (q.next()) {
        return q.value("value").toString().toInt();
    }

    qDebug() << "Something is totally broke.";
    return 9999;
}

int migrate_db() {
    int version = get_version();
    qInfo() << "Current Db Version" << version;

    migrate(version, 0, m_00);

    return 0;
}
