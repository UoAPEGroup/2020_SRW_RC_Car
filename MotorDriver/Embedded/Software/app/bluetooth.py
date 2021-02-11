import time
import psycopg2

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
import dash_bootstrap_components as dbc

global readNewestCarVCS, readNewestCarDS

readNewestCarVCS = """ 
            SELECT voltage, current FROM carVCS WHERE id = %s
            """
readNewestCarDS = """
            SELECT direction, speedGrade FROM carDS WHERE id = 0
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
    global direction, speedGrade

    cur.execute(readNewestCarVCS, (currentId,))

    values = cur.fetchall()

    voltageValues.append(values[0][0])
    voltageMax.append(10000)
    X.append(X[-1] + 1)
    currentValues.append(values[0][1])
    X2.append(X2[-1] + 1)
    powerValues.append((values[0][0] * values[0][1])/1000)
    X3.append(X3[-1] + 1)

    cur.execute(readNewestCarDS)

    values = cur.fetchall()

    direction = values[0][0]
    speedGrade = values[0][1]


bluetooth = dash.Dash(__name__, external_stylesheets=[dbc.themes.BOOTSTRAP])

startTime = time.time()

backgroundColor = 'white'
headerColor = 'white'
uoaLightBlue = '#009AC7'
uoaDarkBlue = '#00457d'
textColor = 'black'

'''initalize lists that will hold the x and y values in graphs'''
X = deque(maxlen = 20)
voltageValues = deque(maxlen = 20)
voltageMax = deque(maxlen = 20)
X.append(0)
voltageValues.append(0)
voltageMax.append(10000)

X2 = deque(maxlen=20)
currentValues = deque(maxlen = 20)
X2.append(0)
currentValues.append(0)

X3 = deque(maxlen=20)
powerValues = deque(maxlen = 20) 
X3.append(0)
powerValues.append(0)

X4 = deque(maxlen = 20)
speedValues = deque(maxlen = 20)
X4.append(0)
speedValues.append(0)

''' create connection to database'''
con = openDatabaseConnection()

cur = con.cursor()

cur.execute(""" select * from carVCS order by id""")

rows = cur.fetchall()

'''update initial values for voltage/current '''

for row in rows:
    voltageValues.append(row[1])
    voltageMax.append(10000)
    X.append(X[-1] + 1)
    currentValues.append(row[2])
    X2.append(X2[-1] + 1)
    powerValues.append((row[1] * row[2])/1000)
    X3.append(X3[-1] + 1)

'''store original direction and speedgrade''' 

cur.execute(""" SELECT * FROM carDS """)

rows = cur.fetchall()

''' store the highest ID value and the direction/speedgrade'''
global direction, speedGrade, maxID

direction = rows[0][1]
speedGrade = rows[0][2]

cur.execute("""
            SELECT MAX(id) FROM carVCS""")

maxID = cur.fetchone()
maxID = maxID[0]

'''Layout for the web app'''
bluetooth.layout = dbc.Container(

    children = [
        
        html.Div( 
            dbc.Container(
                dbc.Jumbotron(
                html.Div(
                    children = [
                        html.H1('RC Car Live Updates', className = "display-3"),
                        html.Hr(className = "my-2", style = {"margin-right": "50vw"}),
                        html.P('UoA FoE Summer Workshop 2020', className = "lead", style = {"margin-top": "2vw"}),
                ], style = {"margin-left": "2vw"} ), fluid = True, style = {"backgroundColor": "green !important"}),
            fluid = True),
        ),
        
        html.Div(
            
            dbc.Row( 
                [ 
                    dbc.Col( dcc.Graph( id = 'carData', animate = False), width = 10), 
                    dbc.Col( children = [
                        dbc.Row(dbc.Card( children = [dbc.CardHeader("System Information:"), dbc.CardBody(id = 'direction', className = "card-title")], color = uoaDarkBlue, inverse = True, outline = True), style = { "margin-top": "6vw"}),
                        ], width = 2),
                    

                ],
            ),
        ),
        


        dcc.Interval(
            id='updateGraph',
            interval = 1*1000,
            n_intervals = 0
        ),

        ],
    fluid = True, style = {"backgroundColor" : "#FAFAFA"},
)

@bluetooth.callback(Output('direction', 'children'),
                    Input('updateGraph', 'n_intervals'))
def metric_update(self):
    global direction, direction_string, speedGrade, speedGrade_string, maxID

    ''' check if there's been an update to the database'''

    cur.execute("SELECT MAX(id) FROM carVCS")
    currentId = cur.fetchone()
    print(currentId[0])

    currentId = currentId[0]

    if ((currentId != None) and (currentId > maxID)):
        maxID = currentId
        updateValues(cur, maxID)

    if (direction == 1):
        direction_string = "Forward"
    else:
        direction_string = "Reverse"

    if(speedGrade == 0):
        speedGrade_string = "Braked"
    elif(speedGrade == 1):
        speedGrade_string = "Minimum Speed"
    elif(speedGrade == 2):
        speedGrade_string = "Medium Speed"
    elif(speedGrade == 3):
        speedGrade_string = "Maximum Speed"

    return [
            html.H4(direction_string), 
            html.H4(speedGrade_string)]



@bluetooth.callback(Output('carData', 'figure'),
                    [Input('updateGraph', 'n_intervals')])
def update_graph(self):

    fig = make_subplots(
        rows = 4, cols = 1, 
        vertical_spacing = 0.1, 
        subplot_titles = ("Voltage at H-Bridge vs Time", "Current at H-Bridge vs Time", "Motor Power vs. Time", "Car Speed vs. Time")
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
        row = 2, col = 1)

    fig.add_trace(
        go.Scatter(
            x = list(X3),
            y = list(powerValues),
            name = 'Power',
            mode = 'lines+markers',
        ),
        row = 3, col = 1
    ) 

    fig.add_trace(
        go.Scatter(
            x = list(X4),
            y = list(speedValues),
            name = "Speed",
            mode = "lines+markers"
        ),
        row = 4, col = 1
    )

    fig.update_xaxes(title_text = "time(s)", range = [min(X) - 1, max(X) + 1], row = 1, col = 1)
    fig.update_xaxes(title_text = "time(s)", range = [min(X2) - 1, max(X2) + 1], row = 2, col = 1)
    fig.update_xaxes(title_text = "time(s)", range = [min(X3) - 1, max(X3) + 1], row = 3, col = 1)
    fig.update_xaxes(title_text = "time(s)", range = [min(X4) - 1, max(X4) + 1], row = 4, col = 1)

    fig.update_yaxes(title_text = "voltage(mV)", range = [min(voltageValues) - 0.25*(min(voltageValues)), max(voltageValues) + 0.25*(max(voltageValues))], row = 1, col = 1)
    fig.update_yaxes(title_text = "current(mA)", range = [min(currentValues) - 0.25 *(min(currentValues)), max(currentValues) + 0.25 * (max(currentValues))], row = 2, col = 1)
    fig.update_yaxes(title_text = "power(mW)", range = [min(powerValues) - 0.25 *(min(powerValues)), max(powerValues) + 0.25 * (max(powerValues))], row = 3, col = 1)
    fig.update_yaxes(title_text = "speed(m/s)", range = [min(speedValues) - 0.25 * (min(speedValues)), max(speedValues) + 0.25 * (max(speedValues))], row = 4, col = 1)

    fig.update_layout(paper_bgcolor = backgroundColor, height = 1000, font_color = textColor)

    return fig

if __name__ == '__main__':    

    bluetooth.run_server(debug=True, use_reloader = False)
    cur.close()
    con.close()

    print("closed")
    