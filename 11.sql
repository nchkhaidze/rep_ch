SELECT title FROM movies
JOIN stars on stars.movie_id = movies.id
JOIN people on people.id = stars.person_id
JOIN ratings on ratings.movie_id = movies.id
WHERE people.name = 'Chadwick Boseman'
ORDER BY rating DESC
LIMIT 5;
