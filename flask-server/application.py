from flask import Flask, render_template, request
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route("/")
def index():
    return render_template('index.html')

@app.route("/aws_iot_post", methods=["POST"])
def aws_iot_post():
    if request.method == "POST":
        print(request.json)
        connection = sqlite3.connect('database.db')

        cur = connection.cursor()

        cur.execute("INSERT INTO sensor_data (speed, pressure, gyro) VALUES (?, ?, ?)",
                    (request.json["speed"], request.json["pressure"], request.json["gyro"])
                    )
        connection.commit()
        connection.close()
        return {
            "detail": "Information successfully saved."
        }
    return {
        "error": "Error in returning data from AWS."
    }

@app.route("/aws_iot_get", methods=["GET"])
def aws_iot_get():
    if request.method == "GET":
        conn = get_db_connection()
        sensor_data = conn.execute('SELECT * FROM sensor_data ORDER BY created DESC LIMIT 1').fetchall()[0];
        conn.close()
        response = {"speed": 0, "pressure": 0, "gyro": 0}
        response["speed"] = sensor_data["speed"]
        response["pressure"] = sensor_data["pressure"]
        response["gyro"] = sensor_data["gyro"]
        return response
    return {
        "error": "Method not allowed."
    }
    
if __name__ == "__main__":
    app.run(host='0.0.0.0', debug=True)

