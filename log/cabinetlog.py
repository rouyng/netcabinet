import serial
import datetime
import csv

ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
    try:
        ser_bytes = ser.readline()
        decoded_bytes = ser_bytes[0:len(ser_bytes) - 3].decode("utf-8")
        currtime = datetime.datetime.now()
        with open('{}-cabinetlog.csv'.format(currtime.strftime("%m.%d.%y")), 'a') as f:
            writer = csv.writer(f, delimiter=",", escapechar=' ', quoting=csv.QUOTE_NONE)
            writer.writerow([currtime.strftime("%c"), decoded_bytes])
    except KeyboardInterrupt:
        print('Keyboard interrupt!')
        break