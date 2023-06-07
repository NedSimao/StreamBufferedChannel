
import sys
import glob
import serial
import serial.tools.list_ports
from multipledispatch import dispatch


class SerialPort(serial.Serial):
    def __init__(self):
        super(SerialPort, self).__init__()
        pass

    def getPorts(self):
        """ 
        Lists serial port names
        A list of the serial ports available on the system
        """
        # Definning variables:
        result = []

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

        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass

        return result


class Uart(serial.Serial):
    def __init__(self):
        super(Uart, self).__init__(self)
        pass

    def config(self):
        pass

    def write(self):
        pass

    def print(self):
        pass

    def println(self):
        pass


if __name__ == '__main__':
    """
    Where test are going to be done
    """

    uart = SerialPort()
    ports = uart.getPorts()

    print(ports)
    print(ports[0])
    pass
