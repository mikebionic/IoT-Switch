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

@app.route("/sensor_records/")
def sensor_records():
    offset = request.args.get("offset", default=0)
    limit = request.args.get("limit", default=10)
    records = Sensor_record.query\
        .order_by(Sensor_record.dateAdded.desc())\
        .paginate(int(offset), int(limit), False)

    res = {
        "data": [record.json() for record in records.items],
        "page_total": len(records.items),
        "total": records.total,
        "current_page": records.page,
        "pages": records.pages
        
    }
    return res