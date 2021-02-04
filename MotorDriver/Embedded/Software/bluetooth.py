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

global STOP, MIN_SPEED, MID_SPEED, MAX_SPEED

STOP = 0
MIN_SPEED = 5000
MID_SPEED = 7000
MAX_SPEED = 9500

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

X4 = deque(maxlen = 20)
readings4 = deque(maxlen = 20)
X4.append(0)
readings4.append(0)

def read_from_port(s):  
    
    if (s.inWaiting() > 0):
        res = s.readline()
        res = res.strip().decode("utf-8")
        print(res)
        unit = res[-1]
        res = res[:-1]
        
        if (unit == "V"):
            
            readings.append(int(res))
            X.append(X[-1] + 1)

        elif (unit == "A"):

            readings2.append(int(res))
            X2.append(X2[-1] + 1)
        
        elif(unit == "P"):

            readings3.append(int(res))
            X3.append(X3[-1] + 1)

        elif(unit == "S"):

            readings4.append(int(res))
            X4.append(X4[-1] + 1)
        
        elif(unit == "D"):

            global direction
            direction = int(res)

        elif(unit == "G"):

            global speedGrade
            speedGrade = int(res)
            

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

    html.Div(
        'Direction: N/A', 
        id = "direction"),

    dcc.Graph(
        id='example-graph',
        animate = False
    ),
    
    dcc.Interval(
        id='graph-update',
        interval = 1*1000,
        n_intervals = 0
    ),

    ]
)

@bluetooth.callback(Output('direction', 'children'),
                    Input('graph-update', 'n_intervals'))
def metric_update(self):
    global direction, direction_string, speedGrade, speedGrade_string

    output = read_from_port(port)

    if (direction == 1):
        direction_string = "Forward"
    else:
        direction_string = "Reverse"

    if(speedGrade == 0):
        speedGrade_string = "STOP"
    elif(speedGrade == 1):
        speedGrade_string = "MIN"
    elif(speedGrade == 2):
        speedGrade_string = "MID"
    elif(speedGrade == 3):
        speedGrade_string = "MAX"

    return [html.H4("Direction: " + direction_string), 
            html.H4("SpeedGrade: " + speedGrade_string)]



@bluetooth.callback(Output('example-graph', 'figure'),
                    [Input('graph-update', 'n_intervals')])
def update_graph(self):
    '''
    output = read_from_port(port)
    '''

    fig = make_subplots(
        rows = 2, cols = 2, 
        vertical_spacing = 0.5, 
        subplot_titles = ("Voltage at H-Bridge vs Time", "Motor Power vs. Time", "Current at H-Bridge vs Time", "Motor Speed vs. Time")
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

    fig.add_trace(
        go.Scatter(
            x = list(X4),
            y = list(readings4),
            name = "Speed",
            mode = "lines+markers"
        ),
        row = 2, col = 2
    )

    fig.update_xaxes(title_text = "time(s)", range = [min(X) - 1, max(X) + 1], row = 1, col = 1)
    fig.update_xaxes(title_text = "time(s)", range = [min(X2) - 1, max(X2) + 1], row = 2, col = 1)
    fig.update_xaxes(title_text = "time(s)", range = [min(X3) - 1, max(X3) + 1], row = 1, col = 2)
    fig.update_xaxes(title_text = "time(s)", range = [min(X4) - 1, max(X4) + 1], row = 2, col = 2)

    fig.update_yaxes(title_text = "voltage(mV)", range = [min(readings) - 1, max(readings) + 1], row = 1, col = 1)
    fig.update_yaxes(title_text = "current(mA)", range = [min(readings2) - 1, max(readings2) + 1], row = 2, col = 1)
    fig.update_yaxes(title_text = "power(mW)", range = [min(readings3) - 1, max(readings3) + 1], row = 1, col = 2)
    fig.update_yaxes(title_text = "speed(m/s)", range = [min(readings4) - 1, max(readings4) + 1], row = 2, col = 2)

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
    