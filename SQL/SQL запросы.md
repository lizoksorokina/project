# Вводная информация об объекте исследования
Вы будете работать с данными, которые собираются с самосвалов, перевозящих породу (например, уголь) на карьере. На самосвалах стоят датчики, которые собирают множество различной информации (скорость, высота, расход топлива и тд). Данные с каждого датчика приходят вместе с временной меткой, идентификатором самосвала и его местоположением (координатами) в момент получения значения с датчика.

Сам по себе карьер состоит из пунктов погрузки (откуда вывозят породу), пунктов разгрузки (куда её отвозят) и маршрутов между ними. На картинке показан пример исходных данных координат самосвалов (синие точки) и примерных дорог на карьере (фиолетовые). Пункты погрузки и разгрузки на картинке не указаны.

Одним рейсом самосвала называется его движение от пункта погрузки до пункта разгрузки и обратно до пункта погрузки.

![](https://drive.google.com/uc?export=view&id=1QLscdUpjOGU8m9WvN8ulKdC9YBWJyKw4)

# Часть 1. SQL

Дана упрощенная схема базы данных:

![](https://drive.google.com/uc?export=view&id=1eZVg0OMLNh3Zn4Ss00oNw6KtcMYMTtdZ)

**telemetry** - таблица с телеметрией карьерных самосвалов следующего формата:

| id | objectid | time | sensorid | value | lat | lon | speed|
| :-: |:-: |:-: |:-: |:-: |:-: |:-: |:-: |
| 42 | 123 | 01.01.2024 | 21:00:54 | 35 | 85,694 | 51.384 | 41.857 | 15.81 |

где
* id - номер записи в таблице
* objectid - идентификатор самосвала
* time - момент времени
* sensorid - идентификатор датчика
* value - значение, которое передал датчик
* lat, lon - координаты
* speed - текущая скорость самосвала

**objects** - таблица, в которой хранится информация о самосвалах:

| id | modelname | enterprise_id | created_at |
| :-: |:-: |:-: |:-: |
| 123 | БелАЗ-75131 | 4 | 01.01.2024 | 00:00:00 |

где
* id - идентификатор самосвала
* modelname - модель самосвала
* enterprise_id - идентификатор предприятия
* created_at - временная метка создания записи

**sensors** - таблица с описанием датчиков:

| id | name | tag | min_value | max_value |
| :-: |:-: |:-: |:-: | :-: |
| 35 | Вес | weight | 0 | 180 |

где
* id - идентификатор датчика
* name - наименование датчика
* tag - тег датчика
* min_value - минимальное допустимое значение датчика
* max_value - максимальное допустимое значение датчика


## Задание 1
Необходимо написать запрос, который для каждого самосвала модели “БелАЗ-75320” на предприятии с id = 6 выведет процент количества записей телеметрии, когда значение тега высоты (height) находилось в допустимых пределах, относительно всех записей по данному датчику за последние сутки.


```python
WITH correct AS (
    SELECT
        o.id AS objectid,
        t.id,
        COUNT(*) AS amount
    FROM
        objects AS o
    JOIN
        telemetry AS t ON o.id = t.objectid
    JOIN
        sensors AS s ON t.sensorid = s.id
    WHERE
        o.modelname = 'БелАЗ-75320'
        AND o.enterprise_id = 6
        AND t.time >= NOW() - INTERVAL 1 DAY
        AND t.value BETWEEN s.min_value AND s.max_value
        AND s.tag = 'height'
    GROUP BY
        o.id, t.id
),
all_data AS (
    SELECT
        o.id AS objectid,
        t.id,
        COUNT(*) AS amount
    FROM
        objects AS o
    JOIN
        telemetry AS t ON o.id = t.objectid
    JOIN
        sensors AS s ON t.sensorid = s.id
    WHERE
        t.time >= NOW() - INTERVAL 1 DAY
        AND s.tag = 'height'
    GROUP BY
        o.id, t.id
)
SELECT
    c.objectid,
    c.id,
    c.amount / a.amount AS percentage_valid
FROM
    correct c
LEFT JOIN
    all_data a ON a.objectid = c.objectid AND a.id = c.id;

```

 Задание 2
Необходимо написать запрос, для вывода уникальных значений по датчику satenum (количество доступных спутников связи) для каждого самосвала с идентификатором из списка [34, 42, 99] за последние двое суток.



SELECT
    t.objectid,
    t.sensorid,
    t.value,
    t.time 
FROM
    telemetry t
JOIN
    sensors s ON t.sensorid = s.id
WHERE
    t.objectid IN (34, 42, 99)
    AND t.time >= NOW() - INTERVAL 2 DAY
    AND s.tag = 'satenum'
GROUP BY
    t.objectid, t.sensorid, t.value, t.time;









SELECT
    t.objectid,
    t.sensorid,
    t.value,
    t.time 
FROM
    telemetry t
JOIN
    sensors s ON t.sensorid = s.id
WHERE
    t.objectid IN (34, 42, 99)
    AND t.time >= NOW() - INTERVAL 2 DAY
    AND s.tag = 'satenum'
GROUP BY
    t.objectid, t.sensorid, t.value, t.time;







## Задание 3
В таблицу с телеметрией собираются данные с датчика уровня топлива в процентах (тег fuel_tank_level). В данной задаче будем считать, что самосвалы в течение последнего часа ездят непрерывно, а значит и уровень топлива постепенно снижается. Необходимо написать запрос, который для каждого самосвала модели “БелАЗ-75131” вернет 1, если был зафиксирован хоть один случай, когда между двумя последовательными временными точками изменение уровня топлива было более 5%, или вывести 0, если подобной аномалии не было.


```python
SELECT
    t.objectid,
    CASE
        WHEN ABS(t.value - LAG(t.value) OVER (ORDER BY t.time)) > 5 THEN 1
        ELSE 0
    END AS была_аномалия
FROM
    telemetry t
JOIN
    objects o ON t.objectid = o.id
JOIN
    sensors s ON t.sensorid = s.id
WHERE
    o.modelname = 'БелАЗ-75131'
    AND s.tag = 'fuel_tank_level'
    AND t.time >= NOW() - INTERVAL 1 HOUR
GROUP BY
    t.objectid;

```
