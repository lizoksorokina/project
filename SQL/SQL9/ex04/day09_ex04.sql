CREATE OR REPLACE FUNCTION fnc_persons_female()
    RETURNS TABLE
               (id   bigint,
                name    varchar,
                age     integer,
                gender  varchar,
                address varchar)
    AS $func$
        SELECT * FROM person
        WHERE gender = 'female';
    $func$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION fnc_persons_male()
    RETURNS TABLE
            (
                id      bigint,
                name    varchar,
                age     integer,
                gender  varchar,
                address varchar
            )
    AS $fanc$
        SELECT * FROM person
        WHERE gender = 'male';
    $fanc$ LANGUAGE sql;

SELECT * FROM fnc_persons_male();
SELECT * FROM fnc_persons_female();
