import bleak
import asyncio
import psycopg2
from bleak import BleakClient, BleakScanner

'''set up BLE address, characteristic UUID, and database query text'''
global characteristicUUID, macUUID, updateCarVCS, updateCarDS

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
                speedGrade = %s
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

def processData(sender, data):
    global pos, maxID
    
    print(str(data))
    '''Figure out how to translate data from NSlineData to python string'''
    stringToDecode = str(data)
    stringToDecode = stringToDecode[2:-5]
    print(stringToDecode)
    
    updateString = decode(stringToDecode)

    if (updateString  != -1):
        pos = pos + 1

        if pos == 10:
                pos = 0

        maxID = maxID + 1

        '''change indexes when speed calculation has been done'''
        cur.execute(updateCarVCS, (maxID, updateString[0], updateString[1], pos))
        cur.execute(updateCarDS, (updateString[2], updateString[3]))

        con.commit() 


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
