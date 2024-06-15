SELECT gs::date AS missing_date
FROM generate_series('2022-1-1', '2022-1-10', interval '1 day') AS gs(day)
    LEFT JOIN person_visits ON (gs.day = visit_date
        AND (person_id = 1 OR person_id = 2))
WHERE person_id IS NULL
ORDER BY missing_date