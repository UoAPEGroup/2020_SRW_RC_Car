import bleak
import asyncio
from bleak import BleakClient, BleakScanner

characteristicUUID = '0000ffe1-0000-1000-8000-00805f9b34fb'
macUUID = 'D3FBCEE5-A512-45F4-B322-971D41E18A6C'
name = 'A52'


async def run():
    async with BleakScanner() as scanner:
        await asyncio.sleep(5.0)
        devices = await scanner.get_discovered_devices()
    for d in devices:
        if ((d.name).upper() != ("UNKNOWN")):
            print("Name: ", (d.name))
            print("Address: ", d.address)
            print("UUIDS: ", d.metadata['uuids'])

loop = asyncio.get_event_loop()
loop.run_until_complete(run())