#!python
from __future__ import print_function
import os
import sys
import flask
import flask_sijax
import argparse

from arduino_device import findArduinoDevicePorts

from arduino_dac import ArduinoDac
from arduino_dac import isArduinoDacPortInfo


network_port = 5000

# Setup application w/ sijax
path = os.path.join('.', os.path.dirname(__file__), 'static/js/sijax/')
app = flask.Flask(__name__)
app.config["SIJAX_STATIC_PATH"] = path
app.config["SIJAX_JSON_URI"] = '/static/js/sijax/json2.js'
flask_sijax.Sijax(app)

class SijaxHandler(object):
    """A container class for all Sijax handlers.

    Grouping all Sijax handler functions in a class
    (or a Python module) allows them all to be registered with
    a single line of code.
    """

    # arduino_dac
    @staticmethod
    def analogWriteA(obj_response,milli_volt):
        if AD is not None:
            AD.analogWriteA(milli_volt)

    @staticmethod
    def analogWriteB(obj_response,milli_volt):
        if AD is not None:
            AD.analogWriteB(milli_volt)

    @staticmethod
    def analogWriteC(obj_response,milli_volt):
        if AD is not None:
            AD.analogWriteC(milli_volt)

    @staticmethod
    def analogWriteD(obj_response,milli_volt):
        if AD is not None:
            AD.analogWriteD(milli_volt)

    @staticmethod
    def analogWriteAll(obj_response,milli_volt):
        if AD is not None:
            AD.analogWriteAll(milli_volt)

    @staticmethod
    def startWaveform(obj_response,waveform):
        if AD is not None:
            AD.startWaveform(waveform)

    @staticmethod
    def stopWaveform(obj_response):
        if AD is not None:
            AD.stopWaveform()


@flask_sijax.route(app, "/")
def index():
    if flask.g.sijax.is_sijax_request:
        # The request looks like a valid Sijax request
        # Let's register the handlers and tell Sijax to process it
        flask.g.sijax.register_object(SijaxHandler)
        return flask.g.sijax.process_request()

    return flask.render_template('dac.html')


def arduinoDacWebserver():
    global AD
    AD = None

    parser = argparse.ArgumentParser(description='Arduino DAC Webserver')
    parser.add_argument('-d', '--debug',
                        help='start the server in local-only debug mode',
                        action='store_true')
    args = parser.parse_args()

    server = 'remote'
    debug = False
    if args.debug:
        server = 'local'
        debug = True

    # Open connection to device
    arduino_device_ports = findArduinoDevicePorts()
    arduino_dac_port = None
    for port in arduino_device_ports:
        port_info = arduino_device_ports[port]
        if isArduinoDacPortInfo(port_info):
            arduino_dac_port = port

    if arduino_dac_port is not None:
        AD = ArduinoDac(port=arduino_dac_port)

    if server == 'local':
        print(' * using debug server - localhost only')
        app.run(port=network_port,debug=debug)
    else:
        print(' * using builtin server - remote access possible')
        app.run(host='0.0.0.0',port=network_port)


# -----------------------------------------------------------------------------
if __name__ == '__main__':
    arduinoDacWebserver()
