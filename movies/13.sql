SELECT name

  FROM people
       JOIN stars
       ON stars.person_id = people.id

 WHERE movie_id IN

       (SELECT movie_id
          FROM stars
               JOIN people
               ON stars.person_id = people.id
         WHERE name = 'Kevin Bacon'
           AND birth = 1958)

   AND NOT id IN

       (SELECT id
          FROM people
         WHERE name = 'Kevin Bacon'
           AND birth = 1958)

 ORDER BY name ASC;