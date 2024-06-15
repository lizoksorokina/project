DROP FUNCTION fnc_persons_female();
DROP FUNCTION fnc_persons_male();

CREATE OR REPLACE FUNCTION fnc_persons(pgender varchar DEFAULT 'female')
    RETURNS TABLE
            (
                id      bigint,
                name    varchar,
                age     integer,
                gender  varchar,
                address varchar
            )
    AS $func$
        SELECT *
        FROM person
        WHERE gender = pgender;
    $func$ LANGUAGE sql;

SELECT *
FROM fnc_persons(pgender := 'male');
SELECT *
FROM fnc_persons();