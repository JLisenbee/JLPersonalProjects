import sqlite3

db = sqlite3.connect("db/mechs.db")

cur = db.cursor()

## 

db.close()