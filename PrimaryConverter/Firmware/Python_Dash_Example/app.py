import serial
import random
import time
import dash
import dash_core_components as dcc
import dash_html_components as html
import pandas as pd
import plotly.express as px
import plotly.graph_objects as go
from dash.dependencies import Output, Input
from plotly.subplots import make_subplots

#dequeueing lists
#heroku creation + add on FREE postgres database, get/store access information 
#psycopg2 library on python, establish connection w/ database, create first table (can be easily deleted later), commit changes, and read (i.e., select) values off table
#long term: figure out data storage method (i.e., from reading a com port to online database (how do you want your data organized)), (local script) + create online script that reads from database and updates plotly/dash page
#most important: html/css for aesthetics

app = dash.Dash(__name__)

#COMPORT
COM_PORT = "COM3"

#list used for the axis values
axis_x = [0]

num_channels = 5    #number of channels

list_of_axis = []  #list containing all the list of channel measurements
temp1_axis = [0]    #channel 1
temp2_axis = [0]    #channel 2
temp3_axis = [0]    #channel 3
voltage_axis = [0]  #channel 4
current_axis = [0]  #channel 5

#add in all the list of measurements in the list of lists
list_of_axis.append(temp1_axis)
list_of_axis.append(temp2_axis)
list_of_axis.append(temp3_axis)
list_of_axis.append(current_axis)
list_of_axis.append(voltage_axis)

global next_update_channel
next_update_channel = 0    #holder for channel number of next update

#checks the first word of string to see if it is a measurement line
def data_selector(string):
    switcher = {
        "TEMP1:": 1,
        "TEMP2:": 2,
        "TEMP3:": 3,
        "ISENS:": 4,
        "VSENS:": 5
    }
    return switcher.get(string, 0)  #returns 0 if it is not a measurement line

#missing port at the moment for testing
def parse_str(p):
    output = ""
    #port.inWaiting() --- not used right now due to testing
    if(p.inWaiting() > 0):
        line = p.readline()
        line = str(line)
        #line = "TEMP3: "
        #line = line + str(random.randint(0,5000))
        collapsed_line = ' '.join(line.split())     #merge all the consective white spaces
        split_string = collapsed_line.split(' ')    #split into list of strings
        global next_update_channel
        next_update_channel = data_selector(split_string[0])    #indicates the next channel to be updated
        if (next_update_channel > 0):
            output = split_string[1]    #data value
            print(split_string[1]) #test
    return output

#serial initalisation
def serial_int(id_port = ""):
    p = None

    try: 
        p = serial.Serial(
            port = "COM3",
            baudrate = 9600,
            bytesize = serial.EIGHTBITS,
            parity = serial.PARITY_NONE,
            stopbits = serial.STOPBITS_ONE,
        )

    except serial.SerialException as msg:
        print("Failed to open port: {0}".format(msg))

    return p

port = serial_int("COM3") #port selection

#page layout
app.layout = html.Div([
    dcc.Graph(
        id = 'graph',
        animate = False
    ),
    dcc.Interval(
        id = 'timer',
        interval = 1000, #1s intervals
        n_intervals = 0
    )
])

"""
#updates values
def update_values():
    axis_x.append(axis_x[-1] + 1) #increment time axis_x

    new_value = parse_str(port) #gets new value and updates the next_channel variable
    for x in range(num_channels):
        if (x == next_update_channel):
            list_of_axis[x].append(new_value)
        else:
            list_of_axis[x].append(list_of_axis[x][-1]) #updates the other lists that don't have a next update value with the last value in their repective list
    
    return None
"""

#addds traces
@app.callback(Output('graph', 'figure'),
              Input('timer', 'n_intervals'))
