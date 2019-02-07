#!python
from __future__ import print_function, division
import atexit
import argparse
import copy
import time

from arduino_device import ArduinoDevice, ArduinoDevices, findArduinoDevicePorts


DEBUG = False
BAUDRATE = 'default'
DEVICE_MODEL_NUMBER = 2486

class ArduinoDac(ArduinoDevice):

    def __init__(self,*args,**kwargs):
        kwargs.update({'model_number': DEVICE_MODEL_NUMBER})
        serial_number = None
        if 'debug' not in kwargs:
            kwargs.update({'debug': DEBUG})
        if 'baudrate' not in kwargs:
            kwargs.update({'baudrate': BAUDRATE})
        elif (kwargs['baudrate'] is None) or (kwargs['baudrate'].lower() == 'default'):
            kwargs.update({'baudrate': BAUDRATE})
        if 'serial_number' in kwargs:
            serial_number = kwargs.pop('serial_number')
        if ('port' not in kwargs) or (kwargs['port'] is None):
            port =  findArduinoDacPort(baudrate=kwargs['baudrate'],
                                        serial_number=serial_number)
            kwargs.update({'port': port})
        super(ArduinoDac,self).__init__(*args,**kwargs)
        atexit.register(self._exitArduinoDac)
        dev_info = self.getDevInfo()

    def _exitArduinoDac(self):
        pass

    def getArduinoDacInfo(self):
        arduino_dac_info = self.getArduinoDeviceInfo()

        return arduino_dac_info


# device_names example:
# [{'port':'/dev/ttyACM0',
#   'device_name':'dac0'},
#  {'serial_number':3,
#   'device_name':'dac1'}]
class ArduinoDacs(ArduinoDevices):

    def __init__(self,*args,**kwargs):
        if ('use_ports' not in kwargs) or (kwargs['use_ports'] is None):
            kwargs['use_ports'] = findArduinoDacPorts(*args,**kwargs)
        super(ArduinoDacs,self).__init__(*args,**kwargs)

    def appendDevice(self,*args,**kwargs):
        self.append(ArduinoDac(*args,**kwargs))

    def getArduinoDacInfo(self):
        arduino_dac_info = []
        for device_index in range(len(self)):
            dev = self[device_index]
            arduino_dac_info.append(dev.getArduinoDacInfo())
        return arduino_dac_info


def findArduinoDacPorts(baudrate=None, serial_number=None, try_ports=None, debug=DEBUG):
    arduino_device_ports = findArduinoDevicePorts(baudrate=baudrate,
                                                  model_number=DEVICE_MODEL_NUMBER,
                                                  serial_number=serial_number,
                                                  try_ports=try_ports,
                                                  debug=debug)

    if type(serial_number) is int:
        serial_number = [serial_number]

    arduino_dac_ports = {}
    for port in arduino_device_ports:
        try:
            dev_serial_number = arduino_device_ports[port]['serial_number']
        except KeyError:
            break
        if (serial_number is None) or (dev_serial_number in serial_number):
            arduino_dac_ports[port] = {'serial_number': dev_serial_number}
    return arduino_dac_ports

def findArduinoDacPort(baudrate=None, serial_number=None, try_ports=None, debug=DEBUG):
    arduino_dac_ports = findArduinoDacPorts(baudrate=baudrate,
                                                                     serial_number=serial_number,
                                                                     try_ports=try_ports,
                                                                     debug=debug)
    if len(arduino_dac_ports) == 1:
        return arduino_dac_ports.keys()[0]
    elif len(arduino_dac_ports) == 0:
        arduino_device_ports = findArduinoDevicePorts(baudrate=baudrate,
                                                      model_number=DEVICE_MODEL_NUMBER,
                                                      serial_number=serial_number,
                                                      try_ports=try_ports,
                                                      debug=debug)
        err_str = 'Could not find Arduino dacs. Check connections and permissions.\n'
        err_str += 'Tried ports: ' + str(arduino_device_ports)
        raise RuntimeError(err_str)
    else:
        err_str = 'Found more than one Arduino dac. Specify port or serial_number.\n'
        err_str += 'Matching ports: ' + str(arduino_dac_ports)
        raise RuntimeError(err_str)

def isArduinoDacPortInfo(port_info):
    return port_info['model_number'] == DEVICE_MODEL_NUMBER

def arduinoDacCli():
    parser = argparse.ArgumentParser(description='Arduino Dac')
    # parser.add_argument('--debug',
    #                     help='Use the simulated software dac instead of the real hardware dac',
    #                     action='store_true')
    # parser.add_argument('-d','--device',nargs=1,type=int,default=[0],
    #                     help='device index')
    subparsers = parser.add_subparsers(dest='subparser_name',help='sub-command help')

    # create the parser for the "info" command
    parser_info = subparsers.add_parser('info', help='info help')

    args = parser.parse_args()

    o = ArduinoDac(debug=DEBUG)
    # if not args.debug:
    #     o = ArduinoDac()
    # else:
    #     o = ArduinoDacDebug()
    # device = args.device[0]
    if args.subparser_name == 'info':
        print(o.getArduinoDacInfoDict())

# -----------------------------------------------------------------------------------------
if __name__ == '__main__':
    arduinoDacCli()
