import dash
from dash.dependencies import Output, Input, State
import dash_core_components as dcc
import dash_html_components as html
import dash_bootstrap_components as dbc

global parameterTable, uoaLightBlue, uoaDarkBlue, uoaGray, textColor, lightGray

#color values
uoaLightBlue = '#009AC7'
uoaDarkBlue = 'rgb(18, 61, 113)'
uoaGray = "#8D9091"
textColor = 'black'
lightGray = "rgb(228, 231, 235)"

#system parameter table
parameterTableHeader = [html.Thead(html.Tr([html.Th("Parameter"), html.Th("Value")]))]
row1 = html.Tr([html.Td("Max Voltage at H-Bridge"), html.Td("20V")])
row2 = html.Tr([html.Td("Max Current at H-Bridge"), html.Td("3A")])
row3 = html.Tr([html.Td("Car Power Rating"), html.Td("30W")])
parameterTableBody = [html.Tbody([row1, row2, row3])]

parameterTable = dbc.Table(parameterTableHeader + parameterTableBody, bordered= True, striped = True, hover = True)