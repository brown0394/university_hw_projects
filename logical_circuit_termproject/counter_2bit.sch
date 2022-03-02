ModuleName counter_2bit
LanguageType Veirlog
GridInterval 8
MillimetersIn100RealScaledUnit 25
ZoomOutScale 64
NumberOfHorzPapaers 8
NumberOfVertPapaers 4
Parameters
End
Wires
Wire Name: w0
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 208 ,Y1: 136 ,X2: 232 ,Y2: 136
Edge X1: 208 ,Y1: 136 ,X2: 208 ,Y2: 272
Edge X1: 208 ,Y1: 272 ,X2: 208 ,Y2: 336
Edge X1: 208 ,Y1: 272 ,X2: 232 ,Y2: 272
Edge X1: 192 ,Y1: 336 ,X2: 208 ,Y2: 336
End
Branches
End
Wire Name: w1
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 224 ,Y1: 184 ,X2: 288 ,Y2: 184
Edge X1: 224 ,Y1: 184 ,X2: 224 ,Y2: 352
Edge X1: 192 ,Y1: 352 ,X2: 224 ,Y2: 352
Edge X1: 224 ,Y1: 352 ,X2: 288 ,Y2: 352
Edge X1: 288 ,Y1: 320 ,X2: 288 ,Y2: 352
End
Branches
End
Wire Name: w2
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 344 ,Y1: 88 ,X2: 432 ,Y2: 88
End
Branches
End
Wire Name: w3
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 384 ,Y1: 224 ,X2: 432 ,Y2: 224
Edge X1: 384 ,Y1: 104 ,X2: 384 ,Y2: 224
Edge X1: 344 ,Y1: 224 ,X2: 384 ,Y2: 224
Edge X1: 384 ,Y1: 104 ,X2: 432 ,Y2: 104
End
Branches
End
Wire Name: b4
LV: 1
RV: 0
Width: 2
Edges
Edge X1: 488 ,Y1: 32 ,X2: 568 ,Y2: 32
End
Branches
Branch Left: 512 ,Top: 32
BranchStrList
1
End
Branch Left: 528 ,Top: 32
BranchStrList
0
End
End
Wire Name: w6
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 184 ,Y1: 224 ,X2: 232 ,Y2: 224
Edge X1: 184 ,Y1: 56 ,X2: 184 ,Y2: 224
Edge X1: 184 ,Y1: 56 ,X2: 528 ,Y2: 56
Edge X1: 528 ,Y1: 32 ,X2: 528 ,Y2: 56
Edge X1: 528 ,Y1: 56 ,X2: 528 ,Y2: 224
Edge X1: 488 ,Y1: 224 ,X2: 528 ,Y2: 224
End
Branches
End
Wire Name: w7
LV: 0
RV: 0
Width: 1
Edges
Edge X1: 200 ,Y1: 88 ,X2: 232 ,Y2: 88
Edge X1: 200 ,Y1: 72 ,X2: 200 ,Y2: 88
Edge X1: 200 ,Y1: 72 ,X2: 512 ,Y2: 72
Edge X1: 512 ,Y1: 32 ,X2: 512 ,Y2: 72
Edge X1: 512 ,Y1: 72 ,X2: 512 ,Y2: 96
Edge X1: 496 ,Y1: 96 ,X2: 512 ,Y2: 96
End
Branches
End
End
Ports
Port Left: 192 Top: 336 ,Orientation: 0
Portname: clk ,PortType: singlebit ,LanguageType: Veriilog ,PortDirection: 0 ,LV:
0
,Width:
1
,RV:
0
Port Left: 192 Top: 352 ,Orientation: 0
Portname: rst ,PortType: singlebit ,LanguageType: Veriilog ,PortDirection: 0 ,LV:
0
,Width:
1
,RV:
0
Port Left: 568 Top: 32 ,Orientation: 0
Portname: Dout ,PortType: multibit ,LanguageType: Veriilog ,PortDirection: 2 ,LV:
1
,Width:
2
,RV:
0
End
Symbols
Symbol Left: 256 Top: 80
Name: s0
LibraryName: PNULib
IpName: PNU_DFF
SymbolParameters
End
Symbol Left: 256 Top: 216
Name: s1
LibraryName: PNULib
IpName: PNU_DFF
SymbolParameters
End
Symbol Left: 432 Top: 80
Name: s2
LibraryName: PNULib
IpName: PNU_XOR2
SymbolParameters
End
Symbol Left: 432 Top: 216
Name: s3
LibraryName: PNULib
IpName: PNU_NOT
SymbolParameters
End
End
Texts
End
Links
End
