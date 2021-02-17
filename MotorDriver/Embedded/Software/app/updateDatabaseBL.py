import bleak
import asyncio
import psycopg2
from bleak import BleakClient, BleakScanner

'''set up BLE address, characteristic UUID, and database query text'''
global characteristicUUID, macUUID, updateCarVCS, updateCarDS, unfinishedString

unfinishedString = ""

characteristicUUID = '0000ffe1-0000-1000-8000-00805f9b34fb'
macUUID = 'D3FBCEE5-A512-45F4-B322-971D41E18A6C'

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

def openDatabaseConnection():
    con = None

    try: 
        con = psycopg2.connect(database = "d4odufthffmam6", user = "rhahsgujdzpjxa", port = "5432", 
                                    password = "2fe675581f9680a9958f466cd1953b7fecaea654271a9d6f614250e36bf389fc",
                                    host = "ec2-54-164-233-77.compute-1.amazonaws.com")
    except Exception as err:
        print("Couldn't connect to database")

    return con

def updateDatabase(updateString, databaseToUpdate):
    global maxID, pos
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

def startAndFinish(string):
    print(string)
    (decodedValues, databaseToUpdate) = decode(string)
    if (decodedValues != -1):
        updateDatabase(decodedValues, databaseToUpdate)

def startNoFinish(string):
    global unfinishedString
    unfinishedString = string
    print(unfinishedString)

def noStartAndFinish(string):
    global unfinishedString
    unfinishedString = unfinishedString + string
    print(unfinishedString)
    (decodedValues, databaseToUpdate) = decode(unfinishedString)
    unfinishedString = ""
    if (decodedValues != -1):
        updateDatabase(decodedValues, databaseToUpdate)

def noStartNoFinish(string):
    global unfinishedString
    unfinishedString = unfinishedString + string
    print(unfinishedString)

def extractStringsToDecode(dictString, string):
    #identify which function to run depending on whether the transmitted string is complete or incomplete
    findFunction = {
        "11": startAndFinish,
        "01": startNoFinish,
        "10": noStartAndFinish,
        "00": noStartNoFinish
    }

    func = findFunction.get(dictString, "Invalid")
    func(string)


def processData(sender, data):
    global pos, maxID
    
    '''Figure out how to translate data from NSlineData to python string'''
    bluetoothString = str(data)
    bluetoothString = bluetoothString.strip()

    bluetoothString = bluetoothString[2:-1]

    #split the incoming transmission into separate components
    splitThroughNewline = bluetoothString.split('\\n\\r')

    print(splitThroughNewline)
    #identify whether the lines of data are incomplete or complete, and manage them accordingly
    if (splitThroughNewline != None):
            for (line) in splitThroughNewline:

                if ((line != "") and (line != None)): 

                    line.replace("\\", "")
                    line.replace("r", "")
                    line.replace("n", "")

                    startLine = line[0]
                    dictString = "0"

                    if ((line.find("P")) != -1):
                        dictString = "1"

                    if((startLine == "S") or (startLine == "H")):
                        dictString = dictString + "1"
                    else:
                        dictString = dictString + "0"

            #check whether it's a finished or nonfinished string
                    extractStringsToDecode(dictString, line)


async def run(address):
    async with BleakClient(macUUID) as client:
        x = await client.is_connected()
        while True:
            await client.start_notify(characteristicUUID, processData)
            await asyncio.sleep(2.0)
            await client.stop_notify(characteristicUUID)

        client.disconnect()


global pos, maxID
'''connect to database/bluetooth'''
con = openDatabaseConnection()

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

if __name__ == "__main__":
    loop = asyncio.get_event_loop()
    loop.run_until_complete(run(macUUID))
    '''Close bluetooth connections'''
    cur.close()
    con.close()
