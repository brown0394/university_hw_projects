module key_led(K1,K2,K3,K4,reset,CLK,LED,isd,DifMod,K5);

input K1;
input K2;
input K3;
input K4;
input reset;
input CLK;
output [7:0] LED;
output isd;
input DifMod;
input K5;

wire [3:0] b11;
wire [7:0] b12;
wire [7:0] b13;
wire [7:0] b14;
wire [7:0] b15;
wire [7:0] b17;
wire [7:0] b20;
wire [2:0] b21;
wire  w20;
wire  w30;
wire  w26;
wire  w27;
wire  w28;
wire  w29;
wire  w25;
wire [7:0] b26;
wire [7:0] b25;
wire  w34;
wire  w32;
wire  w33;
wire [7:0] b27;
wire  w31;
wire  b11_1_w8;
wire  b11_3_w9;
wire  b11_0_w11;
wire  b11_2_w12;

assign w26 = K1;
assign w27 = K2;
assign w28 = K3;
assign w29 = K4;
assign w33 = reset;
assign w34 = CLK;
assign LED = b20;
assign isd = w25;
assign w20 = DifMod;
assign w30 = K5;

assign b11_1_w8 = {b11[1]};
assign b11_3_w9 = {b11[3]};
assign b11_0_w11 = {b11[0]};
assign b11_2_w12 = {b11[2]};

register_8bit
     s1 (
      .Dout(b20),
      .clk(w34),
      .rst(w33),
      .Din(b27),
      .Ce(w31));

Enablechk
     s2 (
      .Input(b17),
      .out(w32));

XorOp
     s3 (
      .en(b11_2_w12),
      .Out(b15),
      .IN(b17),
      .SV(b20));

Xnor
     s4 (
      .en(b11_0_w11),
      .Out(b14),
      .IN(b17),
      .SV(b20));

OrEightbit
     s5 (
      .en(b11_3_w9),
      .Out(b13),
      .IN(b17),
      .SV(b20));

OpSelector
     s6 (
      .p1(b11),
      .in(b21));

Nor
     s7 (
      .en(b11_1_w8),
      .Out(b12),
      .IN(b17),
      .SV(b20));

OpCounter
     s8 (
      .out(b21),
      .Input(w32),
      .rst(w33));

TwoFourEight
     s9 (
      .norr(b12),
      .orr(b13),
      .xnorr(b14),
      .xorr(b15),
      .out(b27));

IsDefused
     s10 (
      .in(b20),
      .out(w25));

LTP
     s14 (
      .clk(w34),
      .Level(w32),
      .rst(w33),
      .Pulse(w31));

DifModSelector
     s15 (
      .Out(b17),
      .difMod(w20),
      .Mod2(b26),
      .Mod1(b25));

InputSelectorMod2
     s12 (
      .K5(w30),
      .K1(w26),
      .K2(w27),
      .K3(w28),
      .K4(w29),
      .out(b26));

InputSelector
     s13 (
      .K1(w26),
      .K2(w27),
      .K3(w28),
      .K4(w29),
      .out(b25));

endmodule

