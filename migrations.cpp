#include "migrations.h"
#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <string>

const int max_version = 1;

// The first migration just adds the version table.
const char *m_0 = R"ll(
PRAGMA foreign_keys = ON;
--#--
CREATE TABLE IF NOT EXISTS config (
    key TEXT PRIMARY KEY,
    value TEXT
);
--#--
INSERT INTO config (key, value) VALUES ('db-version', '0')
ON CONFLICT DO NOTHING;
)ll";

const char *m_1 = R"ll(
CREATE TABLE account
(
    id   TEXT PRIMARY KEY,
    name TEXT NOT NULL
);
--#--
CREATE TABLE category
(
    id   TEXT PRIMARY KEY,
    name TEXT NOT NULL
);
--#--
CREATE TABLE entry
(
    id        TEXT PRIMARY KEY,
    account   TEXT   NOT NULL REFERENCES account (id),
    category  TEXT REFERENCES category (id),
    timestamp BIGINT NOT NULL,
    memo      TEXT,
    amount    INT    NOT NULL
);
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
            qFatal() << "Migration Failed" << q.lastError();
            QSqlDatabase::database().rollback();
            QApplication::exit();
            return 1;
        }
    }

    QSqlQuery set_version(
        "UPDATE config SET value = ? WHERE key = 'db-version'");
    set_version.addBindValue(QString::fromStdString(std::to_string(target)));

    bool set_version_ok = set_version.exec();

    if (!set_version_ok) {
        qFatal() << "Failed to set db-version" << set_version.lastError();
        QSqlDatabase::database().rollback();
        QApplication::exit();
        return 1;
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

    if (version >= max_version) {
        return 0;
    }

    qInfo() << "Migrating version from" << version << "to" << max_version;

    migration_version(version, 0);
    migration_version(version, 1);

    return 0;
}
