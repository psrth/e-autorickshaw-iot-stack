import sqlite3

connection = sqlite3.connect('database.db')

with open('schema.sql') as f:
    connection.executescript(f.read())

cur = connection.cursor()

cur.execute("INSERT INTO sensor_data (speed, pressure, gyro) VALUES (?, ?, ?)",
            ('34', '50', '60')
            )


connection.commit()
connection.close()