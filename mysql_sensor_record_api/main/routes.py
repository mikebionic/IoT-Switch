from main import app
from main import db
from main.models import Sensor_record
from flask import request

@app.route("/add-recording/")
def add_recording():
    temp = request.args.get("temp",default=0)
    hum = request.args.get("hum",default=0)
    temp2 = request.args.get("temp2",default=0)
    hum2 = request.args.get("hum2",default=0)
    soil_hum = request.args.get("soil_hum",default=0)
    soil_hum2 = request.args.get("soil_hum2",default=0)
    soil_hum3 = request.args.get("soil_hum3",default=0)
    gas = request.args.get("gas",default=0)
    
    try:
        new_record = Sensor_record(
            temp = temp,
            hum = hum,
            temp2 = temp2,
            hum2 = hum2,
            soil_hum = soil_hum,
            soil_hum2 = soil_hum2,
            soil_hum3 = soil_hum3,
            gas = gas,
        )
        db.session.add(new_record)
        db.session.commit()
    except Exception as e:
        print(e)
        return f"error {e}", 400
    return "OK"