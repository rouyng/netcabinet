import serial
import datetime
import csv

ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
    try:
        ser_bytes = ser.readline()
        decoded_bytes = str(ser_bytes[0:len(ser_bytes) - 2].decode("utf-8"))
        today = datetime.date.today()
        with open('~/{}-cabinetlog.csv'.format(today.strftime("%m.%d.%y")) as f:
            writer = csv.writer(f, delimiter="")
            writer.writerow([time.time(), ",", decoded_bytes])
    except KeyboardInterrupt:
        print('Keyboard interrupt!')
        break