#include "migrations.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <string>

const int max_version = 1;

int migrate(int target, QString query_text) {
    auto q_splits = query_text.split("--#--");

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

    for (int i = (version + 1); i <= max_version; i++) {
        auto str = QString(":/sql/%1.sql")
                       .arg(QString::number(i).rightJustified(2, '0'));

        QFile sql_file(str);
        if (sql_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&sql_file);
            QString content = in.readAll();
            sql_file.close();

            // Now you have the file content in the 'content' QString
            migrate(i, content);
        } else {
            qDebug() << "Error opening file: " << sql_file.errorString() << str;
        }
    }

    return 0;
}
