CREATE TABLE IF NOT EXISTS person_audit
(
    created     timestamp WITH TIME ZONE DEFAULT NOW() NOT NULL,
    type_event  char(1) DEFAULT 'I' NOT NULL
                CONSTRAINT ch_type_event
                    CHECK (type_event IN ('I', 'U', 'D')),
    row_id      bigint NOT NULL,
    name        varchar,
    age         integer,
    gender      varchar,
    address     varchar
);

CREATE OR REPLACE FUNCTION fnc_trg_person_insert_audit() RETURNS TRIGGER AS
$func$
BEGIN
    INSERT INTO person_audit(row_id, name, age, gender, address)
    VALUES (NEW.id, NEW.name, NEW.age, NEW.gender, NEW.address);
    RETURN NEW;
END;
$func$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_person_insert_audit
    AFTER INSERT ON person
    FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_insert_audit();

INSERT INTO person(id, name, age, gender, address) VALUES (10, 'Damir', 22, 'male', 'Irkutsk');
SELECT * FROM person_audit;
