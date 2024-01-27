import sqlite3

## initiate tables
def init(cur: sqlite3.Cursor):
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
def insert(cur: sqlite3.Cursor, chassis: str, model: str, weight: int, role: str, walk: int, jump: int):

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

    return cur.fetchall()

## Print contents of tables
def print_tables(cur: sqlite3.Cursor):

    cur.execute("SELECT * FROM mechs ORDER BY weight")
    print(cur.fetchall())
    cur.execute("SELECT * FROM speed")
    print(cur.fetchall())
    cur.execute("SELECT * FROM roles")
    print(cur.fetchall())

    return True

def get_mechs(cur: sqlite3.Cursor):
    sql = "SELECT * FROM mechs JOIN speed USING(chassis, model)"
    args = ()
    cur.execute(sql, args)

    return cur.fetchall()



########### ENTRY POINT ###########

db = sqlite3.connect("db/mechs.db")

cur = db.cursor()

## initiate tables
init(cur)

## Add some stuff to those tables by reading from the LIST.txt file
fileinput = open("db/LIST.txt").read().splitlines()

for mechline in fileinput:
    attr = mechline.split()
    insert(cur, attr[0], attr[1], attr[2], attr[3], attr[4], attr[5])

## Print the tables
for mech in get_mechs(cur):
    print(mech)

## Close the DB
db.close()