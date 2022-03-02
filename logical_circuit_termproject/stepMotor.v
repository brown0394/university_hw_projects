module stepMotor(clk,rst,cnt10);

input clk;
input rst;
output [3:0] cnt10;

wire  w0;
wire  w1;
wire [3:0] b21;
wire  w15;
wire  w17;
wire  w18;
wire  w19;
wire  w20;
wire  w21;
wire  w22;
wire  w14;
wire  b21_0;
wire  b21_0_w11;
wire  b21_1;
wire  b21_1_w24;
wire  b21_2;
wire  b21_2_w23;
wire  b21_3;
wire  b21_3_w16;

assign w0 = clk;
assign w1 = rst;
assign cnt10 = b21;

assign b21[3] = b21_3;
assign b21[2] = b21_2;
assign b21[1] = b21_1;
assign b21[0] = b21_0;

assign b21_0_w11 = {b21[0]};
assign b21_1_w24 = {b21[1]};
assign b21_2_w23 = {b21[2]};
assign b21_3_w16 = {b21[3]};

PNU_AND4
     s4 (
      .i1(w17),
      .i2(w18),
      .i3(w19),
      .i4(w20),
      .o1(w21));

PNU_AND2
     s5 (
      .i1(w15),
      .i2(b21_0_w11),
      .o1(w22));

PNU_OR2
     s6 (
      .i1(w21),
      .i2(w22),
      .o1(w14));

PNU_NOT
     s7 (
      .o1(w17),
      .i1(b21_3_w16));

PNU_NOT
     s8 (
      .o1(w18),
      .i1(b21_2_w23));

PNU_NOT
     s9 (
      .o1(w19),
      .i1(b21_1_w24));

PNU_NOT
     s10 (
      .i1(b21_0_w11),
      .o1(w20));

PNU_NOT
     s11 (
      .o1(w15),
      .i1(b21_3_w16));

PNU_DFF
     s12 (
      .clock(w0),
      .reset(w1),
      .Q(b21_3),
      .D(w14));

PNU_DFF
     s13 (
      .clock(w0),
      .reset(w1),
      .Q(b21_2),
      .D(b21_3_w16));

PNU_DFF
     s14 (
      .clock(w0),
      .reset(w1),
      .Q(b21_1),
      .D(b21_2_w23));

PNU_DFF
     s15 (
      .clock(w0),
      .reset(w1),
      .Q(b21_0),
      .D(b21_1_w24));

endmodule

