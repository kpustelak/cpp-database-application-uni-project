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

INSERT INTO genres (name, description)
SELECT 'Fantasy', 'Magic, mythical creatures and epic quests'
WHERE NOT EXISTS (SELECT 1 FROM genres WHERE name = 'Fantasy');

INSERT INTO genres (name, description)
SELECT 'Science Fiction', 'Technology, space travel and futuristic worlds'
WHERE NOT EXISTS (SELECT 1 FROM genres WHERE name = 'Science Fiction');

INSERT INTO genres (name, description)
SELECT 'Crime', 'Detective stories and criminal investigations'
WHERE NOT EXISTS (SELECT 1 FROM genres WHERE name = 'Crime');

INSERT INTO genres (name, description)
SELECT 'History', 'Books focused on historical events and biographies'
WHERE NOT EXISTS (SELECT 1 FROM genres WHERE name = 'History');

INSERT INTO books (title, author, year_of_release, location_code, id_genre)
SELECT 'The Hobbit', 'J.R.R. Tolkien', 1937, 'FAN-A1-01', g.id
FROM genres g
WHERE g.name = 'Fantasy'
  AND NOT EXISTS (
      SELECT 1
      FROM books b
      WHERE b.title = 'The Hobbit' AND b.author = 'J.R.R. Tolkien'
  );

INSERT INTO books (title, author, year_of_release, location_code, id_genre)
SELECT 'Dune', 'Frank Herbert', 1965, 'SCI-B2-03', g.id
FROM genres g
WHERE g.name = 'Science Fiction'
  AND NOT EXISTS (
      SELECT 1
      FROM books b
      WHERE b.title = 'Dune' AND b.author = 'Frank Herbert'
  );

INSERT INTO books (title, author, year_of_release, location_code, id_genre)
SELECT 'The Hound of the Baskervilles', 'Arthur Conan Doyle', 1902, 'CRI-C3-02', g.id
FROM genres g
WHERE g.name = 'Crime'
  AND NOT EXISTS (
      SELECT 1
      FROM books b
      WHERE b.title = 'The Hound of the Baskervilles' AND b.author = 'Arthur Conan Doyle'
  );

INSERT INTO books (title, author, year_of_release, location_code, id_genre)
SELECT 'Sapiens', 'Yuval Noah Harari', 2011, 'HIS-D1-04', g.id
FROM genres g
WHERE g.name = 'History'
  AND NOT EXISTS (
      SELECT 1
      FROM books b
      WHERE b.title = 'Sapiens' AND b.author = 'Yuval Noah Harari'
  );

INSERT INTO book_copies (condition, id_book)
SELECT 'new', b.id
FROM books b
WHERE b.title = 'The Hobbit'
  AND NOT EXISTS (
      SELECT 1 FROM book_copies bc WHERE bc.id_book = b.id AND bc.condition = 'new'
  );

INSERT INTO book_copies (condition, id_book)
SELECT 'good', b.id
FROM books b
WHERE b.title = 'The Hobbit'
  AND NOT EXISTS (
      SELECT 1 FROM book_copies bc WHERE bc.id_book = b.id AND bc.condition = 'good'
  );

INSERT INTO book_copies (condition, id_book)
SELECT 'average', b.id
FROM books b
WHERE b.title = 'Dune'
  AND NOT EXISTS (
      SELECT 1 FROM book_copies bc WHERE bc.id_book = b.id AND bc.condition = 'average'
  );

INSERT INTO book_copies (condition, id_book)
SELECT 'good', b.id
FROM books b
WHERE b.title = 'The Hound of the Baskervilles'
  AND NOT EXISTS (
      SELECT 1 FROM book_copies bc WHERE bc.id_book = b.id AND bc.condition = 'good'
  );

INSERT INTO book_copies (condition, id_book)
SELECT 'new', b.id
FROM books b
WHERE b.title = 'Sapiens'
  AND NOT EXISTS (
      SELECT 1 FROM book_copies bc WHERE bc.id_book = b.id AND bc.condition = 'new'
  );

INSERT INTO readers (name, surname, phone_number, email)
SELECT 'Jan', 'Kowalski', '500100200', 'jan.kowalski@example.com'
WHERE NOT EXISTS (SELECT 1 FROM readers WHERE phone_number = '500100200');

INSERT INTO readers (name, surname, phone_number, email)
SELECT 'Anna', 'Nowak', '500300400', 'anna.nowak@example.com'
WHERE NOT EXISTS (SELECT 1 FROM readers WHERE phone_number = '500300400');

INSERT INTO readers (name, surname, phone_number, email)
SELECT 'Piotr', 'Wisniewski', '500500600', 'piotr.wisniewski@example.com'
WHERE NOT EXISTS (SELECT 1 FROM readers WHERE phone_number = '500500600');

INSERT INTO readers (name, surname, phone_number, email)
SELECT 'Katarzyna', 'Wojcik', '500700800', 'katarzyna.wojcik@example.com'
WHERE NOT EXISTS (SELECT 1 FROM readers WHERE phone_number = '500700800');

INSERT INTO loans (reader_id, book_copies_id, loan_date, return_date, is_returned)
SELECT r.id, bc.id, CURRENT_DATE - INTERVAL '7 days', NULL, FALSE
FROM readers r
JOIN books b ON b.title = 'The Hobbit'
JOIN book_copies bc ON bc.id_book = b.id
WHERE r.phone_number = '500100200'
  AND bc.condition = 'new'
  AND NOT EXISTS (
      SELECT 1
      FROM loans l
      WHERE l.reader_id = r.id
        AND l.book_copies_id = bc.id
        AND l.is_returned = FALSE
  );

INSERT INTO loans (reader_id, book_copies_id, loan_date, return_date, is_returned)
SELECT r.id, bc.id, CURRENT_DATE - INTERVAL '20 days', CURRENT_DATE - INTERVAL '5 days', TRUE
FROM readers r
JOIN books b ON b.title = 'Dune'
JOIN book_copies bc ON bc.id_book = b.id
WHERE r.phone_number = '500300400'
  AND bc.condition = 'average'
  AND NOT EXISTS (
      SELECT 1
      FROM loans l
      WHERE l.reader_id = r.id
        AND l.book_copies_id = bc.id
        AND l.is_returned = TRUE
  );

-- Active overdue loan (borrowed 40 days ago, still not returned)
INSERT INTO loans (reader_id, book_copies_id, loan_date, return_date, is_returned)
SELECT r.id, bc.id, CURRENT_DATE - INTERVAL '40 days', NULL, FALSE
FROM readers r
JOIN books b ON b.title = 'Sapiens'
JOIN book_copies bc ON bc.id_book = b.id
WHERE r.phone_number = '500700800'
  AND bc.condition = 'new'
  AND NOT EXISTS (
      SELECT 1
      FROM loans l
      WHERE l.reader_id = r.id
        AND l.book_copies_id = bc.id
        AND l.is_returned = FALSE
  );cd