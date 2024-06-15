WITH gs AS (SELECT gs::date AS missing_date
FROM generate_series ('2022-01-01', '2022-01-10', '1 day'::interval) gs),
         pv AS (SELECT * FROM person_visits WHERE person_id = 1 OR person_id = 2)
SELECT missing_date
FROM gs LEFT JOIN pv ON pv.visit_date = gs.missing_date
WHERE pv.visit_date IS NULL
ORDER BY missing_date;
