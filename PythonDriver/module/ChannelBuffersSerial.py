
import sys
import glob
import serial
import serial.tools.list_ports
from multipledispatch import dispatch


class SerialPort(serial.Serial):

    global ser  # global variable to store the serial object

    def __init__(self):
        super(SerialPort, self).__init__()

    def listSerialPorts(self):
        """ 
        Lists the serial port names available on the system
        """

        # Checking the computer operational system:
        if sys.platform.startswith('win'):
            ports = ['COM%s' % (i + 1) for i in range(256)]
        elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
            # this excludes your current terminal "/dev/tty"
            ports = glob.glob('/dev/tty[A-Za-z]*')
        elif sys.platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError('Unsupported platform')

        # Definning variables:
        portsFound = []
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                portsFound.append(port)
            except (OSError, serial.SerialException):
                pass

        return portsFound

    def findDevices(self, device_serial_name="Arduino"):
        """
        Look through all the available serial connections, the serial objects with "device_serial_name" 
        inside
        """
        comPorts = []

        portsFound = self.listSerialPorts()
        connectionAvailable = len(portsFound)

        for curr_device in range(connectionAvailable):
            devicePort = str(portsFound[curr_device])

            if device_serial_name in devicePort:
                comPorts.append((devicePort.split(' '))[0])

        return comPorts

    def connectPort(self, serialPort, baudrate=9600, timeout=-1, xonxoff=False):
        if serialPort is not None:
            try:
                self.ser = serial.Serial(
                    serialPort, baudrate, timeout, xonxoff)
                print("Connected to "+serialPort)
            except serial.SerialException as var:
                print("Connection issued!\n Exception detail:"+var)

    def isComStablished(self, command, readStr="ACK", encoding='ascii', errors='strict'):
        command += str('\n')
        serialString = val = self.ser.write(command.encode(encoding, errors))

        # inCommingData=self.ser.read_until(b'}')
        inCommingData = self.ser.readline()

        if (inCommingData == readStr):
            return True

        else:
            return False


class ReadChannel(SerialPort):

    def __init__(self, channelNumber):
        super(SerialPort, self).__init__()
        self.channelNo = channelNumber

    # Declaring and implementing all the available functions for the channelBuffer

    def Ascii(self, sepCar="\t", decode='ascii'):
        readData = self.ser.readline().decode(decode).split(sepCar)

        return readData

    def AsciiTimeStamp(self, sepCar="\t"):

        readData = self.Ascii(sepCar)

        return readData

    def RawData16(self):

        pass

    def RawData8(self):

        pass

    def RawDataTimeStamp16(self):

        pass

    def RawDataTimeStamp8(self):

        pass


if __name__ == '__main__':
    pass
