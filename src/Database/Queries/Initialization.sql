CREATE TABLE `Albums` (
    `id` int PRIMARY KEY,
    `name` string,
    `artist` string,
    `tags` string
);

CREATE TABLE `Song` (
    `id` int PRIMARY KEY,
    `name` string NOT NULL,
    `file_id` int NOT NULL
);

CREATE TABLE `Movies` (
    `id` int PRIMARY KEY,
    `name` string NOT NULL,
    `tags` string NOT NULL,
    `file_id` int NOT NULL
);

CREATE TABLE `Files` (
    `file_id` int PRIMARY KEY,
    `location` string NOT NULL,
    `filename` string NOT NULL
);
