CREATE SEQUENCE seq_person_discounts START 1; --создание последовательности для вычисления айди для любой н.к
ALTER TABLE person_discounts --изменение таблицы
ALTER COLUMN id -- изменение какой колонки
SET DEFAULT nextval('seq_person_discounts'); --устанавливает базовое которое возвращает функция некствал возвращая значение ++

SELECT setval('seq_person_discounts', ( -- устанавливает счетчик на знач ниже
SELECT COUNT(*) + 1 FROM person_discounts));
