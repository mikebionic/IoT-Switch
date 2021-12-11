from main import app
from main import db
from main.models import Sensor_record

@app.route("/add-recording/")
def add_recording():
    temp = request.args.get("temp")
    hum = request.args.get("hum")
    soil_hum = request.args.get("soil_hum")
    
    new_record = Sensor_record(
        temp = temp,
        hum = hum,
        soil_hum = soil_hum
    )
    db.session.add(new_record)
    db.session.commit()
    return "OK"