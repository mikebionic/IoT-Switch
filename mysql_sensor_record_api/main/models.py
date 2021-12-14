from datetime import datetime
from main import db

class Sensor_record(db.Model):
    __tablename__ = "yumuslar"
    no = db.Column(db.Integer,primary_key=True)
    temp = db.Column(db.String)
    hum = db.Column(db.String)
    temp2 = db.Column(db.String)
    hum2 = db.Column(db.String)
    soil_hum = db.Column(db.String)
    soil_hum2 = db.Column(db.String)
    soil_hum3 = db.Column(db.String)
    gas = db.Column(db.String)
    date = db.Column(db.String, default = str(datetime.now().strftime("%d:%m:%Y")))
    time = db.Column(db.String, default = str(datetime.now().strftime("%H:%M:%S")))
    # dateAdded = db.Column(db.DateTime,default=datetime.now())

    def json(self):
        sensor_records = {
            "no": self.no,
            "temp": self.temp,
            "hum": self.hum,
            "soil_hum": self.soil_hum,  
            "temp2": self.temp2,
            "hum2": self.hum2,
            "soil_hum": self.soil_hum,
            "soil_hum2": self.soil_hum2,
            "soil_hum3": self.soil_hum3,
            "gas": self.gas,
            "date": self.date,
            "time": self.time,
        }
        return sensor_records