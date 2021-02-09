import psycopg2
import serial
import sys

'''create update carVCS and carDS syntax'''
global updateCarVCS, updateCarDS

updateCarVCS = """ UPDATE carVCS 
            SET id = %s,
            voltage = %s,
            current = %s
            WHERE pos = %s
            """

updateCarDS = """ update carDS
                SET direction = %s, 
                speedGrade = %s
                where id = 0
                """

def openSerialPort(portToOpen = ""):
    s = None
    
    try:
        s = serial.Serial(
        port = portToOpen, 
        baudrate = 9600, 
        bytesize = serial.EIGHTBITS,
        parity = serial.PARITY_NONE,
        stopbits= serial.STOPBITS_ONE,
        )
    
    except serial.SerialException as msg:
        print("Can't open port")
    
    return s

def openDatabaseConnection():
    con = None

    try: 
        con = psycopg2.connect(database = "d4odufthffmam6", user = "rhahsgujdzpjxa", port = "5432", 
                                    password = "2fe675581f9680a9958f466cd1953b7fecaea654271a9d6f614250e36bf389fc",
                                    host = "ec2-54-164-233-77.compute-1.amazonaws.com")
    except Exception as err:
        print("Couldn't connect to database")

    return con

'''definitely find a better way to implement this (not using a while True)'''
def readFromPort(s):
        while True:
                if (s.inWaiting() > 0):
                        res = s.readline()
                        res = res.strip().decode("utf-8")
                        print(res)
                        return res

def decode(string):

    validInput = False

    if (string[0] == 'M' and string[len(string) - 1] == 'N'):
        validInput = True
        string = string[1:(len(string) - 1)]

    if validInput:
        listOfUnits = ['V', 'A', 'D', 'G']

        indexList = []
        calculations = []

        index = 0
        count = 0

        for unit in listOfUnits:

            index = string.find(unit)

            calculations.append(string[:(index)])
            string = string[(index + 1):len(string)]

            count = count + 1

        return calculations

    else:
        print("Invalid output")
        return -1


'''connect to database/bluetooth'''
con = openDatabaseConnection()
s = openSerialPort("COM8")

cur = con.cursor()

cur.execute(""" SELECT MAX(id) from carVCS """)

'''store the last id that was created'''
maxID = cur.fetchone()

maxID = maxID[0]

cur.execute("""
        SELECT pos FROM carVCS WHERE id = %s
        """, (maxID, ))

'''select and store the position of the highest id'''
output = cur.fetchone()

pos = output[0]

while True:

        stringToDecode = readFromPort(s)
        updateString = []
        updateString = decode(stringToDecode)

        if (updateString != -1):
                
                pos = pos + 1

                if pos == 10:
                        pos = 0
                maxID = maxID + 1

                '''change indexes when speed calculation has been done'''
                cur.execute(updateCarVCS, (maxID, updateString[0], updateString[1], pos))
                cur.execute(updateCarDS, (updateString[2], updateString[3]))

                con.commit() 

'''Close bluetooth/database connections'''
cur.close()
con.close()
s.close