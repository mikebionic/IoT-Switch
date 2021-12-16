import requests

from main import db
from main.models import Device

sych_server_host = "http://localhost:8001/"
sych_url_path = "add-recording/"

temp_command = "temp_command"
temp2_command = "temp2_command"
hum_command = "hum_command"
hum2_command = "hum2_command"
soil_hum_command = "soil_hum_command"
soil_hum2_command = "soil_hum2_command"
soil_hum3_command = "soil_hum3_command"
gas_command = "gas_command"


def synch_sensor_data():
    temp, hum, temp2, hum2, soil_hum, soil_hum2, soil_hum3, gas = gather_db_data()
    print(temp, hum, temp2, hum2, soil_hum, soil_hum2, soil_hum3, gas)

    arg_temp = f"temp={temp}"
    arg_hum = f"hum={hum}"
    arg_temp2 = f"temp2={temp2}"
    arg_hum2 = f"hum2={hum2}"
    arg_soil_hum = f"soil_hum={soil_hum}"
    arg_soil_hum2 = f"soil_hum2={soil_hum2}"
    arg_soil_hum3 = f"soil_hum3={soil_hum3}"
    arg_gas = f"gas={gas}"
    args_data = f"?{arg_temp}&{arg_temp2}&{arg_hum}&{arg_hum2}&{arg_soil_hum}&{arg_soil_hum2}&{arg_soil_hum3}&{arg_gas}"

    try:
        r = requests.get(f"{sych_server_host}/{sych_url_path}{args_data}")
        print(r.text())
    except Exception as e:
        print(e)


def gather_db_data():
    temp, hum, temp2, hum2, soil_hum, soil_hum2, soil_hum3, gas = 0, 0, 0, 0, 0, 0, 0, 0

    try:
        if not temp_command:
            print("not using temp_command")
            raise Exception

        temp_device = Device.query.filter_by(command = temp_command).first()
        if temp_device:
            temp = temp_device.state
    except Exception as e:
        print(e)

    try:
        if not temp2_command:
            print("not using temp2_command")
            raise Exception

        temp2_device = Device.query.filter_by(command = temp2_command).first()
        if temp2_device:
            temp2 = temp2_device.state
    except Exception as e:
        print(e)

    try:
        if not hum_command:
            print("not using hum_command")
            raise Exception

        hum_device = Device.query.filter_by(command = hum_command).first()
        if hum_device:
            hum = hum_device.state
    except Exception as e:
        print(e)

    try:
        if not hum2_command:
            print("not using hum2_command")
            raise Exception

        hum2_device = Device.query.filter_by(command = hum2_command).first()
        if hum2_device:
            hum2 = hum2_device.state
    except Exception as e:
        print(e)

    try:
        if not soil_hum_command:
            print("not using soil_hum_command")
            raise Exception

        soil_hum_device = Device.query.filter_by(command = soil_hum_command).first()
        if soil_hum_device:
            soil_hum = soil_hum_device.state
    except Exception as e:
        print(e)

    try:
        if not soil_hum2_command:
            print("not using soil_hum2_command")
            raise Exception

        soil_hum2_device = Device.query.filter_by(command = soil_hum2_command).first()
        if soil_hum2_device:
            soil_hum2 = soil_hum2_device.state
    except Exception as e:
        print(e)

    try:
        if not soil_hum3_command:
            print("not using soil_hum3_command")
            raise Exception

        soil_hum3_device = Device.query.filter_by(command = soil_hum3_command).first()
        if soil_hum3_device:
            soil_hum3 = soil_hum3_device.state
    except Exception as e:
        print(e)

    try:
        if not gas_command:
            print("not using gas_command")
            raise Exception

        gas_device = Device.query.filter_by(command = gas_command).first()
        if gas_device:
            gas = gas_device.state
    except Exception as e:
        print(e)

    return temp, hum, temp2, hum2, soil_hum, soil_hum2, soil_hum3, gas

synch_sensor_data()