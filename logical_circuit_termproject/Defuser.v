module Defuser(clk,rst,difMod,k1,k2,k3,k4,k5,LED,SegOut,sixLightOut,oneSeg,tenSeg,start,timMod,mutemod,fLedG,stepmot,piezo,fLedR);

input clk;
input rst;
input difMod;
input k1;
input k2;
input k3;
input k4;
input k5;
output [7:0] LED;
output [7:0] SegOut;
output [5:0] sixLightOut;
output oneSeg;
output tenSeg;
input start;
input timMod;
input mutemod;
output [3:0] fLedG;
output [3:0] stepmot;
output piezo;
output [3:0] fLedR;

wire  w6;
wire  w8;
wire  w9;
wire  w10;
wire  w11;
wire  w12;
wire  w13;
wire  w18;
wire [7:0] b15;
wire [7:0] b19;
wire [5:0] b20;
wire  w30;
wire  w26;
wire  w31;
wire  w32;
wire  w33;
wire  w45;
wire [3:0] b29;
wire [3:0] b30;
wire [3:0] b31;
wire  w29;
wire  w40;
wire  w34;
wire  w37;
wire [3:0] b32;
wire [2:0] b28;
wire  w28;
wire  w35;
wire  w38;
wire  w39;
wire  w41;
wire  w36;

assign w40 = clk;
assign w33 = rst;
assign w8 = difMod;
assign w13 = k1;
assign w12 = k2;
assign w11 = k3;
assign w10 = k4;
assign w9 = k5;
assign LED = b15;
assign SegOut = b19;
assign sixLightOut = b20;
assign oneSeg = w45;
assign tenSeg = w35;
assign w26 = start;
assign w30 = timMod;
assign w34 = mutemod;
assign fLedG = b30;
assign stepmot = b29;
assign piezo = w29;
assign fLedR = b31;

PNU_AND2
     s2 (
      .o1(w6),
      .i1(w18),
      .i2(w36));

PNU_NOT
     s3 (
      .o1(w18),
      .i1(w28));

key_led
     s5 (
      .DifMod(w8),
      .K5(w9),
      .K4(w10),
      .K3(w11),
      .K2(w12),
      .K1(w13),
      .LED(b15),
      .CLK(w40),
      .reset(w37),
      .isd(w36));

time_counter
     s4 (
      .defused(w6),
      .timeMod(w30),
      .one(w45),
      .clk(w40),
      .rst(w37),
      .deciSeg(b32),
      .hexSeg(b28),
      .bomb(w28),
      .ten(w35),
      .tensec(w38),
      .LSB(w39),
      .sec(w41));

SegmentOutput
     s6 (
      .SegOut(b19),
      .zeroSeg(b20),
      .clk(w40),
      .one(b32),
      .ten(b28),
      .bomb(w28));

PNU_OR2
     s8 (
      .i2(w32),
      .i1(w33),
      .o1(w37));

PNU_DFF_Ce
     s7 (
      .Ce(w26),
      .D(w26),
      .Q(w31),
      .reset(w33),
      .clock(w40));

PNU_NOT
     s9 (
      .i1(w31),
      .o1(w32));

Effects
     s10 (
      .stepout(b29),
      .fLEDG(b30),
      .fLEDR(b31),
      .clk(w40),
      .mute(w34),
      .rst(w37),
      .bomb(w28),
      .u10(w38),
      .defused(w36));

Effect_piezo
     s11 (
      .piezoout(w29),
      .clk(w40),
      .mute(w34),
      .rst(w37),
      .bomb(w28),
      .u10(w38),
      .LSB(w39),
      .sec(w41),
      .defused(w36));

endmodule

