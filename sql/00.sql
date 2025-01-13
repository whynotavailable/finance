PRAGMA foreign_keys = ON;
--#--
CREATE TABLE IF NOT EXISTS config (
    key TEXT PRIMARY KEY,
    value TEXT
);
--#--
INSERT INTO config (key, value) VALUES ('db-version', '0')
ON CONFLICT DO NOTHING;
