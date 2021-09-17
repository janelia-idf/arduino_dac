"""
Copyright 2013 Peter Polidoro

This file is part of arduino_dac.

arduino_dac is free software: you can redistribute it
and/or modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation, either version 3
of the License, or (at your option) any later version.

arduino_dac is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with arduino_dac.  If not, see
<http://www.gnu.org/licenses/>.  """

from distutils.core import setup


setup(
    name='arduino_dac',
    version='0.1.0',
    author='Peter Polidoro',
    author_email='peter@polidoro.io',
    packages=['arduino_dac',
              'arduino_dac/webserver',
              ],
    scripts=['bin/arduino_dac_cli.py',
             'bin/arduino_dac_webserver.py',
             ],
    package_data={'arduino_dac/webserver':['templates/*.html',
                                            'static/*.css',
                                            'static/images/*.gif',
                                            'static/images/*.png',
                                            'static/js/jquery/*.js',
                                            'static/js/extras/*.js',
                                            'static/js/scripts/*.js']},
    url='https://bitbucket.org/peterpolidoro/arduino_dac',
    license='LICENSE.LESSER.txt',
    description='Software to control the Arduino DAC',
    long_description=open('README.rst').read(),
)
