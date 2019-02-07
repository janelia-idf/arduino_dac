===========
arduino_dac
===========

arduino_dac is a python package to control the Arduino DAC over USB,
using the python module, the command line, or a webpage using a
webserver.


Install
-------

See INSTALL.rst

Running
=======

* If installed into a virtual environment, activate the virtual
  environment before running::

    source ~/virtualenvs/arduino_dac/bin/activate

Python Module
-------------

Typical usage often looks like this::

    from arduino_dac import ArduinoDac

Web Page Controls
-----------------

Open a terminal and run::

    arduino_dac_webserver.py

Open a browser and navigate to::

    http://localhost:5000



Author: Peter Polidoro

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
