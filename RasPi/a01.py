import serial

arduinoSerialData = serial.Serial('/dev/ttyACM0', 9600)
while True:
  if (arduinoSerialData.inWaiting() & gt;0):
    myData = arduinoSerialData.readLine()
    print myData

