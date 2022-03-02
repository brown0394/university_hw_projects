ModuleName StepBomb
LanguageType Veirlog
GridInterval 8
MillimetersIn100RealScaledUnit 25
ZoomOutScale 81
NumberOfHorzPapaers 8
NumberOfVertPapaers 4
Parameters
End
Wires
Wire Name: b11
LV: 3
RV: 0
Width: 4
Edges
Edge X1: 1552 ,Y1: 168 ,X2: 1584 ,Y2: 168
End
Branches
End
Wire Name: w18
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 368 ,Y1: 312 ,X2: 416 ,Y2: 312
End
Branches
End
Wire Name: w6
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 784 ,Y1: 264 ,X2: 808 ,Y2: 264
End
Branches
End
Wire Name: w7
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 648 ,Y1: 240 ,X2: 880 ,Y2: 240
Edge X1: 648 ,Y1: 240 ,X2: 648 ,Y2: 264
Edge X1: 880 ,Y1: 240 ,X2: 880 ,Y2: 264
Edge X1: 864 ,Y1: 264 ,X2: 880 ,Y2: 264
Edge X1: 880 ,Y1: 264 ,X2: 896 ,Y2: 264
Edge X1: 648 ,Y1: 264 ,X2: 672 ,Y2: 264
End
Branches
End
Wire Name: w8
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 1008 ,Y1: 216 ,X2: 1032 ,Y2: 216
End
Branches
End
Wire Name: w9
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 872 ,Y1: 192 ,X2: 1104 ,Y2: 192
Edge X1: 872 ,Y1: 192 ,X2: 872 ,Y2: 216
Edge X1: 1104 ,Y1: 192 ,X2: 1104 ,Y2: 216
Edge X1: 1088 ,Y1: 216 ,X2: 1104 ,Y2: 216
Edge X1: 1104 ,Y1: 216 ,X2: 1120 ,Y2: 216
Edge X1: 872 ,Y1: 216 ,X2: 896 ,Y2: 216
End
Branches
End
Wire Name: w10
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 1232 ,Y1: 168 ,X2: 1256 ,Y2: 168
End
Branches
End
Wire Name: w14
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 584 ,Y1: 312 ,X2: 672 ,Y2: 312
End
Branches
End
Wire Name: w11
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 1096 ,Y1: 144 ,X2: 1328 ,Y2: 144
Edge X1: 1096 ,Y1: 144 ,X2: 1096 ,Y2: 168
Edge X1: 1328 ,Y1: 144 ,X2: 1328 ,Y2: 168
Edge X1: 1312 ,Y1: 168 ,X2: 1328 ,Y2: 168
Edge X1: 1328 ,Y1: 168 ,X2: 1384 ,Y2: 168
Edge X1: 1096 ,Y1: 168 ,X2: 1120 ,Y2: 168
End
Branches
End
Wire Name: w13
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 120 ,Y1: 312 ,X2: 200 ,Y2: 312
End
Branches
End
Wire Name: w12
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 1176 ,Y1: 408 ,X2: 1336 ,Y2: 408
Edge X1: 952 ,Y1: 408 ,X2: 1176 ,Y2: 408
Edge X1: 1176 ,Y1: 264 ,X2: 1176 ,Y2: 408
Edge X1: 1336 ,Y1: 184 ,X2: 1336 ,Y2: 408
Edge X1: 1336 ,Y1: 184 ,X2: 1384 ,Y2: 184
Edge X1: 728 ,Y1: 408 ,X2: 952 ,Y2: 408
Edge X1: 952 ,Y1: 312 ,X2: 952 ,Y2: 408
Edge X1: 416 ,Y1: 408 ,X2: 728 ,Y2: 408
Edge X1: 728 ,Y1: 360 ,X2: 728 ,Y2: 408
Edge X1: 200 ,Y1: 408 ,X2: 416 ,Y2: 408
Edge X1: 416 ,Y1: 328 ,X2: 416 ,Y2: 408
Edge X1: 200 ,Y1: 328 ,X2: 200 ,Y2: 408
Edge X1: 96 ,Y1: 408 ,X2: 200 ,Y2: 408
End
Branches
End
End
Ports
Port Left: 120 Top: 312 ,Orientation: 0
Portname: clk ,PortType: singlebit ,LanguageType: Veriilog ,PortDirection: 0 ,LV:
0
,Width:
1
,RV:
0
Port Left: 96 Top: 408 ,Orientation: 0
Portname: rst ,PortType: singlebit ,LanguageType: Veriilog ,PortDirection: 0 ,LV:
0
,Width:
1
,RV:
0
Port Left: 1584 Top: 168 ,Orientation: 0
Portname: st ,PortType: multibit ,LanguageType: Veriilog ,PortDirection: 2 ,LV:
3
,Width:
4
,RV:
0
End
Symbols
Symbol Left: 224 Top: 304
Name: s1
LibraryName: (NoLibraryName)
IpName: Clock_Divisior
SymbolParameters
End
Symbol Left: 1408 Top: 160
Name: s0
LibraryName: (NoLibraryName)
IpName: stepMotor
SymbolParameters
End
Symbol Left: 440 Top: 304
Name: s10
LibraryName: (NoLibraryName)
IpName: Clock_Divisior
SymbolParameters
End
Symbol Left: 696 Top: 256
Name: s3
LibraryName: PNULib
IpName: PNU_DFF
SymbolParameters
End
Symbol Left: 808 Top: 256
Name: s4
LibraryName: PNULib
IpName: PNU_NOT
SymbolParameters
End
Symbol Left: 920 Top: 208
Name: s2
LibraryName: PNULib
IpName: PNU_DFF
SymbolParameters
End
Symbol Left: 1032 Top: 208
Name: s6
LibraryName: PNULib
IpName: PNU_NOT
SymbolParameters
End
Symbol Left: 1144 Top: 160
Name: s7
LibraryName: PNULib
IpName: PNU_DFF
SymbolParameters
End
Symbol Left: 1256 Top: 160
Name: s5
LibraryName: PNULib
IpName: PNU_NOT
SymbolParameters
End
End
Texts
End
Links
End
