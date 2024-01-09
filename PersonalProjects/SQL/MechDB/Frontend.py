import sqlite3
from tkinter import *
from tkinter import ttk

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

## Add some stuff to those tables
insert(cur, "Jagermech", "s", 75, "anti air", 4, 0)
insert(cur, "enforcer", "4r", 50, "skirmisher", 4, 4)
insert(cur, "awesome", "8q", 80, "Fire Support", 3, 0)
insert(cur, "hunchback", "4g", 50, "brawler", 4, 0)
insert(cur, "griffin", "1n", 55, "skirmisher", 5, 5)
insert(cur, "centurion", "A", 55, "brawler", 4, 0)

root = Tk()
frame = ttk.Frame(root, padding = 10)
frame.grid()
ttk.Label(frame, text="Name", font="Courier 24 bold").grid(column=0, row=0, padx=10, pady=10, columnspan=2)        ## Combined Chassis and Model
ttk.Label(frame, text="Tonnage", font="Courier 24 bold").grid(column=2, row=0, padx=10, pady=10, columnspan=2)     
ttk.Label(frame, text="Role", font="Courier 24 bold").grid(column=4, row=0, padx=10, pady=10, columnspan=2)
ttk.Label(frame, text="Movement", font="Courier 24 bold").grid(column=6, row=0, padx=10, pady=10, columnspan=2)    ## Combined Walk/Run/Jump

i = 1
for mech in get_mechs(cur):
    ttk.Label(frame, text=mech[0] + "-" + mech[1], font="Courier 18").grid(column=0, row=i, padx=5, pady=5, sticky=W, columnspan=2)
    ttk.Label(frame, text=mech[2], font="Courier 18").grid(column=2, row=i, padx=5, pady=5, columnspan=2)
    ttk.Label(frame, text=mech[3], font="Courier 18").grid(column=4, row=i, padx=5, pady=5, columnspan=2)
    ttk.Label(frame, text=str(mech[4]) + "/" + str(mech[5]) + "/" + str(mech[6]), font="Courier 18").grid(column=6, row=i, padx=5, pady=5, columnspan=2)
    i+=1

## Button and text boxes to make more
chassis = ""
model = ""
weight = 0
role = ""
walk = 0
jump = 0

def new_entry():
    insert(cur, chassis, model, weight, role, walk, jump)
chassis_text = Entry(frame, font="Courier 18", textvariable=chassis).grid(column=0, row=i, sticky=W)
model_text = Entry(frame, font="Courier 18", textvariable=model).grid(column=1, row=i, sticky=E)
weight_text = Entry(frame, font="Courier 18", textvariable=weight).grid(column=2, row=i, columnspan=2)
role_text = Entry(frame, font="Courier 18", textvariable=role).grid(column=4, row=i, columnspan=2)
walk_text = Entry(frame, font="Courier 18", textvariable=walk).grid(column=6, row=i, sticky=W)
jump_text = Entry(frame, font="Courier 18", textvariable=jump).grid(column=7, row=i, sticky=E)
new_button = Button(frame, text="Enter", font="Courier 18", command=new_entry).grid(column=8, row=i)

root.mainloop()

## Print the tables
for mech in get_mechs(cur):
    print(mech)

## Close the DB
db.close()