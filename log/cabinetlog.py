import serial
import datetime
import csv

# open serial connection, /dev/ttyACM0 should be changed to the serial port where the Arduino is connected
ser = serial.Serial('/dev/ttyACM0', 9600)

# script will run until it receives a keyboard interrupt or is otherwise killed
while True:
    try:
        ser_bytes = ser.readline()                                      # read one line from serial connection
        decoded_bytes = ser_bytes[0:len(ser_bytes) - 3].decode("utf-8") # decode raw input to UTF-8 encoding, slice string to remove trailing characters
        currtime = datetime.datetime.now()                              # get current time
        # create or append to an existing csv file
        with open('{}-cabinetlog.csv'.format(currtime.strftime("%m.%d.%y")), 'a') as f:
            # set up csv file parameters, no quoting because the serial output is already comma delimited
            writer = csv.writer(f, delimiter=",", escapechar=' ', quoting=csv.QUOTE_NONE)
            # write current date/time and one line of serial output to a row
            writer.writerow([currtime.strftime("%c"), decoded_bytes])
    # a tidy-looking exception for keyboard interrupts, because this script will likely be keyboard-interrupted a lot!
    except KeyboardInterrupt:
        print('Keyboard interrupt!')
        break