SELECT title FROM movies
JOIN stars on stars.movie_id = movies.id
JOIN people on people.id = stars.person_id
WHERE name IN ('Helena Bonham Carter', 'Johnny Depp')
GROUP BY title
HAVING COUNT(title) > 1;