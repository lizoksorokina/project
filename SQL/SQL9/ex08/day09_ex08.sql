CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop int DEFAULT 10)
    RETURNS SETOF integer
    AS $func$
        WITH RECURSIVE fibonacci(a, b) AS (
            VALUES (0, 1)
        UNION ALL
            SELECT b, a + b FROM fibonacci
            WHERE b < pstop)
        SELECT a FROM fibonacci;
    $func$ LANGUAGE sql;

SELECT * FROM fnc_fibonacci(100);
SELECT * FROM fnc_fibonacci();
