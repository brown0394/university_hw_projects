ModuleName TriMode
LanguageType Veirlog
GridInterval 8
MillimetersIn100RealScaledUnit 25
ZoomOutScale 64
NumberOfHorzPapaers 8
NumberOfVertPapaers 4
Parameters
End
Wires
Wire Name: w23
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 352 ,Y1: 408 ,X2: 352 ,Y2: 560
Edge X1: 352 ,Y1: 408 ,X2: 440 ,Y2: 408
Edge X1: 352 ,Y1: 264 ,X2: 352 ,Y2: 408
Edge X1: 232 ,Y1: 560 ,X2: 352 ,Y2: 560
Edge X1: 440 ,Y1: 392 ,X2: 440 ,Y2: 408
Edge X1: 352 ,Y1: 264 ,X2: 440 ,Y2: 264
Edge X1: 440 ,Y1: 248 ,X2: 440 ,Y2: 264
End
Branches
End
Wire Name: w24
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 320 ,Y1: 344 ,X2: 320 ,Y2: 496
Edge X1: 320 ,Y1: 344 ,X2: 384 ,Y2: 344
Edge X1: 320 ,Y1: 200 ,X2: 320 ,Y2: 344
Edge X1: 232 ,Y1: 496 ,X2: 320 ,Y2: 496
Edge X1: 320 ,Y1: 200 ,X2: 384 ,Y2: 200
End
Branches
End
Wire Name: w9
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 656 ,Y1: 184 ,X2: 696 ,Y2: 184
End
Branches
End
Wire Name: b10
LV: 1
RV: 0
Width: 2
Edges
Edge X1: 536 ,Y1: 736 ,X2: 672 ,Y2: 736
End
Branches
Branch Left: 544 ,Top: 736
BranchStrList
1
End
Branch Left: 560 ,Top: 736
BranchStrList
0
End
End
Wire Name: w16
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 656 ,Y1: 200 ,X2: 696 ,Y2: 200
End
Branches
End
Wire Name: w18
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 672 ,Y1: 280 ,X2: 696 ,Y2: 280
End
Branches
End
Wire Name: w12
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 496 ,Y1: 296 ,X2: 560 ,Y2: 296
Edge X1: 560 ,Y1: 296 ,X2: 560 ,Y2: 736
Edge X1: 560 ,Y1: 280 ,X2: 560 ,Y2: 296
Edge X1: 560 ,Y1: 280 ,X2: 616 ,Y2: 280
Edge X1: 560 ,Y1: 200 ,X2: 560 ,Y2: 280
Edge X1: 560 ,Y1: 104 ,X2: 560 ,Y2: 200
Edge X1: 560 ,Y1: 200 ,X2: 600 ,Y2: 200
End
Branches
End
Wire Name: w13
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 496 ,Y1: 152 ,X2: 544 ,Y2: 152
Edge X1: 544 ,Y1: 104 ,X2: 544 ,Y2: 152
Edge X1: 544 ,Y1: 152 ,X2: 544 ,Y2: 184
Edge X1: 544 ,Y1: 184 ,X2: 600 ,Y2: 184
Edge X1: 544 ,Y1: 184 ,X2: 544 ,Y2: 264
Edge X1: 544 ,Y1: 264 ,X2: 544 ,Y2: 736
Edge X1: 544 ,Y1: 264 ,X2: 696 ,Y2: 264
End
Branches
End
Wire Name: w10
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 760 ,Y1: 192 ,X2: 952 ,Y2: 192
Edge X1: 952 ,Y1: 72 ,X2: 952 ,Y2: 192
Edge X1: 352 ,Y1: 72 ,X2: 952 ,Y2: 72
Edge X1: 352 ,Y1: 72 ,X2: 352 ,Y2: 152
Edge X1: 352 ,Y1: 152 ,X2: 384 ,Y2: 152
End
Branches
End
Wire Name: w11
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 328 ,Y1: 56 ,X2: 968 ,Y2: 56
Edge X1: 328 ,Y1: 56 ,X2: 328 ,Y2: 296
Edge X1: 968 ,Y1: 56 ,X2: 968 ,Y2: 272
Edge X1: 760 ,Y1: 272 ,X2: 968 ,Y2: 272
Edge X1: 328 ,Y1: 296 ,X2: 384 ,Y2: 296
End
Branches
End
End
Ports
Port Left: 232 Top: 496 ,Orientation: 0
Portname: clk ,PortType: singlebit ,LanguageType: Veriilog ,PortDirection: 0 ,LV:
0
,Width:
1
,RV:
0
Port Left: 232 Top: 560 ,Orientation: 0
Portname: rst ,PortType: singlebit ,LanguageType: Veriilog ,PortDirection: 0 ,LV:
0
,Width:
1
,RV:
0
Port Left: 672 Top: 736 ,Orientation: 0
Portname: cnt3 ,PortType: multibit ,LanguageType: Veriilog ,PortDirection: 2 ,LV:
1
,Width:
2
,RV:
0
End
Symbols
Symbol Left: 600 Top: 176
Name: s3
LibraryName: PNULib
IpName: PNU_NOT
SymbolParameters
End
Symbol Left: 696 Top: 176
Name: s4
LibraryName: PNULib
IpName: PNU_AND2
SymbolParameters
End
Symbol Left: 696 Top: 256
Name: s5
LibraryName: PNULib
IpName: PNU_AND2
SymbolParameters
End
Symbol Left: 600 Top: 192
Name: s6
LibraryName: PNULib
IpName: PNU_NOT
SymbolParameters
End
Symbol Left: 616 Top: 272
Name: s7
LibraryName: PNULib
IpName: PNU_NOT
SymbolParameters
End
Symbol Left: 408 Top: 144
Name: s8
LibraryName: PNULib
IpName: PNU_DFF
SymbolParameters
End
Symbol Left: 408 Top: 288
Name: s9
LibraryName: PNULib
IpName: PNU_DFF
SymbolParameters
End
End
Texts
Text Left: 472 Top: 136
Text:
A
,Width: 13 ,Height: 15 ,FontSize: 8 ,TextColor: 0 ,BackgroundColor: 16777215
Text Left: 472 Top: 280
Text:
B
,Width: 13 ,Height: 15 ,FontSize: 8 ,TextColor: 0 ,BackgroundColor: 16777215
Text Left: 536 Top: 80
Text:
A
,Width: 13 ,Height: 15 ,FontSize: 8 ,TextColor: 0 ,BackgroundColor: 16777215
Text Left: 552 Top: 80
Text:
B
,Width: 13 ,Height: 15 ,FontSize: 8 ,TextColor: 0 ,BackgroundColor: 16777215
End
Links
End
