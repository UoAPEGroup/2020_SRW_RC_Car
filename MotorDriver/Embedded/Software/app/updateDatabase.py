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
                speedGrade = %s,
                overVoltage = %s,
                overCurrent = %s,
                establishedConnection = %s
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
        sys.exit()
    
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

    #check if input is valid 
    if ( ((string[0] == 'H') or (string[0] == 'S')) and string[len(string) - 1] == 'P'):

        calculations = []
        listOfUnits = []
        databaseToUpdate = 3

        if(string[0] == "H"):
            listOfUnits = ['V', 'A']
            databaseToUpdate = 0

        if(string[0] == "S"):
            listOfUnits = ['P']
            databaseToUpdate = 1

        #if input is valid, delete extraneous start/stop characters
        string = string[1:(len(string))]

        #set values to search for in string, and specify which database needs to be updated 
        index = 0
        count = 0
        
        #extract relevant values from string
        for unit in listOfUnits:

            index = string.find(unit)

            calculations.append(string[:(index)])
            string = string[(index + 1):len(string)]

            count = count + 1

        print(calculations, databaseToUpdate)
        return [calculations, databaseToUpdate]

    else:
        print("Invalid output")
        return [-1, -1]


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

    (updateString, databaseToUpdate) = decode(stringToDecode)

    print(updateString)

    if (updateString != -1):
            
        pos = pos + 1

        if pos == 10:
            pos = 0

        maxID = maxID + 1

        #change indexes when speed calculation has been done
        if databaseToUpdate == 0:
            cur.execute(updateCarVCS, (maxID, updateString[0], updateString[1], pos))
            for value in updateString:
                print(value)

        elif databaseToUpdate == 1:
            cur.execute(updateCarDS, (updateString[0][0], updateString[0][1], updateString[0][2], updateString[0][3], updateString[0][4]))
            for x in range(len(updateString)):
                print(updateString[x])

        con.commit() 

'''Close bluetooth/database connections'''
cur.close()
con.close()
s.close