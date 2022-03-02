module SegmentOutput(one,ten,SegOut,clk,bomb,zeroSeg);

input [3:0] one;
input [2:0] ten;
output [7:0] SegOut;
input clk;
input bomb;
output [5:0] zeroSeg;

wire [7:0] b0;
wire [7:0] b1;
wire [7:0] b4;
wire [7:0] b5;
wire  w6;
wire [2:0] b7;
wire [3:0] b8;
wire [5:0] b20;
wire  w16;
wire  b8_3_w8;
wire  b8_2_w9;
wire  b8_1_w10;
wire  b8_0_w11;
wire  b7_2_w12;
wire  b7_1_w13;
wire  b7_0_w14;
wire  b20_5;

assign b8 = one;
assign b7 = ten;
assign SegOut = b5;
assign w6 = clk;
assign w16 = bomb;
assign zeroSeg = b20;

assign b20[5] = b20_5;
assign b20[4] = b20_5;
assign b20[3] = b20_5;
assign b20[2] = b20_5;
assign b20[1] = b20_5;
assign b20[0] = b20_5;

assign b8_3_w8 = {b8[3]};
assign b8_2_w9 = {b8[2]};
assign b8_1_w10 = {b8[1]};
assign b8_0_w11 = {b8[0]};
assign b7_2_w12 = {b7[2]};
assign b7_1_w13 = {b7[1]};
assign b7_0_w14 = {b7[0]};

seven_segment_array
     s0 (
      .Out(b0),
      .A(b8_3_w8),
      .B(b8_2_w9),
      .C(b8_1_w10),
      .D(b8_0_w11));

seven_segement_array_two
     s1 (
      .Out(b1),
      .B(b7_2_w12),
      .C(b7_1_w13),
      .D(b7_0_w14));

DifModSelector
     s2 (
      .Mod1(b0),
      .Mod2(b1),
      .Out(b4),
      .difMod(w6));

SegmentEightEight
     s3 (
      .IN(b4),
      .Out(b5),
      .bomb(w16));

PNU_NOT
     s29 (
      .o1(b20_5),
      .i1(w16));

endmodule

