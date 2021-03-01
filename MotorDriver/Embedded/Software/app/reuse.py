import dash
from dash.dependencies import Output, Input, State
import dash_core_components as dcc
import dash_html_components as html
import dash_bootstrap_components as dbc

global parameterTable, gridColor, uoaLightBlue, uoaDarkBlue, textColor, uoaGray, lightGray, textGray, oxfordBlue, skobeloff, middleYellow

#color values
uoaLightBlue = '#009AC7'
uoaDarkBlue = 'rgb(18, 61, 113)'
uoaGray = "#8D9091"
lightGray = "rgb(228, 231, 235)"
oxfordBlue = '#001629'
skobeloff = '#127475'
middleYellow = '#F7E733'
prussianBlue = '#002C52'
richBlack = "#000B14"
darkGray = '#3D3D3D'

textColor = '#C5C6C7'
gridColor = '#192841'

#system parameter table
parameterTableHeader = [html.Thead(html.Tr([html.Th("Parameter"), html.Th("Value")]))]
row1 = html.Tr([html.Td("Max Voltage at H-Bridge"), html.Td("12V")])
row2 = html.Tr([html.Td("Max Current at H-Bridge"), html.Td("2.5A")])
row3 = html.Tr([html.Td("Car Power Rating"), html.Td("30W")])
parameterTableBody = [html.Tbody([row1, row2, row3])]

parameterTable = dbc.Table(parameterTableHeader + parameterTableBody, className = "table table-dark", bordered = True, striped = True, hover = True)