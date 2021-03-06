"""
__init__.py

Created by Eduardo Diaz
"""
#Copyright 2009 armsim authors.
#
#This file is part of armsim.
#
#armsim is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#armsim is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with armsim.  If not, see <http://www.gnu.org/licenses/>.

class AccessMode(object):
    ReadOnly  = 0
    WriteOnly = 1
    ReadWrite = 2

class PeriherpalRegister(object):
    def __init__(self, name, value, accessMode=2):
        self.name       = name
        self.value      = value
        self.accessMode = accessMode

