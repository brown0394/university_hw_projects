module Deci_counter(clk,rst,cnt10);

input clk;
input rst;
output [3:0] cnt10;

wire  w0;
wire  w1;
wire [3:0] b21;
wire  w17;
wire  w19;
wire  w20;
wire  w21;
wire  w16;
wire  w24;
wire  w29;
wire  w30;
wire  w31;
wire  w32;
wire  w41;
wire  w42;
wire  w44;
wire  w45;
wire  w46;
wire  w47;
wire  w36;
wire  w37;
wire  w34;
wire  w43;
wire  w48;
wire  w49;
wire  w39;
wire  w52;
wire  w51;
wire  w50;
wire  b21_3;
wire  b21_3_w35;
wire  b21_2;
wire  b21_2_w38;
wire  b21_1;
wire  b21_1_w33;
wire  b21_0;
wire  b21_0_w40;

assign w0 = clk;
assign w1 = rst;
assign cnt10 = b21;

assign b21[3] = b21_3;
assign b21[2] = b21_2;
assign b21[1] = b21_1;
assign b21[0] = b21_0;

assign b21_3_w35 = {b21[3]};
assign b21_2_w38 = {b21[2]};
assign b21_1_w33 = {b21[1]};
assign b21_0_w40 = {b21[0]};

PNU_OR2
     s14 (
      .i1(w16),
      .i2(w24),
      .o1(w50));

PNU_OR3
     s15 (
      .i1(w30),
      .i2(w31),
      .i3(w32),
      .o1(w51));

PNU_AND4
     s20 (
      .i1(w17),
      .i2(w19),
      .i3(w20),
      .i4(w21),
      .o1(w16));

PNU_NOT
     s8 (
      .o1(w17),
      .i1(b21_3_w35));

PNU_NOT
     s9 (
      .o1(w19),
      .i1(b21_2_w38));

PNU_NOT
     s10 (
      .o1(w20),
      .i1(b21_1_w33));

PNU_NOT
     s11 (
      .o1(w21),
      .i1(b21_0_w40));

PNU_AND2
     s12 (
      .o1(w24),
      .i1(b21_3_w35),
      .i2(b21_0_w40));

PNU_AND2
     s13 (
      .o1(w30),
      .i1(b21_2_w38),
      .i2(b21_1_w33));

PNU_AND2
     s16 (
      .o1(w31),
      .i1(b21_2_w38),
      .i2(b21_0_w40));

PNU_AND2
     s17 (
      .i2(w29),
      .o1(w32),
      .i1(b21_3_w35));

PNU_NOT
     s19 (
      .o1(w29),
      .i1(b21_0_w40));

PNU_NOT
     s24 (
      .o1(w36),
      .i1(b21_0_w40));

PNU_AND2
     s25 (
      .o1(w37),
      .i1(b21_1_w33),
      .i2(b21_0_w40));

PNU_AND2
     s27 (
      .i2(w41),
      .i1(w42),
      .o1(w46));

PNU_NOT
     s28 (
      .o1(w42),
      .i1(b21_3_w35));

PNU_NOT
     s29 (
      .o1(w41),
      .i1(b21_0_w40));

PNU_AND2
     s30 (
      .i1(w44),
      .i2(w45),
      .o1(w47));

PNU_NOT
     s31 (
      .o1(w44),
      .i1(b21_1_w33));

PNU_NOT
     s32 (
      .o1(w45),
      .i1(b21_0_w40));

PNU_OR2
     s34 (
      .i1(w46),
      .i2(w47),
      .o1(w39));

PNU_AND2
     s35 (
      .i2(w36),
      .i1(b21_3_w35),
      .o1(w34));

PNU_OR3
     s26 (
      .i3(w37),
      .i2(w34),
      .i1(w49),
      .o1(w52));

PNU_AND3
     s33 (
      .i1(b21_2_w38),
      .i2(w43),
      .i3(w48),
      .o1(w49));

PNU_NOT
     s36 (
      .i1(b21_1_w33),
      .o1(w43));

PNU_NOT
     s37 (
      .i1(b21_0_w40),
      .o1(w48));

PNU_DFF
     s38 (
      .clock(w0),
      .reset(w1),
      .Q(b21_3),
      .D(w50));

PNU_DFF
     s39 (
      .clock(w0),
      .reset(w1),
      .Q(b21_2),
      .D(w51));

PNU_DFF
     s40 (
      .clock(w0),
      .reset(w1),
      .Q(b21_0),
      .D(w39));

PNU_DFF
     s41 (
      .clock(w0),
      .reset(w1),
      .Q(b21_1),
      .D(w52));

endmodule

