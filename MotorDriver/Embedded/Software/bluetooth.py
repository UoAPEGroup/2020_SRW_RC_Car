import serial
import time
import sys
import io
import threading

'''dash/ploty '''
import dash
from dash.dependencies import Output, Input
import dash_core_components as dcc
import dash_html_components as html
import plotly
import plotly.graph_objs as go
import plotly.express as px
import pandas as pd
from collections import deque
from plotly.subplots import make_subplots

bluetooth = dash.Dash(__name__)

startTime = time.time()

X = deque(maxlen=20)
readings = deque(maxlen = 20)
X.append(0)
readings.append(0)

X2 = deque(maxlen=20)
readings2 = deque(maxlen = 20)
X2.append(0)
readings2.append(0)

X3 = deque(maxlen=20)
readings3 = deque(maxlen = 20) 
X3.append(0)
readings3.append(0)

def read_from_port(s):  

    if (s.inWaiting() > 0):
        res = s.readline().strip().decode("utf-8")

        if ((res[-1]) == "V"):
            res = res[:-1]
            print(res)
            readings.append(int(res))
            X.append(X[-1] + 1)

        elif ((res[-1]) == "A"):
            res = res[:-1]
            print(res)
            readings2.append(int(res))
            X2.append(X2[-1] + 1)
        
        elif((res[-1]) == "P"):
            res = res[:-1]
            print(res)
            readings3.append(int(res))
            X3.append(X3[-1] + 1)

        return res
    else: 
        return -1

def openSerialPort(port = ""):
    s = None
    
    try:
        s = serial.Serial(
        port = 'COM8', 
        baudrate = 9600, 
        bytesize = serial.EIGHTBITS,
        parity = serial.PARITY_NONE,
        stopbits= serial.STOPBITS_ONE,
        )
    
    except serial.SerialException as msg:
        print("Can't open port")
    
    return s

port = openSerialPort('COM8')
if port == None:
    sys.exit(1)
    
bluetooth.layout = html.Div(
    [

    dcc.Graph(
        id='example-graph',
        animate = True
    ),
    
    dcc.Interval(
        id='graph-update',
        interval = 1*500,
        n_intervals = 0
    ),

    ]
)


@bluetooth.callback(Output('example-graph', 'figure'),
                    [Input('graph-update', 'n_intervals')])
def update_graph(self):
    global X
    global readings
    global X2
    global readings2
    global X3
    global readings3

    output = read_from_port(port)

    fig = make_subplots(
        rows = 2, cols = 2, 
        vertical_spacing = 0.5, 
        subplot_titles = ("Voltage at H-Bridge vs Time", "Motor Power vs. Time", "Current at H-Bridge vs Time")
    )

    fig.add_trace(
        go.Scatter(
            x = list(X),
            y = list(readings),  
            name = 'Voltage', 
            mode = 'lines+markers',

        ),
        row = 1, col = 1)

    fig.add_trace( 
        go.Scatter(
            x = list(X2),
            y = list(readings2), 
            name = 'Current',
            mode = 'lines+markers',
        ),
        row = 2, col = 1)

    fig.add_trace(
        go.Scatter(
            x = list(X3),
            y = list(readings3),
            name = 'Power',
            mode = 'lines+markers',
        ),
        row = 1, col = 2
    ) 

    fig.update_xaxes(title_text = "time(s)", range = [min(X) - 1, max(X) + 1], row = 1, col = 1)
    fig.update_xaxes(title_text = "time(s)", range = [min(X2) - 1, max(X2) + 1], row = 2, col = 1)
    fig.update_xaxes(title_text = "time(s)", range = [min(X3) - 1, max(X3) + 1], row = 1, col = 2)

    fig.update_yaxes(title_text = "voltage(mV)", range = [min(readings) - 1, max(readings) + 1], row = 1, col = 1)
    fig.update_yaxes(title_text = "current(mA)", range = [min(readings2) - 1, max(readings2) + 1], row = 2, col = 1)
    fig.update_yaxes(title_text = "power(mW)", range = [min(readings3) - 1, max(readings3) + 1], row = 1, col = 2)

    fig.update_layout(height = 700, width = 1200)

    return fig

if __name__ == '__main__':    

    bluetooth.run_server(debug=True, use_reloader = False)
    port.close()
    '''
    port.flushInput()
    port.flushOutput()
    '''

    print("closed")
    