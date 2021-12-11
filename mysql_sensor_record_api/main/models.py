from datetime import datetime

class Sensor_record(db.Model):
    id = db.Column(db.Integer,primary_key=True)
    temp = db.Column(db.String)
    hum = db.Column(db.String)
    soil_hum = db.Column(db.String)
    date = db.Column(db.String, default = str(datetime.now().strftime("%d:%m:%Y")))
    time = db.Column(db.String, default = str(datetime.now().strftime("%H:%M:%S")))
    # dateAdded = db.Column(db.DateTime,default=datetime.now())

    def json(self):
        sensor_records = {
            "id": self.id,
            "temp": self.temp,
            "hum": self.hum,
            "soil_hum": self.soil_hum,
            "date": self.date,
            "time": self.time,     
        }
        return sensor_records