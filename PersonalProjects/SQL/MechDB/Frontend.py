import sqlite3

## initiate tables
def init(cur: sqlite3.Cursor) -> bool:
    cur.execute("""CREATE TABLE IF NOT EXISTS roles (
            role TEXT NOT NULL,
            PRIMARY KEY (role)
            )""")

    cur.execute("""CREATE TABLE IF NOT EXISTS mechs (
            chassis TEXT NOT NULL, 
            model   TEXT NOT NULL, 
            weight  INT CHECK (weight >= 20 AND weight <= 100), 
            role    TEXT NOT NULL,
            PRIMARY KEY (chassis, model),
            FOREIGN KEY (role) REFERENCES roles(role)
            )""")

    cur.execute("""CREATE TABLE IF NOT EXISTS speed (
            chassis TEXT,
            model   TEXT,
            walk    INT,
            run     INT AS (round(walk * 1.5, 0)),
            jump    INT,
            PRIMARY KEY (chassis, model),
            FOREIGN KEY (chassis) REFERENCES mechs(chassis),
            FOREIGN KEY (model) REFERENCES mechs(model)
            )""")
    
    return True
    
## Insert an entry into the database
def insert(cur: sqlite3.Cursor, chassis: str, model: str, weight: int, role: str, walk: int, jump: int) -> bool:

    ## Uppercase Text Elements
    chassis = chassis.upper()
    model = model.upper()
    role = role.upper()

    ## Check to see if this mech has a new role. If it does, insert it
    sql = "SELECT * FROM roles"
    args = ()
    cur.execute(sql, args)

    role_list = cur.fetchall()
    role_tuple = (role,)

    if role_tuple not in role_list:
        sql = "INSERT INTO roles(role) VALUES(?)"
        args = (role,)
        cur.execute(sql, args)

    ## Insert into parent tables
    sql = "INSERT INTO mechs(chassis, model, weight, role) VALUES(?, ?, ?, ?)"
    args = (chassis, model, weight, role)
    cur.execute(sql, args)

    sql = "INSERT INTO speed(chassis, model, walk, jump) VALUES(?, ?, ?, ?)"
    args = (chassis, model, walk, jump)
    cur.execute(sql, args)



    return True

## Print contents of tables
def print_tables(cur: sqlite3.Cursor) -> bool:

    cur.execute("SELECT * FROM mechs ORDER BY weight")
    print(cur.fetchall())
    cur.execute("SELECT * FROM speed")
    print(cur.fetchall())
    cur.execute("SELECT * FROM roles")
    print(cur.fetchall())

    return True

def print_mechs(cur: sqlite3.Cursor) -> bool:
    sql = "SELECT * FROM mechs JOIN speed USING(chassis, model) WHERE role = 'SKIRMISHER'"
    args = ()
    cur.execute(sql, args)
    print(cur.fetchall())



########### ENTRY POINT ###########

db = sqlite3.connect("db/mechs.db")

cur = db.cursor()

## initiate tables
init(cur)

## Add some stuff to those tables
insert(cur, "Jagermech", "s", 75, "anti air", 4, 0)
insert(cur, "enforcer", "4r", 50, "skirmisher", 4, 4)
insert(cur, "awesome", "8q", 80, "Fire Support", 3, 0)
insert(cur, "hunchback", "4g", 50, "brawler", 4, 0)
insert(cur, "griffin", "1n", 55, "skirmisher", 5, 3)
insert(cur, "centurion", "1n", 55, "brawler", 4, 0)

## Print the tables
print_mechs(cur)

## Close the DB
db.close()