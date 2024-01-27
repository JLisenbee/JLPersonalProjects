import sqlite3
from tkinter import *
from tkinter import ttk

## Reloads the mechs from the input file
def load_mechs():
    fileinput = open("db/LIST.txt").read().splitlines()
    for mechline in fileinput:
        attr = mechline.split()
        insert(cur, attr[0], attr[1], attr[2], attr[3], attr[4], attr[5])

## initiate the database
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

    load_mechs()

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

## Query DB to get all the mechs
def get_mechs(cur: sqlite3.Cursor):
    sql = "SELECT * FROM mechs JOIN speed USING(chassis, model) ORDER BY chassis, model"
    args = ()
    cur.execute(sql, args)

    return cur.fetchall()




########### ENTRY POINT ###########
db = sqlite3.connect("db/mechs.db")
cur = db.cursor()

## initiate tables
init(cur)

## TK window
root = Tk()
root.geometry("500x500")
frm = ttk.Frame(root)
frm.grid()
ttk.Button(frm, text="Quit", command=root.destroy).grid(column=0, row=0)

chassis = StringVar()
model = StringVar()
weight = StringVar()
role = StringVar()
walk = StringVar()
jump = StringVar()
output = StringVar()

ttk.Label(frm, text="Chassis", width=10).grid(column=0, row=1)
Entry(frm, textvariable = chassis).grid(column=1, row=1)

ttk.Label(frm, text="Model", width=10).grid(column=0, row=2)
Entry(frm, textvariable = model).grid(column=1, row=2)

ttk.Label(frm, text="Weight", width=10).grid(column=0, row=3)
Entry(frm, textvariable = weight).grid(column=1, row=3)

ttk.Label(frm, text="Role", width=10).grid(column=0, row=4)
Entry(frm, textvariable = role).grid(column=1, row=4)

ttk.Label(frm, text="Walk", width=10).grid(column=0, row=5)
Entry(frm, textvariable = walk).grid(column=1, row=5)

ttk.Label(frm, text="Jump", width=10).grid(column=0, row=6)
Entry(frm, textvariable = jump).grid(column=1, row=6)

Label(frm, width=10, textvariable= output).grid(column=0, row=8)

def insert_from_gui():
    insert(cur, chassis.get(), model.get(), int(weight.get()), role.get(), int(walk.get()), int(jump.get()))
    output.set("Submitted")

    

ttk.Button(frm, text="Submit", command=insert_from_gui).grid(column=0, row=7)

root.mainloop()



## Print the tables
for mech in get_mechs(cur):
    print(mech)

## Close the DB
db.commit()
db.close()