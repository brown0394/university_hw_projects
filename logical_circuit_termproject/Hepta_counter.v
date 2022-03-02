module Hepta_counter(clk,rst,cnt10);

input clk;
input rst;
output [2:0] cnt10;

wire  w39;
wire  w28;
wire [2:0] b25;
wire  w16;
wire  w20;
wire  w32;
wire  w33;
wire  w34;
wire  w37;
wire  w38;
wire  w40;
wire  w19;
wire  w21;
wire  w23;
wire  b25_2;
wire  b25_2_w22;
wire  b25_1;
wire  b25_1_w17;
wire  b25_0;
wire  b25_0_w18;

assign w28 = clk;
assign w39 = rst;
assign cnt10 = b25;

assign b25[2] = b25_2;
assign b25[1] = b25_1;
assign b25[0] = b25_0;

assign b25_2_w22 = {b25[2]};
assign b25_1_w17 = {b25[1]};
assign b25_0_w18 = {b25[0]};

PNU_AND2
     s4 (
      .o1(w37),
      .i1(b25_2_w22),
      .i2(b25_0_w18));

PNU_NOT
     s8 (
      .o1(w16),
      .i1(b25_0_w18));

PNU_AND2
     s9 (
      .o1(w20),
      .i1(b25_1_w17),
      .i2(b25_0_w18));

PNU_OR2
     s16 (
      .i2(w20),
      .i1(w40),
      .o1(w21));

PNU_NOT
     s18 (
      .o1(w32),
      .i1(b25_2_w22));

PNU_NOT
     s19 (
      .o1(w33),
      .i1(b25_1_w17));

PNU_NOT
     s20 (
      .o1(w34),
      .i1(b25_0_w18));

PNU_AND3
     s21 (
      .i1(w32),
      .i2(w33),
      .i3(w34),
      .o1(w38));

PNU_AND2
     s23 (
      .i2(w16),
      .o1(w40),
      .i1(b25_2_w22));

PNU_NOT
     s24 (
      .i1(b25_0_w18),
      .o1(w19));

PNU_OR2
     s22 (
      .i1(w37),
      .i2(w38),
      .o1(w23));

PNU_DFF
     s11 (
      .reset(w39),
      .clock(w28),
      .Q(b25_2),
      .D(w23));

PNU_DFF
     s12 (
      .reset(w39),
      .clock(w28),
      .Q(b25_1),
      .D(w21));

PNU_DFF
     s13 (
      .reset(w39),
      .clock(w28),
      .Q(b25_0),
      .D(w19));

endmodule

