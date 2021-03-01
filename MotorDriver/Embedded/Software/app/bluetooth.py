#dash/plotly 
import dash
import asyncio
from dash.dependencies import Output, Input, State
import dash_bootstrap_components as dbc
import dash_core_components as dcc
import dash_html_components as html
import plotly
import plotly.graph_objs as go
from plotly.subplots import make_subplots

#misc
import time
from datetime import datetime

from collections import deque
import psycopg2

#local files
from reuse import *

#define SQL to read from online database
global readNewestCarVCS, readNewestCarDS

readNewestCarVCS = """ 
            SELECT voltage, current FROM carVCS WHERE id = %s
            """
readNewestCarDS = """
            SELECT direction, speedGrade, overVoltage, overCurrent, establishedConnection FROM carDS WHERE id = 0
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

def updateValues(cur, currentId):
    global systemParameters

    cur.execute(readNewestCarVCS, (currentId,))

    try: 
        values = cur.fetchall()

        if (values != None):
            voltage = values[0][0]/1000
            current = values[0][1]/1000
            print(voltage)

            power = voltage * current

            voltageValues.append(voltage)
            currentValues.append(current)
            powerValues.append(power)

            voltageMax.append(20)
            currentMax.append(3)
            
            X.append(X[-1] + 1)
            X2.append(X2[-1] + 1)
            X3.append(X3[-1] + 1)

        cur.execute(readNewestCarDS)
    
        values = cur.fetchall()
        count = 0

        for value in values:
            systemParameters[count] = value
            count = count + 1

    except Exception: 
        pass

def returnDirectionAndSpeedString(direction, speedGrade):
    directionAndSpeedString = []

    directionString = {
        0: "Forward",
        1: "Reverse"
    }

    speedString = {
        0: "Stopped",
        1: "Min",
        2: "Mid",
        3: "Max"
    }

    directionAndSpeedString.append(directionString.get(direction, "Invalid"))
    directionAndSpeedString.append((speedString.get(speedGrade, "Invalid")))

    return directionAndSpeedString

def initializeLists():
    global X, X2, X3, X4, voltageValues, voltageMax, currentValues, currentMax, powerValues, speedValues

    X = deque(maxlen = 20)
    X.append(0)
    voltageValues = deque(maxlen = 20)
    voltageValues.append(0)

    voltageMax = deque(maxlen = 20)
    voltageMax.append(20)

    X2 = deque(maxlen = 20)
    X2.append(0)
    currentValues = deque(maxlen = 20)
    currentValues.append(0)

    currentMax = deque(maxlen = 20)
    currentMax.append(3)

    X3 = deque(maxlen = 20)
    X3.append(0)
    powerValues = deque(maxlen = 20) 
    powerValues.append(0)

    X4 = deque(maxlen = 20)
    X4.append(0)
    speedValues = deque(maxlen = 20)
    speedValues.append(0)

bluetooth = dash.Dash(__name__, external_stylesheets=[dbc.themes.BOOTSTRAP], update_title='Updating...')

startTime = time.time()

#initialize lists that will be the x and y values of graphs
initializeLists()

global maxID, systemParameters
systemParameters = []

#open connection to database
con = openDatabaseConnection()

cur = con.cursor()

#initialize arrays to hold ten blank values

for value in range(10):
    voltageValues.append(0)
    voltageMax.append(20)

    currentValues.append(0)
    powerValues.append(0)

    X.append(X[-1] + 1)
    X2.append(X2[-1] + 1)
    X3.append(X3[-1] + 1)

#extract initial voltage, current, and speed values
cur.execute(""" select * from carVCS order by id""")
rows = cur.fetchall()
for row in rows:
    voltage = row[1]/1000
    current = row[2]/1000
    power = voltage * current

    voltageValues.append(voltage)
    currentValues.append(current)
    powerValues.append(power)
    
    voltageMax.append(20)

    X.append(X[-1] + 1)
    X2.append(X2[-1] + 1)
    X3.append(X3[-1] + 1)

#extract initial system parameters (direction, speedGrade, and safety parameters)
cur.execute(""" SELECT * FROM carDS """)
rows = cur.fetchall()

count = 0
for row in rows:
    systemParameters.append([row][count])
    count = count + 1

for parameter in systemParameters:
    print(parameter)

#identify the largest ID in the system (i.e., the last transmission sent by the uC)
cur.execute("""SELECT MAX(id) FROM carVCS""")

maxID = cur.fetchone()
maxID = maxID[0]

#layout for the webpage
bluetooth.layout = html.Div(

    children = [

        #create header w/ video
        html.Header(
            html.Div(
                children = [
                    html.Div(
                        [
                            html.Video(src = bluetooth.get_asset_url("car.mp4"), muted = True, loop = True, autoPlay = True, style = {"opacity": "0.6", "width": "100vw", "position": "absolute"}),
                            html.Img(src = bluetooth.get_asset_url("uoaSquare.png"), style = {"position": "relative", "float": "left", "height": "10vw", "left": "89vw", "top": "2vh"}),
                        ],
                    ),

                    html.Div (
                        children = [
                            html.H1('RC Car Live Updates', className = "display-4", style = {}),
                            html.Hr(style = {"backgroundColor": "white"}),
                            html.P('UoA FoE Summer Workshop 2020', className = "lead", style = {"textAlign": "center"}),
                            html.Img(src = bluetooth.get_asset_url("arrow.png"), height = "40vh", style = {"opacity": "0.9", "display": "block", "marginLeft": "auto", "marginRight": "auto", "marginTop": "2vw"}),
                        ], style = {"position": "absolute", "left": "50%", "marginRight": "-50%", "top": "80vh", "transform": "translate(-50%, -50%)", "color": "white"}
                    ),

                ], style = {"width": "100vw", "zIndex": "50", "position": "fixed"}
            )
        ),

        #create the header
        
        html.Div( [
            dbc.Row(html.H1("Live Graphs", className = "display-4", style = {'zIndex': "5000"}), style = {"height": "10vh", "width": "100vw", "paddingTop": "1vw", "paddingLeft": "5.5vw", "color": textColor}),
            dbc.Row([
                    dbc.Col(dbc.Row([
                            html.Div(id = 'direction'), 
                            html.Div(id = 'safety'),
                            dbc.Button("System Ratings:", className = "btn mr-3", id = "collapseButtonSR"), 
                            dbc.Collapse(parameterTable, id = "collapseSR", style = {"paddingLeft": "0.2vw"})], style = {"width": "100vw"}), style = {"background": oxfordBlue, "paddingTop": "5vh"}),
                    ], style = {"width": "100vw"},
                    ),
            dbc.Row(dbc.Col(dcc.Graph( id = 'carData', animate = False, style = {"width": "100vw"}), width = 12), style = {"width": "100vw"}),
            ], style = {"position": "relative", "zIndex": "500", "top": "100vh", "backgroundColor": oxfordBlue},
        ),

        dcc.Interval(
            id='updateGraph',
            interval = 1*800,
        ),

        ],
    style = {"backgroundColor": oxfordBlue},
)

#system callbacks

@bluetooth.callback(Output("collapseSR", "is_open"), 
                    [Input("collapseButtonSR", "n_clicks")], 
                    [State("collapseSR", "is_open")],)
def toggleCollapseSR(n, is_open): 
    if n:
        return not is_open
    return is_open

@bluetooth.callback(Output('direction', 'children'),
                    Input('updateGraph', 'n_intervals'))
def metric_update(self):
    global maxID, directionAndSpeedString, systemParameters

    ''' check if there's been an update to the database'''

    cur.execute("SELECT MAX(id) FROM carVCS")

    try: 
        currentId = cur.fetchone()

        if currentId != None: 
            print(currentId[0])

            currentId = currentId[0]

            if ((currentId != None) and (currentId > maxID)):
                maxID = currentId
                updateValues(cur, maxID)

            directionAndSpeedString = returnDirectionAndSpeedString(systemParameters[0][0], systemParameters[0][1])

    except Exception: 
        pass

    return [
        html.Div(
            children = [
            dbc.Button(directionAndSpeedString[0], className = "btn mr-3", style = {"marginLeft": "6vw"}), 
            dbc.Button(directionAndSpeedString[1], className = "btn mr-3"),
            ]
        ),
    ]

@bluetooth.callback(Output('safety', 'children'),
                    Input('updateGraph', 'n_intervals'))
def update_safety(self):
    global systemParameters

    voltageColor = "success"
    currentColor = "success"
    establishedConnection = "danger"

    if systemParameters[0][2]:
        voltageColor = "danger"
    if systemParameters[0][3]:
        currentColor = "danger"
    if systemParameters[0][4]:
        establishedConnection = "success"

    return [
        
        dbc.Button("Over Voltage", color = voltageColor, className = "btn mr-3"), 
        dbc.Button("Over Current", color = currentColor, className = "btn mr-3"),
        dbc.Button("Connection Established", color = establishedConnection, className = "btn mr-3")

    ]

@bluetooth.callback(Output('carData', 'figure'),
                    [Input('updateGraph', 'n_intervals')])
def update_graph(self):

    fig = make_subplots(
        rows = 2, cols = 2, 
        vertical_spacing = 0.2, 
        subplot_titles = ("Voltage at H-Bridge vs Time", "Current at H-Bridge vs Time", "Motor Power vs. Time", "Car Speed vs. Time"),
    )

    fig.add_trace(
        go.Scatter(
            x = list(X),
            y = list(voltageValues),  
            name = 'Voltage', 
            mode = 'lines+markers',

        ),
        row = 1, col = 1)

    fig.add_trace(
        go.Scatter(
            x = list(X),
            y = list(voltageMax),
            mode = 'lines',
            name = 'Max Voltage'
        ),
        row = 1, col = 1)
    
    fig.add_trace( 
        go.Scatter(
            x = list(X2),
            y = list(currentValues), 
            name = 'Current',
            mode = 'lines+markers',
        ),
        row = 1, col = 2)

    fig.add_trace(
        go.Scatter(
            x = list(X3),
            y = list(powerValues),
            name = 'Power',
            mode = 'lines+markers',
        ),
        row = 2, col = 1
    ) 

    fig.add_trace(
        go.Scatter(
            x = list(X4),
            y = list(speedValues),
            name = "Speed",
            mode = "lines+markers"
        ),
        row = 2, col = 2
    )

    xAxisText = "Time stamp"

    fig.update_xaxes(title_text = xAxisText, gridcolor = gridColor, range = [min(X) - 1, max(X) + 1], row = 1, col = 1)
    fig.update_xaxes(title_text = xAxisText, gridcolor = gridColor, range = [min(X2) - 1, max(X2) + 1], row = 1, col = 2)
    fig.update_xaxes(title_text = xAxisText, gridcolor = gridColor, range = [min(X3) - 1, max(X3) + 1], row = 2, col = 1)
    fig.update_xaxes(title_text = xAxisText, gridcolor = gridColor, range = [min(X4) - 1, max(X4) + 1], row = 2, col = 2)

    axesCoefficient = 0.1

    fig.update_yaxes(title_text = "Voltage(V)", gridcolor = gridColor, range = [0, 12.5], row = 1, col = 1)
    fig.update_yaxes(title_text = "Current(A)", gridcolor = gridColor, range = [0, 3.5], row = 1, col = 2)
    fig.update_yaxes(title_text = "Power(W)", gridcolor = gridColor, range = [min(powerValues) - axesCoefficient *(min(powerValues)), max(powerValues) + axesCoefficient * (max(powerValues))], row = 2, col = 1)
    fig.update_yaxes(title_text = "Speed(m/s)", gridcolor = gridColor, range = [min(speedValues) - axesCoefficient * (min(speedValues)), max(speedValues) + axesCoefficient * (max(speedValues))], row = 2, col = 2)

    for i in fig['layout']['annotations']:
        i['font'] = dict(size=18)

    fig.update_layout(paper_bgcolor = richBlack, plot_bgcolor = oxfordBlue, height = 800, font_color = textColor, showlegend = False),

    return fig

if __name__ == '__main__':    
    
    bluetooth.run_server(debug=True, use_reloader = False)
    cur.close()
    con.close()

    print("closed")
    