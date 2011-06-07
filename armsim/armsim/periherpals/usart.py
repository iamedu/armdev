"""
usart.py

Created by Eduardo Diaz

This file defines the usart periherpal
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
from armsim.periherpals import AccessMode
from armsim.periherpals import PeriherpalRegister
from armsim.bitset import Bitset
from pdc import PDC
from threading import Thread
import os
import uart

class UsartSender(Thread):
    def __init__(self, usart):
        Thread.__init__(self)
        self.usart = usart

    def run(self):
        test = open('test', 'w')
        usart = self.usart
        while True:
            while not usart.sendEnabled():
                pass
            while usart.sendEnabled():
                while (usart.regs[0x0014].value & 0x00000002):
                    pass
                value = usart.regs[0x001C].value & 0x000000FF
                usart.regs[0x001C].value = 0
                value = chr(value)
                #os.write(usart.mid, value)
                test.write(value)
                test.flush()
                
                bs = Bitset(usart.regs[0x0014].value, 32)
                bs[1] = 1
                usart.regs[0x0014].value = int(bs)

class UsartReceiver(Thread):
    def __init__(self, usart):
        Thread.__init__(self)
        self.usart = usart

    def run(self):
        pass

class Usart(PDC):
    """
    This class defines the usart registers and functions
    """

    size = 0x128
    len  = 16 * 1024 #16kb

    def __init__(self):
        PDC.__init__(self)
        self.regs[0x0000] = PeriherpalRegister('US_CR', 0, AccessMode.WriteOnly)
        self.regs[0x0004] = PeriherpalRegister('US_MR', 0)
        self.regs[0x0008] = PeriherpalRegister('US_IER', 0, AccessMode.WriteOnly)
        self.regs[0x000c] = PeriherpalRegister('US_IDR', 0, AccessMode.WriteOnly)
        self.regs[0x0010] = PeriherpalRegister('US_IMR', 0, AccessMode.ReadOnly)
        self.regs[0x0014] = PeriherpalRegister('US_CSR', 2, AccessMode.ReadOnly)
        self.regs[0x0018] = PeriherpalRegister('US_RHR', 0, AccessMode.ReadOnly)
        self.regs[0x001C] = PeriherpalRegister('US_THR', 0, AccessMode.WriteOnly)
        self.regs[0x0020] = PeriherpalRegister('US_BRGR', 0)
        self.regs[0x0024] = PeriherpalRegister('US_RTOR', 0)
        self.regs[0x0028] = PeriherpalRegister('US_TTGR', 0)
        self.regs[0x0040] = PeriherpalRegister('US_FIDI', 0)
        self.regs[0x0044] = PeriherpalRegister('US_NER', 0, AccessMode.ReadOnly)
        self.regs[0x004c] = PeriherpalRegister('US_IF', 0)

        self.regs[0x0014].value = 2;

        self.sender = UsartSender(self)
        self.receiver = UsartReceiver(self)
        
        #(mid, sid, mname, sname) = uart.openpty()
        #self.mid   = mid
        #self.sid   = sid
        #self.mname = mname
        #self.sname = sname

        #print "Setting up virtual serial port at", mname

        self.sender.start()

    def recvEnabled(self):
        control = Bitset(self.regs[0x0000].value)
        return control[4] and not control[5]

    def waitRecvReady(self):
        control = Bitset(self.regs[0x0014].value)
        while control[0]:
            pass

    def sendEnabled(self):
        control = Bitset(self.regs[0x0000].value)
        return control[6] and not control[7]

    def read(self, addr):
        if self.regs[addr].accessMode == AccessMode.WriteOnly:
            return 0
        
        return self.regs[addr].value

    def write(self, addr, value):
        value = abs(value) & 0xFFFFFFFF

        if self.regs[addr].accessMode == AccessMode.ReadOnly:
            return

        self.regs[addr].value = value

        if addr == 0x001c and self.sendEnabled():
            bs = Bitset(self.regs[0x0014].value, 32)
            bs[1] = 0
            self.regs[0x0014].value = int(bs)

