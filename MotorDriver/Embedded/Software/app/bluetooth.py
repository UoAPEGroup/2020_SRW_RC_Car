import time
import psycopg2

'''dash/ploty '''
import dash
from dash.dependencies import Output, Input, State
import dash_core_components as dcc
import dash_html_components as html
import plotly
import plotly.graph_objs as go
import plotly.express as px
import pandas as pd
from collections import deque
from plotly.subplots import make_subplots
import dash_bootstrap_components as dbc
from datetime import datetime

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

    try: 
        values = cur.fetchall()

        if (values != None):

            voltage = values[0][0]/1000
            current = values[0][1]/1000

            power = voltage * current

            voltageValues.append(voltage)
            currentValues.append(current)
            powerValues.append(power)

            voltageMax.append(20)
            
            X.append(X[-1] + 1)
            X2.append(X2[-1] + 1)
            X3.append(X3[-1] + 1)

    except Exception: 
        pass

    cur.execute(readNewestCarDS)
    
    try: 
        values = cur.fetchall()

        if (values != None):
            direction = values[0][0]
            speedGrade = values[0][1]
    except Exception: 
        pass

bluetooth = dash.Dash(__name__, external_stylesheets=[dbc.themes.BOOTSTRAP], update_title='Updating...')

startTime = time.time()

backgroundColor = 'white'
headerColor = 'white'
uoaLightBlue = '#009AC7'
uoaDarkBlue = 'rgb(18, 61, 113)'
uoaGray = "#8D9091"
textColor = 'black'
lightGray = "rgb(228, 231, 235)"

'''initalize lists that will hold the x and y values in graphs'''
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

X3 = deque(maxlen = 20)
X3.append(0)
powerValues = deque(maxlen = 20) 
powerValues.append(0)

X4 = deque(maxlen = 20)
X4.append(0)
speedValues = deque(maxlen = 20)
speedValues.append(0)


''' create connection to database'''
con = openDatabaseConnection()

cur = con.cursor()

cur.execute(""" select * from carVCS order by id""")

rows = cur.fetchall()

'''update initial values for voltage/current '''

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

global parameterTable

parameterTableHeader = [html.Thead(html.Tr([html.Th("Parameter"), html.Th("Value")]))]
row1 = html.Tr([html.Td("Max Voltage at H-Bridge"), html.Td("20V")])
row2 = html.Tr([html.Td("Max Current at H-Bridge"), html.Td("3A")])
row3 = html.Tr([html.Td("Car Power Rating"), html.Td("30W")])
parameterTableBody = [html.Tbody([row1, row2, row3])]

parameterTable = dbc.Table(parameterTableHeader + parameterTableBody, bordered= True, striped = True, hover = True)