def update_figure(self):
    axis_x.append(axis_x[-1] + 1) #increment time axis_x

    #test
    print(parse_str(port))
    new_value = 3000
    #new_value = int(parse_str(port)) #gets new value and updates the next_channel variable


    for x in range(num_channels):
        if (x+1 == next_update_channel):
            list_of_axis[x].append(new_value)
        else:
            list_of_axis[x].append(list_of_axis[x][-1]) #updates the other lists that don't have a next update value with the last value in their repective list

    fig = make_subplots(
        rows = 2, cols = 3,
        horizontal_spacing = 0.1,
        #vertical_spacing = 0.25,
        subplot_titles = ("Temp1", "Temp2", "Temp3", "Voltage", "Current")
    )

    fig.update_layout(shapes=[
        # adds line at y=Rated_V
        {'type': 'line','y0':4000,'y1': 4000,'x0':-20, 
            'x1':axis_x[-1]+10,'xref':'x1','yref':'y1',
            'line': {'color': 'red','width': 2.5}
        },
        {'type': 'line','y0':4000,'y1': 4000,'x0':-20, 
            'x1':axis_x[-1]+10,'xref':'x2','yref':'y2',
            'line': {'color': 'red','width': 2.5}
        },
        {'type': 'line','y0':4000,'y1': 4000,'x0':-20, 
            'x1':axis_x[-1]+10,'xref':'x3','yref':'y3',
            'line': {'color': 'red','width': 2.5}
        },
        {'type': 'line','y0':4000,'y1': 4000,'x0':-20, 
            'x1':axis_x[-1]+10,'xref':'x4','yref':'y4',
            'line': {'color': 'red','width': 2.5}
        },
        {'type': 'line','y0':4000,'y1': 4000,'x0':-20, 
            'x1':axis_x[-1]+10,'xref':'x5','yref':'y5',
            'line': {'color': 'red','width': 2.5}
        }
    ])

    fig.add_trace(
        go.Scatter(
            x=list(axis_x), 
            y=list(temp1_axis), 
            mode='lines+markers', 
            name='Temp1'
        ),
        row = 1, col = 1,
    )
    fig.add_trace(
        go.Scatter(
            x=list(axis_x), 
            y=list(temp2_axis), 
            mode='lines+markers', 
            name='Temp2'
        ),
        row = 1, col = 2,
    )
    fig.add_trace(
        go.Scatter(
            x=list(axis_x), 
            y=list(temp3_axis), 
            mode='lines+markers', 
            name='Temp3'
        ),
        row = 1, col = 3,
    )
    fig.add_trace(
        go.Scatter(
            x=list(axis_x), 
            y=list(voltage_axis), 
            mode='lines+markers', 
            name='Voltage'
        ),
        row = 2, col = 1,
    )
    fig.add_trace(
        go.Scatter(
            x=list(axis_x), 
            y=list(current_axis), 
            mode='lines+markers', 
            name='Current'
        ),
        row = 2, col = 2,
    )

    #updating axis ranges
    fig.update_xaxes(title_text = "time(s)", range = [axis_x[-1]-20, axis_x[-1]+10], row = 1, col = 1)
    fig.update_xaxes(title_text = "time(s)", range = [axis_x[-1]-20, axis_x[-1]+10], row = 2, col = 1)
    fig.update_xaxes(title_text = "time(s)", range = [axis_x[-1]-20, axis_x[-1]+10], row = 1, col = 2)
    fig.update_xaxes(title_text = "time(s)", range = [axis_x[-1]-20, axis_x[-1]+10], row = 2, col = 2)
    fig.update_xaxes(title_text = "time(s)", range = [axis_x[-1]-20, axis_x[-1]+10], row = 1, col = 3)

    fig.update_yaxes(title_text = "Temp1(mV)", range = [0, 5000], row = 1, col = 1)
    fig.update_yaxes(title_text = "Temp2(mV)", range = [0, 5000], row = 1, col = 2) 
    fig.update_yaxes(title_text = "Temp3(mV)", range = [0, 5000], row = 1, col = 3)
    fig.update_yaxes(title_text = "Voltage(mV)", range = [0, 5000], row = 2, col = 1)
    fig.update_yaxes(title_text = "Current(mA)", range = [0, 5000], row = 2, col = 2)

    fig.update_layout(height = 500, width = 1000)

    return fig


if __name__ == '__main__':
    app.run_server(debug=True)
    port.close()