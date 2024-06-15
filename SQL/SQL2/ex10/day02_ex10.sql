SELECT t1.name AS person_name1,
    t2.name AS person_name2,
    t1.address AS common_adress
FROM person t1,
    person t2
WHERE t1.address = t2.address
    AND t1.id > t2.id
ORDER BY person_name1, person_name2, common_adress