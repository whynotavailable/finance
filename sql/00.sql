PRAGMA foreign_keys = ON;
--#--
CREATE TABLE config (
    key TEXT PRIMARY KEY,
    value TEXT
);
--#--
INSERT INTO config (key, value) VALUES ('db-version', '0')
ON CONFLICT DO NOTHING;
