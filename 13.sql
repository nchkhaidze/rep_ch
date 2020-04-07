SELECT DISTINCT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE stars.movie_id IN (SELECT stars.movie_id FROM stars WHERE stars.person_id IN
(SELECT people.id FROM people WHERE name = 'Kevin Bacon' AND birth = '1958'))
AND people.name <> 'Kevin Bacon';