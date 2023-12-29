import sqlite3

db = sqlite3.connect("db/mechs.db")

cur = db.cursor()

## Build Tables if they don't exist already
cur.execute("""CREATE TABLE IF NOT EXISTS mechs (
            chassis TEXT, 
            model   TEXT, 
            weight  INT, 
            PRIMARY KEY (chassis, model)
            )""")

cur.execute("""CREATE TABLE IF NOT EXISTS armor (
            chassis TEXT,
            model   TEXT,
            tons    REAL AS ((h + ct + ctr + rt + rtr + lt + ltr + ra + la + rl + ll) / 16.0),
            h       INT,
            ct      INT,
            ctr     INT,
            rt      INT,
            rtr     INT,
            lt      INT,
            ltr     INT,
            ra      INT,
            la      INT,
            rl      INT,
            ll      INT,
            PRIMARY KEY (chassis, model),
            FOREIGN KEY (chassis) REFERENCES mechs(chassis),
            FOREIGN KEY (model) REFERENCES mechs(model)
            )""")

cur.execute("""CREATE TABLE IF NOT EXISTS speed (
            chassis TEXT
            model   TEXT
            walk    INT
            run     INT
            jump    INT
            PRIMARY KEY (chassis, model)
            FOREIGN KEY (chassis) REFERENCES mechs(chassis)
            FOREIGN KEY (model) REFERENCES mechs(model)
            )""")

## Add some stuff to those tables
cur.execute("INSERT INTO mechs(chassis, model) VALUES('JAGERMECH','DG')")
cur.execute("INSERT INTO armor(chassis, model, h, ct, ctr, rt, rtr, lt, ltr, ra, la, rl, ll) VALUES('JAGERMECH','DG', 9, 18, 5, 17, 5, 17, 5, 8, 8, 12, 12)")

## Print the tables
cur.execute("SELECT * FROM mechs")
print(cur.fetchall())
cur.execute("SELECT * FROM armor")
print(cur.fetchall())
cur.execute("SELECT * FROM speed")
print(cur.fetchall())

## Close the DB
db.close()