CREATE TABLE account
(
    id   TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    clear_amount INT NOT NULL DEFAULT(0)
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
    amount    INT    NOT NULL,
    cleared   BOOLEAN NOT NUlL DEFAULT (FALSE)
);

