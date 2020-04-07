SELECT name FROM people WHERE id IN
(SELECT DISTINCT id FROM people JOIN stars ON people.id = stars.person_id
WHERE stars.movie_id IN
(SELECT id FROM movies WHERE year = '2004'));