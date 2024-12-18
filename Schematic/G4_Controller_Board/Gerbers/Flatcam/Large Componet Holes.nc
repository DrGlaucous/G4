(G-CODE GENERATED BY FLATCAM v8.994 - www.flatcam.org - Version Date: 2020/11/7)

(Name: G4_Controller_Board-PTH.drl_edit_1_cnc)
(Type: G-code from Geometry)
(Units: MM)

(Created on Sunday, 05 November 2023 at 17:52)

(This preprocessor is the default preprocessor used by FlatCAM.)
(It is made to work with MACH3 compatible motion controllers.)


(TOOLS DIAMETER: )
(Tool: 1 -> Dia: 1.0008)
(Tool: 2 -> Dia: 1.0998)
(Tool: 3 -> Dia: 1.3005)
(Tool: 4 -> Dia: 1.5011)

(FEEDRATE Z: )
(Tool: 1 -> Feedrate: 300)
(Tool: 2 -> Feedrate: 300)
(Tool: 3 -> Feedrate: 300)
(Tool: 4 -> Feedrate: 300)

(FEEDRATE RAPIDS: )
(Tool: 1 -> Feedrate Rapids: 1500)
(Tool: 2 -> Feedrate Rapids: 1500)
(Tool: 3 -> Feedrate Rapids: 1500)
(Tool: 4 -> Feedrate Rapids: 1500)

(Z_CUT: )
(Tool: 1 -> Z_Cut: -1.7)
(Tool: 2 -> Z_Cut: -1.7)
(Tool: 3 -> Z_Cut: -1.7)
(Tool: 4 -> Z_Cut: -1.7)

(Tools Offset: )
(Tool: 1 -> Offset Z: 0.0)
(Tool: 2 -> Offset Z: 0.0)
(Tool: 3 -> Offset Z: 0.0)
(Tool: 4 -> Offset Z: 0.0)

(Z_MOVE: )
(Tool: 1 -> Z_Move: 2)
(Tool: 2 -> Z_Move: 2)
(Tool: 3 -> Z_Move: 2)
(Tool: 4 -> Z_Move: 2)

(Z Toolchange: 15.0 mm)
(X,Y Toolchange: 0.0000, 0.0000 mm)
(Z Start: None mm)
(Z End: 0.5 mm)
(X,Y End: None mm)
(Steps per circle: 64)
(Preprocessor Excellon: default)

(X range:    3.7749 ...   29.6994  mm)
(Y range:   11.5833 ...   74.2756  mm)

(Spindle Speed: 0 RPM)
G21
G90
G94

G01 F300.00

M5
G00 Z15.0000
T1
G00 X0.0000 Y0.0000                
M6
(MSG, Change to Tool Dia = 1.0008 ||| Total drills for tool T1 = 25)
M0
G00 Z15.0000

G01 F300.00
M03
G00 X19.7108 Y73.7752
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X14.7121 Y73.7752
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X11.6000 Y67.1000
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X11.6108 Y66.7750
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X11.6000 Y66.4000
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X14.7121 Y59.2744
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X12.7182 Y48.2152
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X4.4251 Y39.4624
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X4.4251 Y34.4611
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X4.4251 Y29.4624
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X4.4251 Y22.2336
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X4.4251 Y17.2348
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X4.4251 Y12.2336
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X24.0695 Y31.0270
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X26.6095 Y31.0270
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X29.1495 Y31.0270
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X18.3545 Y41.2302
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X15.8145 Y41.2302
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X13.2745 Y41.2302
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X17.7195 Y48.2152
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X17.2115 Y59.2744
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X19.7108 Y59.2744
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X22.8000 Y66.4000
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X22.8000 Y67.2000
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X22.8122 Y66.7750
G01 Z-1.7000
G01 Z0
G00 Z2.0000
M05
G00 Z0.50