'''Layout for the web app'''
bluetooth.layout = dbc.Container(

    children = [

        #create the header
        html.Div( 
            dbc.Container(
                dbc.Jumbotron(
                html.Div(
                    children = [
                        html.Div (
                            children = [
                            html.H1('RC Car Live Updates', className = "display-4", style = {"marginTop": "28vw", 'paddingTop': "1vw"}),
                            html.Hr(style = {"margin-right": "57vw", "backgroundColor": "white"}),
                            html.P('UoA FoE Summer Workshop 2020', className = "lead", style = {"margin-top": "2vw"})], style = {}),
                        html.Img(src = bluetooth.get_asset_url("uoaSquare.png"), style = {"height": "10vw", "paddingLeft": "78vw", "marginTop": "-3vw"}),
                ], style = {"marginLeft": "5vw", "color": "white"} ), fluid = True, style = {"backgroundImage": "linear-gradient(rgba(0,0,0,0.5), rgba(0,0,0,0.5)), url(https://images.unsplash.com/photo-1465447142348-e9952c393450?ixid=MXwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHw%3D&ixlib=rb-1.2.1&auto=format&fit=crop&w=1568&q=80)",
                "backgroundPosition": "center center", "backgroundSize": "cover", "height": "45vw", "marginLeft": "0"}),
            fluid = True),
        ),
        
        html.Div( [
            dbc.Row(dbc.Col(dbc.Jumbotron(html.H1("Live Graphs", className = "display-4", style = {}), style = {"height": "10vw", "marginTop": "2vw", "marginLeft": "2vw", "backgroundColor": "#FAFAFA"}), width = 10), style = {} ),
            dbc.Row( 
                [ 
                    dbc.Col( dcc.Graph( id = 'carData', animate = False), width = 10), 
                    dbc.Col( children = [
                        dbc.Row(dbc.Card( children = [dbc.CardBody(id = 'direction', className = "card-title", style = {"textAlign": "left"})], color = uoaDarkBlue, inverse = True, style = {"marginTop": "6vw"})),
                        dbc.Row([
                            dbc.Button("System Ratings:", outline = False, id = "collapseButtonSR", style = {"backgroundColor": "#FAFAFA", "color": "black", "marginTop": "2vw"}), 
                            dbc.Collapse(parameterTable, id = "collapseSR", style = {"marginTop": "0.5vw", "marginLeft": "0.2vw"})
                        ])
                        ], width = 2),
                    

                ],
            ),
        ],
        ),

        

        dcc.Interval(
            id='updateGraph',
            interval = 1*800,
        ),

        ],
    fluid = True, style = {"backgroundColor" : "#FAFAFA"},
)

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
    global direction, direction_string, speedGrade, speedGrade_string, maxID

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

            if (direction == 1):
                direction_string = "Forward"
            else:
                direction_string = "Reverse"

            if(speedGrade == 0):
                speedGrade_string = "Stopped"
            elif(speedGrade == 1):
                speedGrade_string = "Min"
            elif(speedGrade == 2):
                speedGrade_string = "Mid"
            elif(speedGrade == 3):
                speedGrade_string = "Max"

    except Exception: 
        pass

    return [
        html.Div(
            children = [
            html.H2("Direction: ", className = "display-5", style = {"fontSize": "1.5vw"}),
            html.Hr(style = {"backgroundColor": "white", "marginTop": "-0.3vw"}),
            html.H4(direction_string, className = "display-4", style = {"fontSize": "2.5vw", "marginTop": "-0.7vw"}), 
            html.H2("Speed: ", className = "display-5", style = {"fontSize": "1.5vw", "marginTop": "2vw"}),
            html.Hr(style = {"backgroundColor": "white", "marginTop": "-0.3vw"}),
            html.H4(speedGrade_string, style = {"fontSize": "2.5vw", "marginTop": "-0.7vw"}, className = "display-4")],
        ),
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

    fig.update_xaxes(title_text = "time(s)", gridcolor = lightGray, range = [min(X) - 1, max(X) + 1], row = 1, col = 1)
    fig.update_xaxes(title_text = "time(s)", gridcolor = lightGray, range = [min(X2) - 1, max(X2) + 1], row = 1, col = 2)
    fig.update_xaxes(title_text = "time(s)", gridcolor = lightGray, range = [min(X3) - 1, max(X3) + 1], row = 2, col = 1)
    fig.update_xaxes(title_text = "time(s)", gridcolor = lightGray, range = [min(X4) - 1, max(X4) + 1], row = 2, col = 2)

    axesCoefficient = 0.1

    fig.update_yaxes(title_text = "Voltage(V)", gridcolor = lightGray, range = [min(voltageValues) - axesCoefficient*(min(voltageValues)), max(voltageValues) + axesCoefficient*(max(voltageValues))], row = 1, col = 1)
    fig.update_yaxes(title_text = "Current(A)", gridcolor = lightGray, range = [min(currentValues) - axesCoefficient *(min(currentValues)), max(currentValues) + axesCoefficient * (max(currentValues))], row = 1, col = 2)
    fig.update_yaxes(title_text = "Power(W)", gridcolor = lightGray, range = [min(powerValues) - axesCoefficient *(min(powerValues)), max(powerValues) + axesCoefficient * (max(powerValues))], row = 2, col = 1)
    fig.update_yaxes(title_text = "Speed(m/s)", gridcolor = lightGray, range = [min(speedValues) - axesCoefficient * (min(speedValues)), max(speedValues) + axesCoefficient * (max(speedValues))], row = 2, col = 2)

    for i in fig['layout']['annotations']:
        i['font'] = dict(size=18)

    fig.update_layout(paper_bgcolor = "white", plot_bgcolor = "white", height = 800, font_color = textColor, showlegend = True),

    return fig

if __name__ == '__main__':    

    bluetooth.run_server(debug=True, use_reloader = False)
    cur.close()
    con.close()

    print("closed")
    