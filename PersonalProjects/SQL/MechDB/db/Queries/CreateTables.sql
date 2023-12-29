CREATE TABLE IF NOT EXISTS mechs (
    chassis TEXT
    model   TEXT
    weight  INT
    PRIMARY KEY (chassis, model)
);

CREATE TABLE IF NOT EXISTS armor (
    chassis TEXT
    model   TEXT
    tons    REAL AS ((h + ct + ctr + rt + rtr + lt + ltr + ra + la + rl + ll) / 16.0)
    h       INT
    ct      INT
    ctr     INT
    rt      INT
    rtr     INT
    lt      INT
    ltr     INT
    ra      INT
    la      INT
    rl      INT
    ll      INT
    PRIMARY KEY (chassis, model)
    FOREIGN KEY (chassis) REFERENCES mechs(chassis)
    FOREIGN KEY (model) REFERENCES mechs(model)
);

CREATE TABLE IF NOT EXISTS speed (
    chassis TEXT
    model   TEXT
    walk    INT
    run     INT AS (ROUND(walk*1.5, 0))
    jump    INT
    PRIMARY KEY (chassis, model)
    FOREIGN KEY (chassis) REFERENCES mechs(chassis)
    FOREIGN KEY (model) REFERENCES mechs(model)
);