CREATE TABLE genres(
    id SERIAL PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    description VARCHAR(500)
);

CREATE TABLE books(
    id SERIAL PRIMARY KEY,
    title VARCHAR(120) NOT NULL,
    author VARCHAR(80),
    year_of_release INT,
    location_code VARCHAR(50),
    id_genre INT REFERENCES genres(id) ON DELETE RESTRICT
);

CREATE TABLE book_copies (
    id SERIAL PRIMARY KEY,
    condition VARCHAR(10) CHECK (condition IN ('poor', 'average', 'good', 'new')) NOT NULL,
    id_book INT REFERENCES books(id) ON DELETE RESTRICT
);

CREATE TABLE readers (
    id SERIAL PRIMARY KEY,
    name VARCHAR(30),
    surname VARCHAR(50),
    phone_number VARCHAR(15) UNIQUE,
    email VARCHAR(150) UNIQUE
);

CREATE TABLE loans(
    id SERIAL PRIMARY KEY,
    reader_id INT REFERENCES readers(id) ON DELETE RESTRICT,
    book_copies_id INT REFERENCES book_copies(id) ON DELETE RESTRICT,
    loan_date DATE DEFAULT CURRENT_DATE,
    return_date DATE NULL,
    is_returned BOOLEAN DEFAULT FALSE
);