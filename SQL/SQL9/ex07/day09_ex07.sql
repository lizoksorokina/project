CREATE OR REPLACE FUNCTION func_minimum(arr numeric[])
RETURNS numeric
LANGUAGE sql
AS $func$
    SELECT MIN(val)
    FROM unnest(arr) AS val;
$func$;

SELECT func_minimum(ARRAY[10.0, -1.0, 5.0, 4.4]);